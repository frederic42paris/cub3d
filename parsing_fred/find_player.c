/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:59:37 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/08 18:15:59 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_player(t_mlx *mlx)
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
			if (mlx->map_char[j][i] == 'N')
			{
				mlx->posX = j;
				mlx->posY = i;
			}
			i++;
		}
		j++;
	}
}