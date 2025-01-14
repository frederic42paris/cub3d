/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/11 13:27:30 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_textures(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (is_space(mlx->textures[i][j]))
			j++;
		if (check_text_id(mlx, (mlx->textures[i]) + j) == 1)
			return (1);
		if (check_text_path((mlx->textures[i]) + j) == 1)
			return (1);
		if (check_text_rgb((mlx->textures[i]) + j) == 1)
			return (1);
		i++;
	}
	if (check_text_dup(mlx) == 1)
		return (1);
	return (0);
}

int	check_map(t_mlx *mlx)
{
	if (check_map_size(mlx) == 1)
		return (1);
	if (check_map_line(mlx) == 1)
		return (1);
	if (check_map_character(mlx) == 1)
		return (1);
	if (check_map_players(mlx) == 1)
		return (1);
	if (check_map_walls(mlx) == 1)
		return (1);
	return (0);
}

static void	nullifer(t_mlx *mlx)
{
	mlx->count_no = 0;
	mlx->count_so = 0;
	mlx->count_ea = 0;
	mlx->count_we = 0;
	mlx->count_c = 0;
	mlx->count_f = 0;
	mlx->path_north = NULL;
	mlx->path_south = NULL;
	mlx->path_east = NULL;
	mlx->path_west = NULL;
	mlx->textures = NULL;
	mlx->map_char = NULL;
	mlx->map_int = NULL;
	mlx->map_intermediate = NULL;
	mlx->win_ptr = NULL;
	mlx->mlx_p = NULL;
	mlx->fd = 0;
	mlx->text_south = NULL;
	mlx->text_east = NULL;
	mlx->text_north = NULL;
	mlx->text_west = NULL;
	mlx->img = NULL;
}

int	parsing(t_mlx *mlx)
{
	if (store_data(mlx) == 1)
		return (1);
	if (check_textures(mlx) == 1)
		return (1);
	find_player(mlx);
	measure_map(mlx);
	if (store_midmap(mlx) == 1)
		return (1);
	if (check_map(mlx) == 1)
		return (1);
	if (store_textures(mlx) == 1)
		return (1);
	if (store_map(mlx) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (check_argument(argv[1], argc) == 1)
		return (1);
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (printf("Error: memory allocation failed\n"), 1);
	nullifer(mlx);
	if (open_file(mlx, argv[1]) == 1)
		return (1);
	if (parsing(mlx) == 1)
		return (ender(mlx), 1);
	init_player_direction(mlx);
	init_speed(mlx);
	if (init_minilibx(mlx) == 1)
		return (ender(mlx), 1);
	return (ender(mlx), 0);
}
