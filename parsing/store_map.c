/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:16:10 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/11 12:29:53 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	conditions_map(t_mlx *mlx, int i, int j)
{
	if (is_player_character(mlx->map_char[i][j]) == 1)
		mlx->map_int[i][j] = 0;
	else if (mlx->map_char[i][j] == ' ')
		mlx->map_int[i][j] = 1;
	else if (mlx->map_char[i][j] == '\0')
	{
		while (j < mlx->map_height)
		{
			mlx->map_int[i][j] = 1;
			j++;
		}
		return (1);
	}
	else
		mlx->map_int[i][j] = mlx->map_char[i][j] - '0';
	return (0);
}

void	store_map(t_mlx *mlx)
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
			if (conditions_map(mlx, i, j) == 1)
				break;
			j++;
		}
		i++;
	}
}

int	conditions_midmap(t_mlx *mlx, int i, int j)
{
	if (is_player_character(mlx->map_char[i][j]) == 1)
		mlx->map_intermediate[i][j] = 0;
	else if (mlx->map_char[i][j] == ' ')
		mlx->map_intermediate[i][j] = 2;
	else if (mlx->map_char[i][j] == '\0')
	{
		while (j < mlx->map_height)
		{
			mlx->map_intermediate[i][j] = 2;
			j++;
		}
		return (1);
	}
	else
		mlx->map_intermediate[i][j] = mlx->map_char[i][j] - '0';
	return (0);
}

void	store_midmap(t_mlx *mlx)
{
	static int	i = 0;
	int			j;

	mlx->map_intermediate = malloc(sizeof(int *) * (mlx->map_width));
	while (i < mlx->map_width)
	{
		mlx->map_intermediate[i] = malloc(sizeof(int) * (mlx->map_height));
		j = 0;
		while (j < mlx->map_height)
		{
			if (conditions_midmap(mlx, i, j) == 1)
				break;
			j++;
		}
		i++;
	}
}
