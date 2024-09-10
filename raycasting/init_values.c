/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:51:47 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 17:27:55 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player_direction(t_mlx *mlx)
{
	mlx->dir_x = 0;
	mlx->dir_y = 0;
	mlx->plane_x = 0;
	mlx->plane_y = 0;
	if (mlx->player_char == 'N')
	{
		mlx->dir_x = -1;
		mlx->plane_y = 0.66;
	}
	else if (mlx->player_char == 'S')
	{
		mlx->dir_x = 1;
		mlx->plane_y = -0.66;
	}
	else if (mlx->player_char == 'E')
	{
		mlx->dir_y = 1;
		mlx->plane_x = 0.66;
	}
	else if (mlx->player_char == 'W')
	{
		mlx->dir_y = -1;
		mlx->plane_x = -0.66;
	}
}

void	init_speed(t_mlx *mlx)
{
	mlx->move_speed = 1;
	mlx->rot_speed = 0.5;
}
