/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:59:37 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 15:53:32 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_player(t_mlx *mlx)
{
	int	i;
	int	j;

	mlx->hasplayer = 0;
	j = 0;
	while (mlx->map_char[j])
	{
		i = 0;
		while (mlx->map_char[j][i] != '\0')
		{
			if (is_player_character(mlx->map_char[j][i]) == 1)
			{
				mlx->posX = j;
				mlx->posY = i;
				mlx->player_char = mlx->map_char[j][i];
				return ;
			}
			i++;
		}
		j++;
	}
}
