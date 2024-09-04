/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/04 13:03:47 by ftanon           ###   ########.fr       */
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

	void	*eagle;
	void	*redbrick;
	void	*purplestone;
	void	*greystone;
	void	*bluestone;
	void	*mossy;
	void	*wood;
	void	*colorstone;

	void	*eagle_addr;
	void	*redbrick_addr;
	void	*purplestone_addr;
	void	*greystone_addr;
	void	*bluestone_addr;
	void	*mossy_addr;
	void	*wood_addr;
	void	*colorstone_addr;

	int		texNum;
	double	wallX;
	int 	texX;
	double 	step;
	double	texPos;
	int		texY;
	int		bits_per_pixel_text;
	int		line_length_text;
	int		endian_text;
}	t_mlx;

int	store_images(t_mlx *mlx)
{
	int		img_width;
	int		img_height;

	// mlx->eagle = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/eagle.xpm", &img_width, &img_height);
	// mlx->redbrick = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/redbrick.xpm", &img_width, &img_height);
	// mlx->purplestone = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/purplestone.xpm", &img_width, &img_height);
	mlx->greystone = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/greystone.xpm", &img_width, &img_height);
	// mlx->bluestone = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/bluestone.xpm", &img_width, &img_height);
	// mlx->mossy = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/mossy.xpm", &img_width, &img_height);
	// mlx->wood = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/wood.xpm", &img_width, &img_height);
	// mlx->colorstone = mlx_xpm_file_to_image(mlx->mlx_p, "./textures/colorstone.xpm", &img_width, &img_height);
	return (0);
}

int	store_images_addr(t_mlx *mlx)
{
	// mlx->eagle_addr = mlx_get_data_addr(mlx->eagle, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	// mlx->redbrick_addr = mlx_get_data_addr(mlx->redbrick, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	// mlx->purplestone_addr = mlx_get_data_addr(mlx->purplestone, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	mlx->greystone_addr = mlx_get_data_addr(mlx->greystone, &mlx->bits_per_pixel_text, &mlx->line_length_text, &mlx->endian_text);
	// mlx->bluestone_addr = mlx_get_data_addr(mlx->bluestone, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	// mlx->mossy_addr = mlx_get_data_addr(mlx->mossy, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	// mlx->wood_addr = mlx_get_data_addr(mlx->wood, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	// mlx->colorstone_addr = mlx_get_data_addr(mlx->colorstone, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	return (0);
}

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

int buffer[SH][SW];
int texture[8];

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_vertical_line(t_mlx *mlx, int x)
{
	int	y;

	y = mlx->drawStart;
	while (y <= mlx->drawEnd)
	{
		my_mlx_pixel_put(mlx, x, y, mlx->color);
		y++;
	}
}

int	raycasting(t_mlx *mlx)
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
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			mlx->texY = (int)mlx->texPos & (TEXTH - 1);
        	mlx->texPos += mlx->step;
			mlx->color = *(unsigned int*)(mlx->greystone_addr + (TEXTH * mlx->texY + mlx->texX));
			
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(mlx->side == 1)
				mlx->color = (mlx->color >> 1) & 8355711;
	
			my_mlx_pixel_put(mlx, x, y, mlx->color);
			y++;
		}

		// //choose wall color
		// if (worldMap[mlx->mapX][mlx->mapY] == 1)
		// 	mlx->color = 0xFF0000;
		// else if (worldMap[mlx->mapX][mlx->mapY] == 2)
		// 	mlx->color = 0x00FF00;
		// else if (worldMap[mlx->mapX][mlx->mapY] == 3)
		// 	mlx->color = 0x0000FF;
		// else if (worldMap[mlx->mapX][mlx->mapY] == 4)
		// 	mlx->color = 0xFFFFFF;
		// else
		// 	mlx->color = 0xFFFF00;

		// //give x and y sides different brightness
		// if (mlx->side == 1)
		// 	mlx->color = mlx->color / 2;

		// //draw the pixels of the stripe as a vertical line
		// draw_vertical_line(mlx, x);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_p, mlx->win_ptr, mlx->img, 0, 0);
	return 0;
}

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
	if (keycode == KEY_A)
	{

		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(mlx->rotSpeed) - mlx->dirY * sin(mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(mlx->rotSpeed) + mlx->dirY * cos(mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(mlx->rotSpeed) - mlx->planeY * sin(mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(mlx->rotSpeed) + mlx->planeY * cos(mlx->rotSpeed);
	}
	if (keycode == KEY_D)
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

void	start_game(t_mlx *mlx)
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
	start_game(mlx);
}

// void clear_image(t_mlx *mlx)
// {
//     int x;
// 	int	y;
// 	// int color;

// 	x = 0;
// 	// color = 0x000000;
// 	while (x < SW)
// 	{
// 		y = 0;
// 		while (y <= SH)
// 		{
// 			my_mlx_pixel_put(mlx, x, y, 0);
// 			y++;
// 		}
// 		x++;
// 	}
// }