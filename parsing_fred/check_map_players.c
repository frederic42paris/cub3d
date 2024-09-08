/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:27:09 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/08 13:33:15 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_map_players(t_mlx *mlx)
{
	int i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (mlx->map_char[i])
	{
		j = 0;
		while (mlx->map_char[i][j])
		{
			if (mlx->map_char[i][j] == 'N'
				|| mlx->map_char[i][j] == 'S'
				|| mlx->map_char[i][j] == 'E'
				|| mlx->map_char[i][j] == 'W'
			)
				counter++;
			j++;
		}
		i++;
	}
	if (counter > 1)
	{
		printf("Error\nNumber of players incorrect\n");
		return (1);
	}
	return (0);
}