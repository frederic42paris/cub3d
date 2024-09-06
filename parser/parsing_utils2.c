/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:56:52 by arguez            #+#    #+#             */
/*   Updated: 2024/09/06 17:31:29 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while ((line[i] != '\n') && (line[i] != '\0'))
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	is_tag(char *tag)
{
	if (ft_strncmp(tag, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(tag, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(tag, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(tag, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(tag, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(tag, "C ", 2) == 0)
		return (1);
	return (0);
}

int get_map_index(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if ((is_empty_line(map[i]) == 0) && (is_tag(get_tag(map[i])) == 0))
			return (i);
		i++;
	}
	return (-1);
}

int	get_map_size(char **map, t_mlx *mlx)
{
	int	i;

	i = get_map_index(map);
	if (i == -1)
		return (printf("Error: map data missing\n"), 1);
	mlx->map_height = 0;
	mlx->map_width = 0;
	while (map[i] != NULL)
	{
		mlx->map_height++;
		if (ft_strlen(map[i]) > mlx->map_width)
			mlx->map_width = ft_strlen(map[i]);
		i++;
	}
	if ((mlx->map_width < 3) || (mlx->map_height < 3))
		return (printf("Error: map too small (must be at least 2x2)\n"), 1);
	return (0);
}

void	map_filler(t_mlx *mlx, char **map)
{
	int	i;
	int	j;
	int	k;

	i = get_map_index(map);
	k = 0;
	while (map[i] != NULL)
	{
		j = 0;
		mlx->map_int[k] = malloc (mlx->map_width * sizeof(int));
		while (map[i][j] != '\n')
		{
			mlx->map_int[k][j] = get_map_tile(map[i][j]);
			j++;
		}
		i++;
		k++;
	}
}
