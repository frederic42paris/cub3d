/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:16:10 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 12:08:05 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	store_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	mlx->map_int = malloc(sizeof(int *) * (mlx->map_height));
	while (i < mlx->map_height)
	{
		mlx->map_int[i] = malloc(sizeof(int) * (mlx->map_width));
		j = 0;
		while (j < mlx->map_width)
		{
			if (mlx->map_char[i][j] == 'N')
				mlx->map_int[i][j] = 2;
			else if (mlx->map_char[i][j] == ' ')
				mlx->map_int[i][j] = 1;
			else if (mlx->map_char[i][j] == '\0')
				mlx->map_int[i][j] = 1;
			else
				mlx->map_int[i][j] = mlx->map_char[i][j] - '0';
			j++;
		}
		i++;
	}
	return (0);
}