/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/02 12:13:55 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define SW 640
#define SH 480
#define MAPW 24
#define MAPH 24

typedef struct s_mlx
{
	void	*mlx_p;
	void	*img;
	void	*win_ptr;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	double	moveSpeed;
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
}	t_mlx;


int worldMap[MAPW][MAPH]=
{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw_vertical_line(t_mlx *mlx, int x)
{
	int	y;

	y = mlx->drawStart;
	while (y <= mlx->drawEnd)
	{
		mlx_pixel_put(mlx->mlx_p, mlx->win_ptr, x, y, mlx->color);
		y++;
	}
}

void	raycasting(t_mlx *mlx)
{
	int	x;

	x = 0;
	while (x < SW)
	{
		mlx->cameraX = 2 * x / (double)SW - 1;
		mlx->rayDirX = mlx->dirX + mlx->planeX * mlx->cameraX;
		mlx->rayDirY = mlx->dirY + mlx->planeY * mlx->cameraX;

		mlx->mapX = (int)mlx->posX;
		mlx->mapY = (int)mlx->posY;

		mlx->deltaDistX = fabs(1 / mlx->rayDirX);
		mlx->deltaDistY = fabs(1 / mlx->rayDirY);

		mlx->hit = 0;

		if (mlx->rayDirX < 0)
		{
			mlx->stepX = -1;
			mlx->sideDistX = (mlx->posX - mlx->mapX) * mlx->deltaDistX;
		}
		else
		{
			mlx->stepX = 1;
			mlx->sideDistX = (mlx->mapX + 1.0 - mlx->posX) * mlx->deltaDistX;
		}
		if (mlx->rayDirY < 0)
		{
			mlx->stepY = -1;
			mlx->sideDistY = (mlx->posY - mlx->mapY) * mlx->deltaDistY;
		}
		else
		{
			mlx->stepY = 1;
			mlx->sideDistY = (mlx->mapY + 1.0 - mlx->posY) * mlx->deltaDistY;
		}

		while (mlx->hit == 0)
		{
			if (mlx->sideDistX < mlx->sideDistY)
			{
				mlx->sideDistX += mlx->deltaDistX;
				mlx->mapX += mlx->stepX;
				mlx->side = 0;
			}
			else
			{
				mlx->sideDistY += mlx->deltaDistY;
				mlx->mapY += mlx->stepY;
				mlx->side = 1;
			}
			if (worldMap[mlx->mapX][mlx->mapY] > 0)
				mlx->hit = 1;
		}

		if (mlx->side == 0)
			mlx->perpWallDist = (mlx->sideDistX - mlx->deltaDistX);
		else
			mlx->perpWallDist = (mlx->sideDistY - mlx->deltaDistY);

		mlx->lineHeight = (int)(SH / mlx->perpWallDist);
		mlx->drawStart = -mlx->lineHeight / 2 + SH / 2;
		if (mlx->drawStart < 0)
			mlx->drawStart = 0;
		mlx->drawEnd = mlx->lineHeight / 2 + SH / 2;
		if (mlx->drawEnd >= SH)
			mlx->drawEnd = SH - 1;

		if (worldMap[mlx->mapX][mlx->mapY] == 1)
			mlx->color = 0xFF0000;
		else if (worldMap[mlx->mapX][mlx->mapY] == 2)
			mlx->color = 0x00FF00;
		else if (worldMap[mlx->mapX][mlx->mapY] == 3)
			mlx->color = 0x0000FF;
		else if (worldMap[mlx->mapX][mlx->mapY] == 4)
			mlx->color = 0xFFFFFF;
		else
			mlx->color = 0xFFFF00;

		if (mlx->side == 1)
			mlx->color = mlx->color / 2;

		draw_vertical_line(mlx, x);
		x++;
	}
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->mlx_p, mlx->win_ptr);
		exit(0);
	}
	if (keycode == 119)
	{
		if (!worldMap[(int)(mlx->posX + mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX += mlx->dirX * mlx->moveSpeed;
		if (!worldMap[(int)mlx->posX][(int)(mlx->posY + mlx->dirY * mlx->moveSpeed)])
			mlx->posY += mlx->dirY * mlx->moveSpeed;
		mlx_clear_window(mlx->mlx_p, mlx->win_ptr);
		raycasting(mlx);
	}
	if (keycode == 115)
	{
		if (!worldMap[(int)(mlx->posX - mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX -= mlx->dirX * mlx->moveSpeed;
		if (!worldMap[(int)mlx->posX][(int)(mlx->posY - mlx->dirY * mlx->moveSpeed)])
			mlx->posY -= mlx->dirY * mlx->moveSpeed;
		mlx_clear_window(mlx->mlx_p, mlx->win_ptr);
		raycasting(mlx);
	}
	if (keycode == 97)
	{
		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(mlx->rotSpeed) - mlx->dirY * sin(mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(mlx->rotSpeed) + mlx->dirY * cos(mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(mlx->rotSpeed) - mlx->planeY * sin(mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(mlx->rotSpeed) + mlx->planeY * cos(mlx->rotSpeed);
		mlx_clear_window(mlx->mlx_p, mlx->win_ptr);
		raycasting(mlx);
	}
	if (keycode == 100)
	{
		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(-mlx->rotSpeed) - mlx->dirY * sin(-mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(-mlx->rotSpeed) + mlx->dirY * cos(-mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(-mlx->rotSpeed) - mlx->planeY * sin(-mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(-mlx->rotSpeed) + mlx->planeY * cos(-mlx->rotSpeed);
		mlx_clear_window(mlx->mlx_p, mlx->win_ptr);
		raycasting(mlx);
	}
	return (0);
}

void	init_values(t_mlx *mlx)
{
	mlx->posX = 22;
	mlx->posY = 12;
	mlx->dirX = -1;
	mlx->dirY = 0;
	mlx->planeX = 0;
	mlx->planeY = 0.66;
	mlx->time = 0;
	mlx->oldTime = 0;
	mlx->moveSpeed = 0.1;
	mlx->rotSpeed = 0.1;
}

void	start_game(t_mlx *mlx)
{
	mlx->mlx_p = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_p, SW, SH, "cub3d");
	mlx_key_hook(mlx->win_ptr, key_hook, mlx);
	raycasting(mlx);
	mlx_loop(mlx->mlx_p);
}

int	main(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	init_values(mlx);
	start_game(mlx);
}
