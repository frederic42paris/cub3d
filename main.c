/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/04 18:59:52 by ftanon           ###   ########.fr       */
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
#define KEY_W	119
#define KEY_S	115
#define KEY_D	100
#define KEY_A	97
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define TEXTW 64
#define TEXTH 64

typedef struct s_mlx
{
	void	*mlx_p;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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

	void	*greystone;
	int		*greystone_addr;
	void	*bluestone;
	int		*bluestone_addr;
	void	*red;
	int		*red_addr;
	void	*wood;
	int		*wood_addr;
	int		texNum;
	double	wallX;
	int 	texX;
	double 	step;
	double	texPos;
	int		texY;
	int		bits_per_pixel_grey;
	int		line_length_grey;
	int		endian_grey;
	int		bits_per_pixel_blue;
	int		line_length_blue;
	int		endian_blue;
	int		bits_per_pixel_red;
	int		line_length_red;
	int		endian_red;
	int		bits_per_pixel_wood;
	int		line_length_wood;
	int		endian_wood;

	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		p;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
	int		checkerBoardPattern;
	int		floorTexture;
	int		ceilingTexture;
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

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->mlx_p, mlx->win_ptr);
		exit(0);
	}
	if (keycode == KEY_W)
	{
		if (!worldMap[(int)(mlx->posX + mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX += mlx->dirX * mlx->moveSpeed;
		if (!worldMap[(int)mlx->posX][(int)(mlx->posY + mlx->dirY * mlx->moveSpeed)])
			mlx->posY += mlx->dirY * mlx->moveSpeed;
	}
	if (keycode == KEY_S)
	{
		if (!worldMap[(int)(mlx->posX - mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX -= mlx->dirX * mlx->moveSpeed;
		if (!worldMap[(int)mlx->posX][(int)(mlx->posY - mlx->dirY * mlx->moveSpeed)])
			mlx->posY -= mlx->dirY * mlx->moveSpeed;
	}
	if (keycode == KEY_D)
	{
		if (!worldMap[(int)(mlx->posX + mlx->dirY * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX += mlx->dirY * mlx->moveSpeed;
		if (!worldMap[(int)mlx->posX][(int)(mlx->posY - mlx->dirX * mlx->moveSpeed)])
			mlx->posY -= mlx->dirX * mlx->moveSpeed;
	}
	if (keycode == KEY_A)
	{
		if (!worldMap[(int)(mlx->posX + mlx->dirY * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX -= mlx->dirY * mlx->moveSpeed;
		if (!worldMap[(int)mlx->posX][(int)(mlx->posY + mlx->dirX * mlx->moveSpeed)])
			mlx->posY += mlx->dirX * mlx->moveSpeed;
	}
	if (keycode == KEY_LEFT)
	{
		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(mlx->rotSpeed) - mlx->dirY * sin(mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(mlx->rotSpeed) + mlx->dirY * cos(mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(mlx->rotSpeed) - mlx->planeY * sin(mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(mlx->rotSpeed) + mlx->planeY * cos(mlx->rotSpeed);
	}
	if (keycode == KEY_RIGHT)
	{
		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(-mlx->rotSpeed) - mlx->dirY * sin(-mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(-mlx->rotSpeed) + mlx->dirY * cos(-mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(-mlx->rotSpeed) - mlx->planeY * sin(-mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(-mlx->rotSpeed) + mlx->planeY * cos(-mlx->rotSpeed);
	}
	mlx_destroy_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, SW, SH);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	return (0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void floor_ceiling(t_mlx *mlx)
{
	int	x;
	int y;

	y = SH / 2 + 1;
	
	while (y < SH)
	{
		mlx->rayDirX0 = mlx->dirX - mlx->planeX;
		mlx->rayDirY0 = mlx->dirY - mlx->planeY;
		mlx->rayDirX1 = mlx->dirX + mlx->planeX;
		mlx->rayDirY1 = mlx->dirY + mlx->planeY;

		mlx->p = y - SH / 2;

		mlx->posZ = 0.5 * SH;
		mlx->rowDistance = mlx->posZ / mlx->p;

		mlx->floorStepX = mlx->rowDistance * (mlx->rayDirX1 - mlx->rayDirX0) / SW;
		mlx->floorStepY = mlx->rowDistance * (mlx->rayDirY1 - mlx->rayDirY0) / SW;

		mlx->floorX = mlx->posX + mlx->rowDistance * mlx->rayDirX0;
		mlx->floorY = mlx->posY + mlx->rowDistance * mlx->rayDirY0;

		x = 0;
		while (x < SW)
		{
			mlx->cellX = (int)(mlx->floorX);
			mlx->cellY = (int)(mlx->floorY);
			mlx->tx = (int)(TEXTW * (mlx->floorX - mlx->cellX)) & (TEXTW - 1);
			mlx->ty = (int)(TEXTH * (mlx->floorY - mlx->cellY)) & (TEXTH - 1);

			mlx->floorX += mlx->floorStepX;
			mlx->floorY += mlx->floorStepY;


			mlx->color = 0xFFFFFF;

			my_mlx_pixel_put(mlx, x, y, mlx->color);
			mlx->color = 0x0000FF;

			my_mlx_pixel_put(mlx, x, SH - y - 1, mlx->color);

			x++;
		}

		y++;
	}
}

void walls(t_mlx *mlx)
{
	int	x;
	int y;

	x = 0;
	while (x < SW)
	{
		//calculate ray position and direction
		mlx->cameraX = 2 * x / (double)SW - 1;
		mlx->rayDirX = mlx->dirX + mlx->planeX * mlx->cameraX;
		mlx->rayDirY = mlx->dirY + mlx->planeY * mlx->cameraX;

		//which box of the map we're in
		mlx->mapX = (int)mlx->posX;
		mlx->mapY = (int)mlx->posY;

		//length of ray from one x or y-side to next x or y-side
		mlx->deltaDistX = fabs(1 / mlx->rayDirX);
		mlx->deltaDistY = fabs(1 / mlx->rayDirY);

		mlx->hit = 0;

		//calculate step and initial sideDist
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

		//perform DDA
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

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (mlx->side == 0)
			mlx->perpWallDist = (mlx->sideDistX - mlx->deltaDistX);
		else
			mlx->perpWallDist = (mlx->sideDistY - mlx->deltaDistY);

		//Calculate height of line to draw on screen
		mlx->lineHeight = (int)(SH / mlx->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		mlx->drawStart = -mlx->lineHeight / 2 + SH / 2;
		if (mlx->drawStart < 0)
			mlx->drawStart = 0;
		mlx->drawEnd = mlx->lineHeight / 2 + SH / 2;
		if (mlx->drawEnd >= SH)
			mlx->drawEnd = SH - 1;

		//texturing calculations
		mlx->texNum = worldMap[mlx->mapX][mlx->mapY] - 1;
		
		//calculate value of wallX
		if(mlx->side == 0)
			mlx->wallX = mlx->posY + mlx->perpWallDist * mlx->rayDirY;
		else
			mlx->wallX = mlx->posX + mlx->perpWallDist * mlx->rayDirX;
		mlx->wallX -= floor((mlx->wallX));
		
		//x coordinate on the texture
		mlx->texX = (int)(mlx->wallX * (double)(TEXTW));
		if(mlx->side == 0 && mlx->rayDirX > 0)
			mlx->texX = TEXTW - mlx->texX - 1;
		if(mlx->side == 1 && mlx->rayDirY < 0)
			mlx->texX = TEXTW - mlx->texX - 1;

		// How much to increase the texture coordinate per screen pixel
		mlx->step = 1.0 * TEXTH / mlx->lineHeight;

		// Starting texture coordinate
		mlx->texPos = (mlx->drawStart - SH / 2 + mlx->lineHeight / 2) * mlx->step;

		y = mlx->drawStart;
		while (y < mlx->drawEnd)
		{
			mlx->texY = (int)mlx->texPos & (TEXTH - 1);
        	mlx->texPos += mlx->step;

			if (mlx->side == 0 && mlx->rayDirX < 0)
				mlx->color = mlx->bluestone_addr[mlx->texY * TEXTH + mlx->texX];
			else if (mlx->side == 0 && mlx->rayDirX >= 0)
				mlx->color = mlx->greystone_addr[mlx->texY * TEXTH + mlx->texX];
			else if (mlx->side == 1 && mlx->rayDirY < 0)
				mlx->color = mlx->red_addr[mlx->texY * TEXTH + mlx->texX];
			else if (mlx->side == 1 && mlx->rayDirY >= 0)
				mlx->color = mlx->wood_addr[mlx->texY * TEXTH + mlx->texX];
			// int d = y * 256 - SH * 128 + mlx->lineHeight * 128;
			// mlx->texY = ((d * TEXTH) / mlx->lineHeight) / 256;
			// mlx->color = mlx->greystone_addr[mlx->texY * TEXTW + mlx->texX];
			
			my_mlx_pixel_put(mlx, x, y, mlx->color);
			y++;
		}
		x++;
	}
}

int	raycasting(t_mlx *mlx)
{
	floor_ceiling(mlx);
	walls(mlx);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win_ptr, mlx->img, 0, 0);
	return 0;
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
	mlx->moveSpeed = 1;
	mlx->rotSpeed = 0.5;
}

int	store_images(t_mlx *mlx)
{
	int		img_width;
	int		img_height;

	mlx->greystone = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/greystone.xpm", &img_width, &img_height);
	mlx->bluestone = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/bluestone.xpm", &img_width, &img_height);
	mlx->red = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/red.xpm", &img_width, &img_height);
	mlx->wood = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/wood.xpm", &img_width, &img_height);
	return (0);
}

int	store_images_addr(t_mlx *mlx)
{
	mlx->greystone_addr = (int *)mlx_get_data_addr(mlx->greystone, &mlx->bits_per_pixel_grey, &mlx->line_length_grey, &mlx->endian_grey);
	mlx->bluestone_addr = (int *)mlx_get_data_addr(mlx->bluestone, &mlx->bits_per_pixel_blue, &mlx->line_length_blue, &mlx->endian_blue);
	mlx->red_addr = (int *)mlx_get_data_addr(mlx->red, &mlx->bits_per_pixel_red, &mlx->line_length_red, &mlx->endian_red);
	mlx->wood_addr = (int *)mlx_get_data_addr(mlx->wood, &mlx->bits_per_pixel_wood, &mlx->line_length_wood, &mlx->endian_wood);
	return (0);
}

void	init_minilibx(t_mlx *mlx)
{
	mlx->mlx_p = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_p, SW, SH, "cub3d");
	mlx->img = mlx_new_image(mlx->mlx_p, SW, SH);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	store_images(mlx);
	store_images_addr(mlx);
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, &key_hook, mlx);
	mlx_loop_hook(mlx->mlx_p, raycasting, mlx);
	mlx_loop(mlx->mlx_p);
}

int	main(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	init_values(mlx);
	init_minilibx(mlx);
}
