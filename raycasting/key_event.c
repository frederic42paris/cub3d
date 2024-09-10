/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:39:18 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 17:27:55 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_LEFT)
	{
		mlx->olddir_x = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(mlx->rot_speed) - mlx->dir_y
			* sin(mlx->rot_speed);
		mlx->dir_y = mlx->olddir_x * sin(mlx->rot_speed) + mlx->dir_y
			* cos(mlx->rot_speed);
		mlx->oldplane_x = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(mlx->rot_speed) - mlx->plane_y
			* sin(mlx->rot_speed);
		mlx->plane_y = mlx->oldplane_x * sin(mlx->rot_speed) + mlx->plane_y
			* cos(mlx->rot_speed);
	}
}

void	rotate_right(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_RIGHT)
	{
		mlx->olddir_x = mlx->dir_x;
		mlx->dir_x = mlx->dir_x * cos(-mlx->rot_speed) - mlx->dir_y
			* sin(-mlx->rot_speed);
		mlx->dir_y = mlx->olddir_x * sin(-mlx->rot_speed) + mlx->dir_y
			* cos(-mlx->rot_speed);
		mlx->oldplane_x = mlx->plane_x;
		mlx->plane_x = mlx->plane_x * cos(-mlx->rot_speed) - mlx->plane_y
			* sin(-mlx->rot_speed);
		mlx->plane_y = mlx->oldplane_x * sin(-mlx->rot_speed) + mlx->plane_y
			* cos(-mlx->rot_speed);
	}
}

void	move_left_right(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_D)
	{
		if (!mlx->map_int[(int)(mlx->pos_x + mlx->dir_y
				* mlx->move_speed)][(int)mlx->pos_y])
			mlx->pos_x += mlx->dir_y * mlx->move_speed;
		if (!mlx->map_int[(int)mlx->pos_x][(int)(mlx->pos_y - mlx->dir_x
			* mlx->move_speed)])
			mlx->pos_y -= mlx->dir_x * mlx->move_speed;
	}
	if (keycode == KEY_A)
	{
		if (!mlx->map_int[(int)(mlx->pos_x + mlx->dir_y
				* mlx->move_speed)][(int)mlx->pos_y])
			mlx->pos_x -= mlx->dir_y * mlx->move_speed;
		if (!mlx->map_int[(int)mlx->pos_x][(int)(mlx->pos_y + mlx->dir_x
			* mlx->move_speed)])
			mlx->pos_y += mlx->dir_x * mlx->move_speed;
	}
}

void	move_up_down(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_W)
	{
		if (!mlx->map_int[(int)(mlx->pos_x + mlx->dir_x
				* mlx->move_speed)][(int)mlx->pos_y])
			mlx->pos_x += mlx->dir_x * mlx->move_speed;
		if (!mlx->map_int[(int)mlx->pos_x][(int)(mlx->pos_y + mlx->dir_y
			* mlx->move_speed)])
			mlx->pos_y += mlx->dir_y * mlx->move_speed;
	}
	if (keycode == KEY_S)
	{
		if (!mlx->map_int[(int)(mlx->pos_x - mlx->dir_x
				* mlx->move_speed)][(int)mlx->pos_y])
			mlx->pos_x -= mlx->dir_x * mlx->move_speed;
		if (!mlx->map_int[(int)mlx->pos_x][(int)(mlx->pos_y - mlx->dir_y
			* mlx->move_speed)])
			mlx->pos_y -= mlx->dir_y * mlx->move_speed;
	}
}
