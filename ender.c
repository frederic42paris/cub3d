/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ender.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:27:07 by arguez            #+#    #+#             */
/*   Updated: 2024/09/09 17:42:23 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ending_subroutine(t_mlx *mlx)
{
	if (mlx->greystone != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->greystone);
	if (mlx->bluestone != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->bluestone);
	if (mlx->red != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->red);
	if (mlx->wood != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->wood);
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->img);
	if (mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_p, mlx->win_ptr);
	if (mlx->mlx_p != NULL)
		mlx_destroy_display(mlx->mlx_p);
}

void	ender(t_mlx *mlx)
{
	ending_subroutine(mlx);
	if (mlx->path_north != NULL)
		free(mlx->path_north);
	if (mlx->path_south != NULL)
		free(mlx->path_south);
	if (mlx->path_east != NULL)
		free(mlx->path_east);
	if (mlx->path_west != NULL)
		free(mlx->path_west);
	if (mlx->textures != NULL)
		double_free((void **)mlx->textures);
	if (mlx->map_char != NULL)
		double_free((void **)mlx->map_char);
	if (mlx->map_int != NULL)
		double_free_int(mlx->map_int, mlx);
	if (mlx->map_int_one != NULL)
		double_free_int(mlx->map_int_one, mlx);
	if (mlx->mlx_p != NULL)
		free(mlx->mlx_p);
	if (mlx->fd > 0)
		close(mlx->fd);
	free(mlx);
}
