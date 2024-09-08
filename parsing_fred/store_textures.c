/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:01:44 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/08 13:56:34 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int create_argb(int a, int r, int g, int b)
{
    return (a << 24 | r << 16 | g << 8 | b);
}

int	ft_strdup_digit(const char *s, int *j)
{
	char	*dest;
	int		i;
	int		final;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	dest = (char *)malloc(i + 1);
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		dest[i] = s[i];
		i++;
	}
	*j = *j + i;
	dest[i] = '\0';
	final = ft_atoi(dest);
	return (final);
}

char	*ft_strdup_path(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n' && is_not_space(s[i]))
		i++;
	dest = (char *)malloc(i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n' && is_not_space(s[i]))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	store_path(char **path_var, char *str)
{
	int i;

	i = 2;
	while (is_space(str[i]))
			i++;
	*path_var = ft_strdup_path(str + i);
	return (0);
}

int	store_rgb(int *r, int *g, int *b, char *str)
{
	int i;

	i = 1;
	while (is_space(str[i]))
		i++;
	*r = ft_strdup_digit(str + i, &i);
	while(str[i] != '\0' && (str[i] > '9' || str[i] < '0'))
		i++;
	*g = ft_strdup_digit(str + i, &i);
	while(str[i] != '\0' && (str[i] > '9' || str[i] < '0'))
		i++;
	*b = ft_strdup_digit(str + i, &i);
	return (0);
}

int	check_identifier(t_mlx *mlx, char *str)
{
	int len;

	len = ft_strlen_word(str);
	if (len == 2 && ft_strncmp(str, "NO",2) == 0)
		store_path(&mlx->path_north, str);
	else if (len == 2 && ft_strncmp(str, "SO",2) == 0)
		store_path(&mlx->path_south, str);
	else if (len == 2 && ft_strncmp(str, "EA",2) == 0)
		store_path(&mlx->path_east, str);
	else if (len == 2 && ft_strncmp(str, "WE",2) == 0)
		store_path(&mlx->path_west, str);
	else if (len == 1 && ft_strncmp(str, "C",1) == 0)
		store_rgb(&mlx->ceiling_r, &mlx->ceiling_g, &mlx->ceiling_b, str);
	else if (len == 1 && ft_strncmp(str, "F",1) == 0)
		store_rgb(&mlx->floor_r, &mlx->floor_g, &mlx->floor_b, str);
	return (0);
}

int	store_textures(t_mlx *mlx)
{
	int	i;
	int j;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (is_space(mlx->textures[i][j]))
			j++;
		if (check_identifier(mlx, (mlx->textures[i]) + j) == 1)
			return (1);
		i++;
	}
	mlx->ceiling_color = create_argb(0, mlx->ceiling_r, mlx->ceiling_g, mlx->ceiling_b);
	mlx->floor_color = create_argb(0, mlx->floor_r, mlx->floor_g, mlx->floor_b);
	return (0);
}