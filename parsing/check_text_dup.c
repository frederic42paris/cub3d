/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:39:00 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/09 17:09:35 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_text_dup(t_mlx *mlx)
{
	if (mlx->count_no != 1 || mlx->count_so != 1 || mlx->count_ea != 1
		|| mlx->count_we != 1 || mlx->count_c != 1 || mlx->count_f != 1)
	{
		printf("no: %d\nea: %d\nwe: %d\nso: %d\nc: %d\nf: %d\n", mlx->count_no,
			mlx->count_so, mlx->count_ea, mlx->count_we, mlx->count_c,
			mlx->count_f);
		printf("Error\nDuplicate IDs\n");
		return (1);
	}
	return (0);
}
