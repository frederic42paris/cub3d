/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:56:18 by arguez            #+#    #+#             */
/*   Updated: 2024/09/06 18:20:36 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_startpos(t_mlx *mlx, char **map)
{
	int	i;
	int	j;
	int	n;

	i = get_map_index(map);
	n = 0;
	while (map[i] != NULL)
	{
		j = 0;
		if ((map[i][j] == 'N') || (map[i][j] == 'S') || (map[i][j] == 'E')
			|| (map[i][j] == 'W'))
		{
			n++;
			mlx->posX = j;
			mlx->posY = i;
		}
		i++;
	}
	if (n != 1)
		return (printf("Error: map must have exactly 1 starting position\n"), 1);
	return (0);
}

static int	check_map_symbols(char **map)
{
	int	i;
	int	j;

	i = get_map_index(map);
	while (map[i] != NULL)
	{
		j = 0;
		while ((map[i][j] != '\n') && (map[i][j] != '\0'))
		{
			if ((map[i][j] != '1') && (map[i][j] != '0') && (map[i][j] != 'N')
				&& (map[i][j] != 'S') && (map[i][j] != 'E') && (map[i][j] != 'W'))
				return (printf("Error: invalid symbols in map\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_empty_lines(char **map)
{
	int	i;

	i = get_map_index(map);
	while (map[i] != NULL)
	{
		if (is_empty_line(map[i]) == 1)
			return (printf("Error: empty lines in map detected\n"), 1);
		i++;
	}
	return (0);
}

int	check_valid_map(t_mlx *mlx, char **map)
{
	int	errors;

	errors = 0;
	errors += check_startpos(mlx, map);
	errors += check_map_symbols(map);
	errors += check_empty_lines(map);
	errors += check_surrounded_map(map);
	return (errors);
}
