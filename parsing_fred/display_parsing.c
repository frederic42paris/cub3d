/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:23:34 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 11:21:55 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void check_map_char(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(mlx->map_char[i])
	{
		j = 0;
		while(mlx->map_char[i][j])
		{
			printf("%c", mlx->map_char[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void check_map_int(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < mlx->map_height)
	{
		j = 0;
		while(j < mlx->map_width)
		{
			printf("%d", mlx->map_int[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	display_parsing(t_mlx *mlx)
{
	printf("%s\n", mlx->path_north);
	printf("%s\n", mlx->path_south);
	printf("%s\n", mlx->path_east);
	printf("%s\n", mlx->path_west);
	printf("----------\n");
	printf("%d\n", mlx->floor_r);
	printf("%d\n", mlx->floor_g);
	printf("%d\n", mlx->floor_b);
	printf("%d\n", mlx->ceiling_r);
	printf("%d\n", mlx->ceiling_g);
	printf("%d\n", mlx->ceiling_b);
	printf("----------\n");
	// check_map_char(mlx);
	// printf("----------\n");
	printf("%d\n", mlx->map_width);
	printf("%d\n", mlx->map_height);
	printf("%f\n", mlx->posX);
	printf("%f\n", mlx->posY);
	printf("----------\n");
	check_map_int(mlx);
}