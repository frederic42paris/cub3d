/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ender.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:27:07 by arguez            #+#    #+#             */
/*   Updated: 2024/09/10 16:38:29 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	double_free_int(int **tab, t_mlx *mlx)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i < mlx->map_width)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	ending_subroutine(t_mlx *mlx)
{
	if (mlx->text_south != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->text_south);
	if (mlx->text_east != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->text_east);
	if (mlx->text_north != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->text_north);
	if (mlx->text_west != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->text_west);
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->img);
	if (mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_p, mlx->win_ptr);
	if (mlx->mlx_p != NULL)
		mlx_destroy_display(mlx->mlx_p);
}

void	ender(t_mlx *mlx)
{
	ending_subroutine(mlx);
	if (mlx->path_north != NULL)
		free(mlx->path_north);
	if (mlx->path_south != NULL)
		free(mlx->path_south);
	if (mlx->path_east != NULL)
		free(mlx->path_east);
	if (mlx->path_west != NULL)
		free(mlx->path_west);
	if (mlx->textures != NULL)
		double_free((void **)mlx->textures);
	if (mlx->map_char != NULL)
		double_free((void **)mlx->map_char);
	if (mlx->map_int != NULL)
		double_free_int(mlx->map_int, mlx);
	if (mlx->map_int_one != NULL)
		double_free_int(mlx->map_int_one, mlx);
	if (mlx->mlx_p != NULL)
		free(mlx->mlx_p);
	if (mlx->fd > 0)
		close(mlx->fd);
	free(mlx);
}
