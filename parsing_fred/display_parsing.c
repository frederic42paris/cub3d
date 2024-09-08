/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:23:34 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/08 18:41:48 by ftanon           ###   ########.fr       */
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
	while(i < mlx->map_width)
	{
		j = 0;
		while(j < mlx->map_height)
		{
			printf("%d", mlx->map_int[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void check_map_int_one(t_mlx *mlx)
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
			printf("%d", mlx->map_int_one[i][j]);
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
	check_map_char(mlx);
	printf("----------\n");
	printf("%f\n", mlx->posX);
	printf("%f\n", mlx->posY);
	printf("----------\n");
	printf("%d\n", mlx->map_width);
	printf("%d\n", mlx->map_height);
	// printf("----------\n");
	// check_map_int_one(mlx);
	printf("----------\n");
	check_map_int(mlx);
}

void	display_data(t_mlx *mlx)
{
	int k;
	k = 0;
	while(k < 6)
	{
		printf("[%s]\n", mlx->textures[k]);
		k++;
	}
	k = 0;
	while (mlx->map_char[k])
	{
		printf("[%s]\n", mlx->map_char[k]);
		k++;
	}
}