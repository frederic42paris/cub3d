/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:39:00 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/08 13:33:00 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_text_dup(t_mlx *mlx)
{
	if (mlx->count_no != 1
		|| mlx->count_so != 1
		|| mlx->count_ea != 1
		|| mlx->count_we != 1
		|| mlx->count_c != 1
		|| mlx->count_f != 1)
	{
		printf("Error\nDuplicates ID\n");
		return (1);
	}
		return (0);
}