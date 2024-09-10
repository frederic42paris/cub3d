/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:37:56 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 16:49:37 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	store_images(t_mlx *mlx)
{
	int	img_width;
	int	img_height;

	mlx->text_north = mlx_xpm_file_to_image(mlx->mlx_p, mlx->path_south,
			&img_width, &img_height);
	mlx->text_east = mlx_xpm_file_to_image(mlx->mlx_p, mlx->path_west,
			&img_width, &img_height);
	mlx->text_west = mlx_xpm_file_to_image(mlx->mlx_p, mlx->path_east,
			&img_width, &img_height);
	mlx->text_south = mlx_xpm_file_to_image(mlx->mlx_p, mlx->path_north,
			&img_width, &img_height);
	return (0);
}

int	store_images_addr(t_mlx *mlx)
{
	mlx->text_south_addr = (int *)mlx_get_data_addr(mlx->text_south,
			&mlx->bits_per_pixel_text_south, &mlx->line_length_text_south,
			&mlx->endian_text_south);
	mlx->text_east_addr = (int *)mlx_get_data_addr(mlx->text_east,
			&mlx->bits_per_pixel_text_east, &mlx->line_length_text_east,
			&mlx->endian_text_east);
	mlx->text_north_addr = (int *)mlx_get_data_addr(mlx->text_north,
			&mlx->bits_per_pixel_text_north, &mlx->line_length_text_north,
			&mlx->endian_text_north);
	mlx->text_west_addr = (int *)mlx_get_data_addr(mlx->text_west,
			&mlx->bits_per_pixel_text_west, &mlx->line_length_text_west,
			&mlx->endian_text_west);
	return (0);
}
