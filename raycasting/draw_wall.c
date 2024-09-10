/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:18:40 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 17:28:37 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_raydir(t_mlx *mlx, int x)
{
	mlx->hit = 0;
	mlx->camera_x = 2 * x / (double)SW - 1;
	mlx->raydir_x = mlx->dir_x + mlx->plane_x * mlx->camera_x;
	mlx->raydir_y = mlx->dir_y + mlx->plane_y * mlx->camera_x;
	mlx->map_x = (int)mlx->pos_x;
	mlx->map_y = (int)mlx->pos_y;
	mlx->delta_dist_x = fabs(1 / mlx->raydir_x);
	mlx->delta_dist_y = fabs(1 / mlx->raydir_y);
}

void	calculate_sidedist(t_mlx *mlx)
{
	if (mlx->raydir_x < 0)
	{
		mlx->step_x = -1;
		mlx->side_dist_x = (mlx->pos_x - mlx->map_x) * mlx->delta_dist_x;
	}
	else
	{
		mlx->step_x = 1;
		mlx->side_dist_x = (mlx->map_x + 1.0 - mlx->pos_x) * mlx->delta_dist_x;
	}
	if (mlx->raydir_y < 0)
	{
		mlx->step_y = -1;
		mlx->side_dist_y = (mlx->pos_y - mlx->map_y) * mlx->delta_dist_y;
	}
	else
	{
		mlx->step_y = 1;
		mlx->side_dist_y = (mlx->map_y + 1.0 - mlx->pos_y) * mlx->delta_dist_y;
	}
}

void	calculate_distance(t_mlx *mlx)
{
	while (mlx->hit == 0)
	{
		if (mlx->side_dist_x < mlx->side_dist_y)
		{
			mlx->side_dist_x += mlx->delta_dist_x;
			mlx->map_x += mlx->step_x;
			mlx->side = 0;
		}
		else
		{
			mlx->side_dist_y += mlx->delta_dist_y;
			mlx->map_y += mlx->step_y;
			mlx->side = 1;
		}
		if (mlx->map_int[mlx->map_x][mlx->map_y] > 0)
			mlx->hit = 1;
	}
	if (mlx->side == 0)
		mlx->perp_wall_dist = (mlx->side_dist_x - mlx->delta_dist_x);
	else
		mlx->perp_wall_dist = (mlx->side_dist_y - mlx->delta_dist_y);
}

void	calculate_wall(t_mlx *mlx)
{
	mlx->line_height = (int)(SH / mlx->perp_wall_dist);
	mlx->draw_start = -mlx->line_height / 2 + SH / 2;
	if (mlx->draw_start < 0)
		mlx->draw_start = 0;
	mlx->draw_end = mlx->line_height / 2 + SH / 2;
	if (mlx->draw_end >= SH)
		mlx->draw_end = SH - 1;
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
