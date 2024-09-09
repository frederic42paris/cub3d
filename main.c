/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/09 16:48:13 by arguez           ###   ########.fr       */
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

static void	mlx_ender(t_mlx *mlx)
{
	if (mlx->greystone == NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->greystone);
	if (mlx->bluestone == NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->bluestone);
	if (mlx->red == NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->red);
	if (mlx->wood == NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->wood);
	mlx_destroy_display(mlx->mlx_p);
}

void	ender(t_mlx *mlx)
{
	if (mlx->map_char != NULL)
		double_free((void **)mlx->map_char);
	if (mlx->map_int != NULL)
		free(mlx->map_int);
		// double_free((void **)mlx->map_int);
	if (mlx->path_north != NULL)
		free(mlx->path_north);
	if (mlx->path_east != NULL)
		free(mlx->path_east);
	if (mlx->path_west != NULL)
		free(mlx->path_west);
	if (mlx->path_south != NULL)
		free(mlx->path_south);
	if (mlx->textures != NULL)
		double_free((void **)mlx->textures);
	if (mlx->string_buffer != NULL)
		free(mlx->string_buffer);
	if (mlx->map_int_one != NULL)
		free(mlx->map_int_one);
		// double_free((void **)mlx->map_int_one);
	if (mlx->fd > 0)
		close(mlx->fd);
	mlx_ender(mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	
	if (check_argument(argv[1], argc) == 1)
		return (1);
	mlx = malloc(sizeof(t_mlx));
	open_file(mlx, argv[1]);
	if (store_data(mlx) == 1)
		return (1);
	if (check_textures(mlx) == 1)
		return (1);
	// display_data(mlx);
	find_player(mlx);
	measure_map(mlx);
	store_map_one(mlx);
	if (check_map(mlx) == 1)
		return (1);
	store_textures(mlx);
	store_map(mlx);
	display_parsing(mlx);
	init_values(mlx);
	init_minilibx(mlx);
	printf("reached main end\n");
	return (ender(mlx), 0);
}
