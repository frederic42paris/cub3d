/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:39:18 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 16:47:27 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_LEFT)
	{
		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(mlx->rotSpeed) - mlx->dirY
			* sin(mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(mlx->rotSpeed) + mlx->dirY
			* cos(mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(mlx->rotSpeed) - mlx->planeY
			* sin(mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(mlx->rotSpeed) + mlx->planeY
			* cos(mlx->rotSpeed);
	}
}

void	rotate_right(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_RIGHT)
	{
		mlx->oldDirX = mlx->dirX;
		mlx->dirX = mlx->dirX * cos(-mlx->rotSpeed) - mlx->dirY
			* sin(-mlx->rotSpeed);
		mlx->dirY = mlx->oldDirX * sin(-mlx->rotSpeed) + mlx->dirY
			* cos(-mlx->rotSpeed);
		mlx->oldPlaneX = mlx->planeX;
		mlx->planeX = mlx->planeX * cos(-mlx->rotSpeed) - mlx->planeY
			* sin(-mlx->rotSpeed);
		mlx->planeY = mlx->oldPlaneX * sin(-mlx->rotSpeed) + mlx->planeY
			* cos(-mlx->rotSpeed);
	}
}

void	move_left_right(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_D)
	{
		if (!mlx->map_int[(int)(mlx->posX + mlx->dirY
				* mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX += mlx->dirY * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY - mlx->dirX
			* mlx->moveSpeed)])
			mlx->posY -= mlx->dirX * mlx->moveSpeed;
	}
	if (keycode == KEY_A)
	{
		if (!mlx->map_int[(int)(mlx->posX + mlx->dirY
				* mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX -= mlx->dirY * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY + mlx->dirX
			* mlx->moveSpeed)])
			mlx->posY += mlx->dirX * mlx->moveSpeed;
	}
}

void	move_up_down(t_mlx *mlx, int keycode)
{
	if (keycode == KEY_W)
	{
		if (!mlx->map_int[(int)(mlx->posX + mlx->dirX
				* mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX += mlx->dirX * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY + mlx->dirY
			* mlx->moveSpeed)])
			mlx->posY += mlx->dirY * mlx->moveSpeed;
	}
	if (keycode == KEY_S)
	{
		if (!mlx->map_int[(int)(mlx->posX - mlx->dirX
				* mlx->moveSpeed)][(int)mlx->posY])
			mlx->posX -= mlx->dirX * mlx->moveSpeed;
		if (!mlx->map_int[(int)mlx->posX][(int)(mlx->posY - mlx->dirY
			* mlx->moveSpeed)])
			mlx->posY -= mlx->dirY * mlx->moveSpeed;
	}
}
