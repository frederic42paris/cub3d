/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 19:19:43 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ender(t_mlx *mlx)
{
	if (mlx->map_int != NULL)
		double_free((void **)mlx->map_int);
	if (mlx->map_char != NULL)
		double_free((void **)mlx->map_char);
	if (mlx->path_north != NULL)
		free(mlx->path_north);
	if (mlx->path_south != NULL)
		free(mlx->path_south);
	if (mlx->path_east != NULL)
		free(mlx->path_east);
	if (mlx->path_west != NULL)
		free(mlx->path_west);
	free(mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (args_checker(argc, argv[1]) == 0)
		return (1);
	mlx = malloc(sizeof(t_mlx));
	if (mlx == NULL)
		return (printf("Error: memory allocation for shared data struct failed\n"), 1);
	mlx->map_int = parser(argv[1], mlx);
	if (mlx->map_int == NULL)
		return (ender(mlx), 1);
	display_parsing(mlx);
	ender(mlx);
	return (0);
}
