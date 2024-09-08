/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:18:26 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/08 12:48:49 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_map_line(t_mlx *mlx)
{
	int i;

	i = 0;
	while (mlx->map_char[i])
	{
		if (has_alpha_num(mlx->map_char[i]) == 0)
		{
			printf("Error\nMap has empty line\n");
			return (1);
		}
		i++;
	}
	return (0);
}