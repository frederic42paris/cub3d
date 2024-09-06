/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:35:58 by arguez            #+#    #+#             */
/*   Updated: 2024/09/06 17:31:39 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*get_rgb_addr(char **map, char *target)
{
	char	*tag;
	int		i;

	i = 0;
	while (ft_strncmp(get_tag(map[i]), target, 2) != 0)
		i++;
	tag = get_tag(map[i]);
	tag += 2;
	while (*tag == ' ')
		tag++;
	return (tag);
}

static int	get_value(char *rgb)
{
	static int	i = 0;
	int			j;
	int			res;
	char		*tmp;

	j = i;
	while (ft_isdigit(rgb[j]))
		j++;
	tmp = ft_substr(rgb, i, j);
	res = ft_atoi(tmp);
	i = j + 1;
	if ((rgb[i] == ' ') || (rgb[i] == '\n') || (rgb[i] == '\0'))
		i = 0;
	free(tmp);
	return (res);
}

static int	check_rgb_format(char *vals)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 2)
	{
		while ((vals[i] != ',') && (vals[i] != '\n') && (vals[i] != '\0'))
		{
			if (ft_isdigit(vals[i]) == 0)
				return (0);
			i++;
		}
		if (vals[i++] != ',')
			return (0);
		j++;
	}
	while ((vals[i] != ' ') && (vals[i] != '\n') && (vals[i] != '\0'))
	{
		if (ft_isdigit(vals[i]) == 0)
			return (0);
		i++;
	}
	return (0);
}

static int	cev(int n)
{
	if ((n < 0) || (n > 255))
		return (0);
	return (1);
}

int	rgb_checker(t_mlx *mlx, char **map)
{
	char	*floor_vals;
	char	*ceil_vals;

	floor_vals = get_rgb_addr(map, "F ");
	ceil_vals = get_rgb_addr(map, "C ");
	if ((check_rgb_format(floor_vals) == 0) || (check_rgb_format(ceil_vals) == 0))
		return (printf("Error: RGB values must be \
			formatted as: [val],[val],[val]\n"), 1);
	mlx->floor_r = get_value(floor_vals);
	mlx->floor_g = get_value(floor_vals);
	mlx->floor_b = get_value(floor_vals);
	mlx->ceiling_b = get_value(ceil_vals);
	mlx->ceiling_b = get_value(ceil_vals);
	mlx->ceiling_b = get_value(ceil_vals);
	if ((!cev(mlx->floor_r)) || (!cev(mlx->floor_g)) || (!cev(mlx->floor_b)))
		return (printf("Error: floor rgb values must \
			be so that 0 <= value <= 255"), 1);
	if ((!cev(mlx->ceiling_r)) || (!cev(mlx->ceiling_g)) || (!cev(mlx->ceiling_b)))
		return (printf("Error: ceiling rgb values must \
			be so that 0 <= value <= 255"), 1);
	return (0);
}
