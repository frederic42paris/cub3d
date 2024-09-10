/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:28:16 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 17:31:59 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_floor_ceiling_x(t_mlx *mlx, int y)
{
	int	x;

	x = 0;
	while (x < SW)
	{
		mlx->cell_x = (int)(mlx->floor_x);
		mlx->cell_y = (int)(mlx->floor_y);
		mlx->tx = (int)(TEXTW * (mlx->floor_x - mlx->cell_x)) & (TEXTW - 1);
		mlx->ty = (int)(TEXTH * (mlx->floor_y - mlx->cell_y)) & (TEXTH - 1);
		mlx->floor_x += mlx->floorstep_x;
		mlx->floor_y += mlx->floorstep_y;
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
		mlx->raydir_x_o = mlx->dir_x - mlx->plane_x;
		mlx->raydir_y_o = mlx->dir_y - mlx->plane_y;
		mlx->raydir_x_i = mlx->dir_x + mlx->plane_x;
		mlx->raydir_y_i = mlx->dir_y + mlx->plane_y;
		mlx->p = y - SH / 2;
		mlx->pos_z = 0.5 * SH;
		mlx->row_distance = mlx->pos_z / mlx->p;
		mlx->floorstep_x = mlx->row_distance * (mlx->raydir_x_i - mlx->raydir_x_o)
			/ SW;
		mlx->floorstep_y = mlx->row_distance * (mlx->raydir_y_i - mlx->raydir_y_o)
			/ SW;
		mlx->floor_x = mlx->pos_x + mlx->row_distance * mlx->raydir_x_o;
		mlx->floor_y = mlx->pos_y + mlx->row_distance * mlx->raydir_y_o;
		draw_floor_ceiling_x(mlx, y);
		y++;
	}
}
