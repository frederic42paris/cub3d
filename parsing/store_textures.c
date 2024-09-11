/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:01:44 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/11 12:48:18 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	store_path(char **path_var, char *str)
{
	int	i;

	i = 2;
	while (is_space(str[i]))
		i++;
	*path_var = ft_strdup_path(str + i);
	if (*path_var == NULL)
		return (1);
	return (0);
}

int	store_rgb(int *r, int *g, int *b, char *str)
{
	int	i;

	i = 1;
	while (is_space(str[i]))
		i++;
	*r = ft_strdup_digit(str + i, &i);
	if (*r == -1)
		return (1);
	while (str[i] != '\0' && (str[i] > '9' || str[i] < '0'))
		i++;
	*g = ft_strdup_digit(str + i, &i);
	if (*g == -1)
		return (1);
	while (str[i] != '\0' && (str[i] > '9' || str[i] < '0'))
		i++;
	*b = ft_strdup_digit(str + i, &i);
	if (*b == -1)
		return (1);
	return (0);
}

int	check_flcl_id(t_mlx *mlx, char *str)
{
	int	len;

	len = ft_strlen_word(str);
	if (len == 1 && ft_strncmp(str, "C", 1) == 0)
	{
		if (store_rgb(&mlx->ceiling_r, &mlx->ceiling_g,
				&mlx->ceiling_b, str) == 1)
			return (1);
	}
	else if (len == 1 && ft_strncmp(str, "F", 1) == 0)
	{
		if (store_rgb(&mlx->floor_r, &mlx->floor_g, &mlx->floor_b, str) == 1)
			return (1);
	}
	return (0);
}

int	check_identifier(t_mlx *mlx, char *str)
{
	int	len;

	len = ft_strlen_word(str);
	if (len == 2 && ft_strncmp(str, "NO", 2) == 0)
	{
		if (store_path(&mlx->path_north, str) == 1)
			return (1);
	}
	else if (len == 2 && ft_strncmp(str, "SO", 2) == 0)
	{
		if (store_path(&mlx->path_south, str) == 1)
			return (1);
	}
	else if (len == 2 && ft_strncmp(str, "EA", 2) == 0)
	{
		if (store_path(&mlx->path_east, str) == 1)
			return (1);
	}
	else if (len == 2 && ft_strncmp(str, "WE", 2) == 0)
	{
		if (store_path(&mlx->path_west, str) == 1)
			return (1);
	}
	return (0);
}

int	store_textures(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (is_space(mlx->textures[i][j]))
			j++;
		if (check_identifier(mlx, (mlx->textures[i]) + j) == 1)
			return (1);
		if (check_flcl_id(mlx, (mlx->textures[i]) + j) == 1)
			return (1);
		i++;
	}
	mlx->ceiling_color = create_argb(0, mlx->ceiling_r, mlx->ceiling_g,
			mlx->ceiling_b);
	mlx->floor_color = create_argb(0, mlx->floor_r, mlx->floor_g, mlx->floor_b);
	return (0);
}
