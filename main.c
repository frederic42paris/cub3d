/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/08 18:25:29 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	check_textures(t_mlx *mlx)
// {
// 	int	i;
// 	int j;

// 	i = 0;
// 	while (i < 6)
// 	{
// 		j = 0;
// 		while (is_space(mlx->textures[i][j]))
// 			j++;
// 		if (check_text_id(mlx, (mlx->textures[i]) + j) == 1)
// 			return (1);
// 		if (check_text_path((mlx->textures[i]) + j) == 1)
// 			return (1);
// 		if (check_text_rgb((mlx->textures[i]) + j) == 1)
// 			return (1);
// 		i++;
// 	}
// 	if (check_text_dup(mlx) == 1)
// 		return (1);
// 	return (0);
// }

// int	check_map(t_mlx *mlx)
// {
// 	if (check_map_line(mlx) == 1)
// 		return (1);
// 	if (check_map_walls(mlx) == 1)
// 		return (1);
// 	if (check_map_character(mlx) == 1)
// 		return (1);
// 	if (check_map_players(mlx) == 1)
// 		return (1);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	t_mlx	*mlx;
	
// 	check_argument(argv[1], argc);
// 	mlx = malloc(sizeof(t_mlx));
// 	open_file(mlx, argv[1]);
// 	if (store_data(mlx) == 1)
// 		return (1);
// 	if (check_textures(mlx) == 1)
// 		return (1);
// 	// display_data(mlx);
// 	find_player(mlx);
// 	measure_map(mlx);
// 	store_map_one(mlx);
// 	if (check_map(mlx) == 1)
// 		return (1);
// 	store_textures(mlx);
// 	store_map(mlx);
// 	display_parsing(mlx);
// 	init_values(mlx);
// 	init_minilibx(mlx);
// 	return (0);
// }

int worldMap[5][10]=
{
{1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1}
};

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
			if (mlx->map_int[mlx->mapX][mlx->mapY] > 0)
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

		//choose wall color
		if (mlx->map_int[mlx->mapX][mlx->mapY] == 1)
			mlx->color = 0xFF0000;
		else if (mlx->map_int[mlx->mapX][mlx->mapY] == 2)
			mlx->color = 0x00FF00;
		else if (mlx->map_int[mlx->mapX][mlx->mapY] == 3)
			mlx->color = 0x0000FF;
		else if (mlx->map_int[mlx->mapX][mlx->mapY] == 4)
			mlx->color = 0xFFFFFF;
		else
			mlx->color = 0xFFFF00;

		//give x and y sides different brightness
		if (mlx->side == 1)
			mlx->color = mlx->color / 2;

		//draw the pixels of the stripe as a vertical line
		draw_vertical_line(mlx, x);
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
		if (!mlx->map_int[(int)(mlx->posX + mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX += mlx->dirX * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY + mlx->dirY * mlx->moveSpeed)])
			mlx->posY += mlx->dirY * mlx->moveSpeed;
	}
	if (keycode == KEY_S)
	{

		if (!mlx->map_int[(int)(mlx->posX - mlx->dirX * mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX -= mlx->dirX * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY - mlx->dirY * mlx->moveSpeed)])
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
	// mlx->posX = 2;
	// mlx->posY = 2;
	mlx->dirX = 0;
	mlx->dirY = 1;
	mlx->planeX = 0.66;
	mlx->planeY = 0;
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
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, &key_hook, mlx);
	mlx_loop_hook(mlx->mlx_p, raycasting, mlx);
	mlx_loop(mlx->mlx_p);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	check_argument(argv[1], argc);
	mlx = malloc(sizeof(t_mlx));
	open_file(mlx, argv[1]);
	store_data(mlx);
	display_data(mlx);
	find_player(mlx);
	measure_map(mlx);
	store_map(mlx);
	display_parsing(mlx);
	
	init_values(mlx);
	start_game(mlx);
}

// int	main(int argc, char **argv)
// {
// 	t_mlx	*mlx;
	
// 	check_argument(argv[1], argc);
// 	mlx = malloc(sizeof(t_mlx));
// 	open_file(mlx, argv[1]);
// 	if (store_data(mlx) == 1)
// 		return (1);
// 	if (check_textures(mlx) == 1)
// 		return (1);
// 	// display_data(mlx);
// 	find_player(mlx);
// 	measure_map(mlx);
// 	store_map_one(mlx);
// 	if (check_map(mlx) == 1)
// 		return (1);
// 	store_textures(mlx);
// 	store_map(mlx);
// 	display_parsing(mlx);
// 	init_values(mlx);
// 	init_minilibx(mlx);
// 	return (0);
// }