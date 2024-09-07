/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 16:25:09 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	int	i;
	int j;

	i = 0;
	
	check_argument(argv[1], argc);
	mlx = malloc(sizeof(t_mlx));
	open_file(mlx, argv[1]);
	if (store_data(mlx) == 1)
		return (1);
	
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
	display_data(mlx);
	
	// store_textures(mlx);
	// find_player(mlx);
	// measure_map(mlx);
	// store_map(mlx);
	// display_parsing(mlx);
	return (0);
}
