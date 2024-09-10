/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:18:40 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 17:18:59 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_raydir(t_mlx *mlx, int x)
{
	mlx->hit = 0;
	mlx->cameraX = 2 * x / (double)SW - 1;
	mlx->rayDirX = mlx->dirX + mlx->planeX * mlx->cameraX;
	mlx->rayDirY = mlx->dirY + mlx->planeY * mlx->cameraX;
	mlx->mapX = (int)mlx->pos_x;
	mlx->mapY = (int)mlx->posY;
	mlx->deltaDistX = fabs(1 / mlx->rayDirX);
	mlx->deltaDistY = fabs(1 / mlx->rayDirY);
}

void	calculate_sidedist(t_mlx *mlx)
{
	if (mlx->rayDirX < 0)
	{
		mlx->stepX = -1;
		mlx->sideDistX = (mlx->pos_x - mlx->mapX) * mlx->deltaDistX;
	}
	else
	{
		mlx->stepX = 1;
		mlx->sideDistX = (mlx->mapX + 1.0 - mlx->pos_x) * mlx->deltaDistX;
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
}

void	calculate_distance(t_mlx *mlx)
{
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
	if (mlx->side == 0)
		mlx->perpWallDist = (mlx->sideDistX - mlx->deltaDistX);
	else
		mlx->perpWallDist = (mlx->sideDistY - mlx->deltaDistY);
}

void	calculate_wall(t_mlx *mlx)
{
	mlx->lineHeight = (int)(SH / mlx->perpWallDist);
	mlx->drawStart = -mlx->lineHeight / 2 + SH / 2;
	if (mlx->drawStart < 0)
		mlx->drawStart = 0;
	mlx->drawEnd = mlx->lineHeight / 2 + SH / 2;
	if (mlx->drawEnd >= SH)
		mlx->drawEnd = SH - 1;
}

void	draw_walls(t_mlx *mlx)
{
	int	x;

	x = 0;
	while (x < SW)
	{
		calculate_raydir(mlx, x);
		calculate_sidedist(mlx);
		calculate_distance(mlx);
		calculate_wall(mlx);
		calculate_texture(mlx, x);
		x++;
	}
}
