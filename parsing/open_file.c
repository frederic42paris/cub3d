/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:20:52 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 10:21:09 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	open_file(t_mlx	*mlx, char *string)
{
	mlx->fd = open(string, O_RDONLY);
	if (mlx->fd < 0)
	{
		error_message(3);
		return (1);
	}
	return (0);
}