/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:17:28 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 12:00:04 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	measure_map(t_mlx *mlx)
{
	int		i;
	int		j;
	int		width;

	width = 0;
	j = 0;
	while (mlx->map_char[j])
	{
		i = 0;
		while (mlx->map_char[j][i] != '\0')
		{
			i++;
			if (i > width)
				width++;
		}
		j++;
	}
	mlx->map_width = width;
	mlx->map_height = j;
}