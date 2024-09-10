/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:20:52 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/10 15:53:50 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	open_file(t_mlx *mlx, char *string)
{
	mlx->fd = open(string, O_RDONLY);
	if (mlx->fd < 0)
	{
		printf("Error\nFile not found\n");
		return (1);
	}
	return (0);
}
