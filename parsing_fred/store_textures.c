/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:01:44 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 13:24:58 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen_word(const char *s)
{
	size_t	i;

	i = 0;
	while (is_not_space(s[i]))
		i++;
	return (i);
}

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

int	is_identifier(t_mlx *mlx, char *str)
{
	int len;

	len = ft_strlen_word(str);
	if (len == 2 && ft_strncmp(str, "NO",2) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->path_north = ft_strdup_path(str + len);
	}
	else if (len == 2 && ft_strncmp(str, "SO",2) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->path_south = ft_strdup_path(str + len);

	}
	else if (len == 2 && ft_strncmp(str, "EA",2) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->path_east = ft_strdup_path(str + len);
	}
	else if (len == 2 && ft_strncmp(str, "WE",2) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->path_west = ft_strdup_path(str + len);
	}
	else if (len == 1 && ft_strncmp(str, "C",1) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->ceiling_r = ft_strdup_digit(str + len, &len);
		while(str[len] != '\0' && (str[len] > '9' || str[len] < '0'))
			len++;
		mlx->ceiling_g = ft_strdup_digit(str + len, &len);
		while(str[len] != '\0' && (str[len] > '9' || str[len] < '0'))
			len++;
		mlx->ceiling_b = ft_strdup_digit(str + len, &len);
		mlx->ceiling_color = 	create_argb(0, mlx->ceiling_r, mlx->ceiling_g, mlx->ceiling_b);
	}
	else if (len == 1 && ft_strncmp(str, "F",1) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->floor_r = ft_strdup_digit(str + len, &len);
		while(str[len] != '\0' && (str[len] > '9' || str[len] < '0'))
			len++;
		mlx->floor_g = ft_strdup_digit(str + len, &len);
		while(str[len] != '\0' && (str[len] > '9' || str[len] < '0'))
			len++;
		mlx->floor_b = ft_strdup_digit(str + len, &len);
		mlx->floor_color = 	create_argb(0, mlx->floor_r, mlx->floor_g, mlx->floor_b);
	}
	return (0);
}

int	parse_information(t_mlx *mlx, char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	is_identifier(mlx, str + i);
	return 0;
}

int	store_textures(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		parse_information(mlx, mlx->textures[i]);
		i++;
	}
	return (0);
}