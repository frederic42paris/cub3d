/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:35:57 by arguez            #+#    #+#             */
/*   Updated: 2024/09/06 17:51:33 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	textures_malloc_safecheck(t_mlx *mlx)
{
	if ((!mlx->path_north) || (!mlx->path_south) || (!mlx->path_east)
		|| (!mlx->path_west))
	{
		printf("Error: memory allocation for texture paths failed\n");
		return (1);
	}
	return (0);
}

int	textures_loader(t_mlx *mlx, char **map)
{
	int		i;
	char	*tmp;

	tmp = get_tag_addr(map, "NO ");
	i = 0;
	while ((tmp[i] != ' ') && (tmp[i] != '\n') && (tmp[i] != '\0'))
		i++;
	mlx->path_north = ft_substr(tmp, 0, i);
	tmp = get_tag_addr(map, "SO ");
	i = 0;
	while ((tmp[i] != ' ') && (tmp[i] != '\n') && (tmp[i] != '\0'))
		i++;
	mlx->path_south = ft_substr(tmp, 0, i);
	tmp = get_tag_addr(map, "EA ");
	i = 0;
	while ((tmp[i] != ' ') && (tmp[i] != '\n') && (tmp[i] != '\0'))
		i++;
	mlx->path_east = ft_substr(tmp, 0, i);
	tmp = get_tag_addr(map, "WE ");
	i = 0;
	while ((tmp[i] != ' ') && (tmp[i] != '\n') && (tmp[i] != '\0'))
		i++;
	mlx->path_west = ft_substr(tmp, 0, i);
	return (textures_malloc_safecheck(mlx));
}
