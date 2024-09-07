/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 11:20:36 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	

	check_argument(argv[1], argc);
	mlx = malloc(sizeof(t_mlx));
	// mlx->textures = malloc(6 * sizeof(char *) + 1);
	open_file(mlx, argv[1]);
	store_data(mlx);
	store_textures(mlx);
	analyse_map(mlx);
	store_map(mlx);
	display_parsing(mlx);
	// if (mlx == NULL)
		// return (printf("Error: memory allocation for shared data struct failed\n"), 1);
	
	// mlx->map_int = parser(argv[1], mlx);
	// if (mlx->map_int == NULL)
	// 	return (ender(mlx), 1);
	// display_parsing(mlx);
	// ender(mlx);
	return (0);
}
