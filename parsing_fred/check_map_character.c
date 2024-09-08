/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:27:09 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/08 13:33:10 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_map_character(t_mlx *mlx)
{
	int i;
	int	j;

	i = 0;
	while (mlx->map_char[i])
	{
		j = 0;
		while (mlx->map_char[i][j])
		{
			if (mlx->map_char[i][j] != '0'
				&& mlx->map_char[i][j] != '1'
				&& mlx->map_char[i][j] != 'N'
				&& mlx->map_char[i][j] != 'S'
				&& mlx->map_char[i][j] != 'E'
				&& mlx->map_char[i][j] != 'W'
				&& mlx->map_char[i][j] != ' '
			)
			{
				printf("Error\nMap character incorrect\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}