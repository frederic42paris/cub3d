/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 18:49:59 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_textures(t_mlx *mlx)
{
	int	i;
	int j;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (is_space(mlx->textures[i][j]))
			j++;
		if (check_identifier(mlx, (mlx->textures[i]) + j) == 1)
			return (1);
		if (check_path((mlx->textures[i]) + j) == 1)
			return (1);
		if (check_rgb((mlx->textures[i]) + j) == 1)
			return (1);
		i++;
	}
	if (check_duplicates(mlx) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	
	check_argument(argv[1], argc);
	mlx = malloc(sizeof(t_mlx));
	open_file(mlx, argv[1]);
	if (store_data(mlx) == 1)
		return (1);
	// if (check_textures(mlx) == 1)
		// return (1);
	// display_data(mlx);
	
	find_player(mlx);
	measure_map(mlx);
	store_map_one(mlx);
	check_map_walls_x(mlx);
	check_map_walls_y(mlx);
	store_textures(mlx);
	store_map(mlx);
	display_parsing(mlx);
	return (0);
}
