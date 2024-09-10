/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:22:27 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 16:50:04 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	select_texture(t_mlx *mlx)
{
	if (mlx->side == 0 && mlx->rayDirX < 0)
		mlx->color = mlx->text_north_addr[mlx->texY * TEXTH
			+ mlx->texX];
	else if (mlx->side == 0 && mlx->rayDirX >= 0)
		mlx->color = mlx->text_south_addr[mlx->texY * TEXTH
			+ mlx->texX];
	else if (mlx->side == 1 && mlx->rayDirY < 0)
		mlx->color = mlx->text_west_addr[mlx->texY * TEXTH + mlx->texX];
	else if (mlx->side == 1 && mlx->rayDirY >= 0)
		mlx->color = mlx->text_east_addr[mlx->texY * TEXTH + mlx->texX];
}

void	calculate_texture(t_mlx *mlx, int x)
{
	int	y;

	if (mlx->side == 0)
		mlx->wallX = mlx->posY + mlx->perpWallDist * mlx->rayDirY;
	else
		mlx->wallX = mlx->posX + mlx->perpWallDist * mlx->rayDirX;
	mlx->wallX -= floor((mlx->wallX));
	mlx->texX = (int)(mlx->wallX * (double)(TEXTW));
	if (mlx->side == 0 && mlx->rayDirX > 0)
		mlx->texX = TEXTW - mlx->texX - 1;
	if (mlx->side == 1 && mlx->rayDirY < 0)
		mlx->texX = TEXTW - mlx->texX - 1;
	mlx->step = 1.0 * TEXTH / mlx->lineHeight;
	mlx->texPos = (mlx->drawStart - SH / 2 + mlx->lineHeight / 2)
		* mlx->step;
	y = mlx->drawStart;
	while (y < mlx->drawEnd)
	{
		mlx->texY = (int)mlx->texPos & (TEXTH - 1);
		mlx->texPos += mlx->step;
		select_texture(mlx);
		my_mlx_pixel_put(mlx, x, y, mlx->color);
		y++;
	}
}
