/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:37:50 by arguez            #+#    #+#             */
/*   Updated: 2024/09/06 18:56:02 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	right_to_left_subroutine(char **map, int i, int j)
{
	if (j == 0)
	{
		if (map[i][j] == '0')
			return (1);
		return (0);
	}
	if (map[i][j - 1] == ' ')
	{
		if (map[i][j] == '0')
			return (1);
		return (0);
	}
	return (2);
}

int	up_to_down_subroutine(char **map, int i, int j)
{
	if (map[i + 1] == NULL)
	{
		if (map[i][j] == '0')
			return (1);
		return (0);
	}
	if (map[i + 1][j] == ' ')
	{
		if (map[i][j] == '0')
			return (1);
		return (0);
	}
	return (2);
}
