/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:16:10 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 16:39:10 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_empty(t_mlx *mlx, int i, int j, int k)
{
	while (j < mlx->map_height)
	{
		mlx->map_int[i][j] = k;
		j++;
	}
}

void	fill_empty_one(t_mlx *mlx, int i, int j, int k)
{
	while (j < mlx->map_height)
	{
		mlx->map_int_one[i][j] = k;
		j++;
	}
}

int	store_map(t_mlx *mlx)
{
	static int	i = 0;
	int			j;

	mlx->map_int = malloc(sizeof(int *) * (mlx->map_width));
	while (i < mlx->map_width)
	{
		mlx->map_int[i] = malloc(sizeof(int) * (mlx->map_height));
		j = 0;
		while (j < mlx->map_height)
		{
			if (is_player_character(mlx->map_char[i][j]) == 1)
				mlx->map_int[i][j] = 0;
			else if (mlx->map_char[i][j] == ' ')
				mlx->map_int[i][j] = 1;
			else if (mlx->map_char[i][j] == '\0')
			{
				fill_empty(mlx, i, j, 1);
				break ;
			}
			else
				mlx->map_int[i][j] = mlx->map_char[i][j] - '0';
			j++;
		}
		i++;
	}
	return (0);
}

int	store_map_one(t_mlx *mlx)
{
	static int	i = 0;
	int			j;

	mlx->map_int_one = malloc(sizeof(int *) * (mlx->map_width));
	while (i < mlx->map_width)
	{
		mlx->map_int_one[i] = malloc(sizeof(int) * (mlx->map_height));
		j = 0;
		while (j < mlx->map_height)
		{
			if (is_player_character(mlx->map_char[i][j]) == 1)
				mlx->map_int_one[i][j] = 0;
			else if (mlx->map_char[i][j] == ' ')
				mlx->map_int_one[i][j] = 2;
			else if (mlx->map_char[i][j] == '\0')
			{
				fill_empty_one(mlx, i, j, 2);
				break ;
			}
			else
				mlx->map_int_one[i][j] = mlx->map_char[i][j] - '0';
			j++;
		}
		i++;
	}
	return (0);
}
