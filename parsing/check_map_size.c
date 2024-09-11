/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:16:44 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/11 12:18:49 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map_size(t_mlx *mlx)
{
	if ((mlx->map_width < 3) || (mlx->map_height < 3))
	{
		printf("Error: map must be at least 3x3\n");
		return (1);
	}
	return (0);
}
