/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:10:31 by arguez            #+#    #+#             */
/*   Updated: 2024/09/10 16:10:50 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_empty(t_mlx *mlx, char *temp, char *concat)
{
	int	i;

	i = 0;
	if (concat[0] == '\0')
	{
		printf("Error\nEmpty map\n");
		free(temp);
		return (1);
	}
	while (concat[i] != '\0')
	{
		if (concat[i] == '\n' && concat[i + 1] == '\n')
		{
			printf("Error\nEmpty line in map\n");
			free(temp);
			return (1);
		}
		i++;
	}
	mlx->map_char = ft_split(concat, '\n');
	free(concat);
	return (0);
}
