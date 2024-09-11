/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:10:31 by arguez            #+#    #+#             */
/*   Updated: 2024/09/11 11:43:21 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	split_string_2(t_mlx *mlx, char *concat)
{
	mlx->map_char = ft_split(concat, '\n');
	free(concat);
	return (0);
}

void	ssl_subrountine(char **string, char **c2, char **temp, int *counter)
{
	*c2 = ft_strjoin(*temp, *string);
	free(*string);
	free(*temp);
	*counter += 1;
}
