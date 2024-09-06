/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:21:56 by arguez            #+#    #+#             */
/*   Updated: 2024/09/06 19:06:44 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	left_to_right(char **map)
{
	int	i;
	int	j;

	i = get_map_index(map);
	while (map[i] != NULL)
	{
		j = 0;
		while ((map[i][j] != '\n') && (map[i][j] != '\0'))
		{
			if ((map[i][j + 1] == '\n') || (map[i][j + 1] == '\0') 
				|| (map[i][j + 1] == ' '))
			{
				if (map[i][j] == '0')
					return (1);
				else
					break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	right_to_left(char **map)
{
	int	i;
	int	j;

	i = get_map_index(map);
	while (map[i] != NULL)
	{
		j = ft_strlen(map[i]);
		while (j >= 0)
		{
			if (right_to_left_subroutine(map, i, j) == 1)
				return (1);
			if (right_to_left_subroutine(map, i, j) == 0)
				break ;
			j--;
		}
		i++;
	}
	return (0);
}

static int	up_to_down(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = get_map_index(map);
	while ((map[i][j] != '\n') && (map[i][j] != '\0'))
	{
		i = get_map_index(map);
		while (map[i] != NULL)
		{
			if (up_to_down_subroutine(map, i, j) == 1)
				return (1);
			if (up_to_down_subroutine(map, i, j) == 0)
				break ;
			i++;
		}
		j++;
	}
	return (0);
}

static int	down_to_up(char **map)
{
	int	i;
	int	j;
	int end;

	j = 0;
	i = 0;
	end = 0;
	while (map[end] != NULL)
		end++;
	while ((map[i][j] != '\n') && (map[i][j] != '\0'))
	{
		i = end;
		while (i >= 0)
		{
			if (down_to_up_subroutine(map, i, j) == 1)
				return (1);
			if (down_to_up_subroutine(map, i, j) == 0)
				break ;
			i--;
		}
		j++;
	}
	return (0);
}

int	check_surrounded_map(char **map)
{
	int	errors;

	errors = 0;
	errors += left_to_right(map);
	errors += right_to_left(map);
	errors += up_to_down(map);
	errors += down_to_up(map);
	if (errors != 0)
		return (printf("Error: map is not surrounded by walls\n"), errors);
	return (0);
}
