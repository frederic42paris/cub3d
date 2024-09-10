/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:22:27 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 17:29:32 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	select_texture(t_mlx *mlx)
{
	if (mlx->side == 0 && mlx->raydir_x < 0)
		mlx->color = mlx->text_north_addr[mlx->tex_y * TEXTH
			+ mlx->tex_x];
	else if (mlx->side == 0 && mlx->raydir_x >= 0)
		mlx->color = mlx->text_south_addr[mlx->tex_y * TEXTH
			+ mlx->tex_x];
	else if (mlx->side == 1 && mlx->raydir_y < 0)
		mlx->color = mlx->text_west_addr[mlx->tex_y * TEXTH + mlx->tex_x];
	else if (mlx->side == 1 && mlx->raydir_y >= 0)
		mlx->color = mlx->text_east_addr[mlx->tex_y * TEXTH + mlx->tex_x];
}

void	calculate_texture(t_mlx *mlx, int x)
{
	int	y;

	if (mlx->side == 0)
		mlx->wall_x = mlx->pos_y + mlx->perp_wall_dist * mlx->raydir_y;
	else
		mlx->wall_x = mlx->pos_x + mlx->perp_wall_dist * mlx->raydir_x;
	mlx->wall_x -= floor((mlx->wall_x));
	mlx->tex_x = (int)(mlx->wall_x * (double)(TEXTW));
	if (mlx->side == 0 && mlx->raydir_x > 0)
		mlx->tex_x = TEXTW - mlx->tex_x - 1;
	if (mlx->side == 1 && mlx->raydir_y < 0)
		mlx->tex_x = TEXTW - mlx->tex_x - 1;
	mlx->step = 1.0 * TEXTH / mlx->line_height;
	mlx->tex_pos = (mlx->draw_start - SH / 2 + mlx->line_height / 2)
		* mlx->step;
	y = mlx->draw_start;
	while (y < mlx->draw_end)
	{
		mlx->tex_y = (int)mlx->tex_pos & (TEXTH - 1);
		mlx->tex_pos += mlx->step;
		select_texture(mlx);
		my_mlx_pixel_put(mlx, x, y, mlx->color);
		y++;
	}
}
