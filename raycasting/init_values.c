/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:51:47 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 16:53:50 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player_direction(t_mlx *mlx)
{
	mlx->dirX = 0;
	mlx->dirY = 0;
	mlx->planeX = 0;
	mlx->planeY = 0;
	if (mlx->player_char == 'N')
	{
		mlx->dirX = -1;
		mlx->planeY = 0.66;
	}
	else if (mlx->player_char == 'S')
	{
		mlx->dirX = 1;
		mlx->planeY = -0.66;
	}
	else if (mlx->player_char == 'E')
	{
		mlx->dirY = 1;
		mlx->planeX = 0.66;
	}
	else if (mlx->player_char == 'W')
	{
		mlx->dirY = -1;
		mlx->planeX = -0.66;
	}
}

void	init_speed(t_mlx *mlx)
{
	mlx->moveSpeed = 1;
	mlx->rotSpeed = 0.5;
}
