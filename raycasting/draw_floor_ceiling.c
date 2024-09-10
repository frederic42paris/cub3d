/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:28:16 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 16:49:48 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_floor_ceiling_x(t_mlx *mlx, int y)
{
	int	x;

	x = 0;
	while (x < SW)
	{
		mlx->cellX = (int)(mlx->floorX);
		mlx->cellY = (int)(mlx->floorY);
		mlx->tx = (int)(TEXTW * (mlx->floorX - mlx->cellX)) & (TEXTW - 1);
		mlx->ty = (int)(TEXTH * (mlx->floorY - mlx->cellY)) & (TEXTH - 1);
		mlx->floorX += mlx->floorStepX;
		mlx->floorY += mlx->floorStepY;
		mlx->color = mlx->floor_color;
		my_mlx_pixel_put(mlx, x, y, mlx->color);
		mlx->color = mlx->ceiling_color;
		my_mlx_pixel_put(mlx, x, SH - y - 1, mlx->color);
		x++;
	}
}

void	draw_floor_ceiling(t_mlx *mlx)
{
	int	y;

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
		mlx->floorStepX = mlx->rowDistance * (mlx->rayDirX1 - mlx->rayDirX0)
			/ SW;
		mlx->floorStepY = mlx->rowDistance * (mlx->rayDirY1 - mlx->rayDirY0)
			/ SW;
		mlx->floorX = mlx->posX + mlx->rowDistance * mlx->rayDirX0;
		mlx->floorY = mlx->posY + mlx->rowDistance * mlx->rayDirY0;
		draw_floor_ceiling_x(mlx, y);
		y++;
	}
}
