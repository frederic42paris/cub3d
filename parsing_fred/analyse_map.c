/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:17:28 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 12:17:29 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_player(t_mlx *mlx, int i, int j)
{
	if (mlx->map_char[j][i] == 'N')
	{
		mlx->posX = i;
		mlx->posY = j;
		mlx->hasplayer++;
	}
}

void	measure_map(t_mlx *mlx, int i, int j)
{
	mlx->map_width = i;
	mlx->map_height = j;
}

void	analyse_map(t_mlx *mlx)
{
	int		i;
	int		j;

	mlx->hasplayer = 0;
	j = 0;
	while (mlx->map_char[j])
	{
		i = 0;
		while (mlx->map_char[j][i] != '\0')
		{
			find_player(mlx, i, j);
			i++;
		}
		j++;
	}
	measure_map(mlx, i, j);
}