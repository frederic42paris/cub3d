/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:13:22 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 15:36:17 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen_word_rgb(const char *s)
{
	size_t	i;

	i = 0;
	while (is_not_space(s[i]))
		i++;
	return (i);
}

int	is_not_space_comma(char c)
{
	if (c != ' ' && c != '\0' && c != '\t'  && c != ',')
		return (1);
	else
		return (0);
}

int	is_space_comma(char c)
{
	if (c == ' ' || c == '\t' || c == ',')
		return (1);
	else
		return (0);
}

int	check_rgb_value(char *str)
{
	int	i;
	int j;
	char *path;
	int nb;

	path = NULL;
	i = 0;
	j = 0;
	nb = 0;
	while (is_not_space(str[i]))
		i++;
	while (is_space(str[i]))
		i++;
	while (is_not_space_comma(str[i + j]))
		j++;
	path = ft_substr(str, i, j);
	nb = ft_atoi(path);
	// printf("%d\n", nb);
	if (nb > 255 || nb < 0)
	{
		printf("wrong rgb value\n");
		return (1);
	}
	
	i = i + j;

	while (is_space_comma(str[i]))
		i++;
	while (is_not_space_comma(str[i + j]))
		j++;
	path = ft_substr(str, i, j);
	nb = ft_atoi(path);
	// printf("%d\n", nb);
	if (nb > 255 || nb < 0)
	{
		printf("wrong rgb value\n");
		return (1);
	}

	i = i + j;

	while (is_space_comma(str[i]))
		i++;
	while (is_not_space_comma(str[i + j]))
		j++;
	path = ft_substr(str, i, j);
	nb = ft_atoi(path);
	// printf("%d\n", nb);
	if (nb > 255 || nb < 0)
	{
		printf("wrong rgb value\n");
		return (1);
	}
	return (0);
}

int	is_identifier_rgb(char *str)
{
	int len;

	len = ft_strlen_word_rgb(str);
	if (len == 1
		&& (
			ft_strncmp(str, "C",1) == 0
			|| ft_strncmp(str, "F",1) == 0
			))
		if (check_rgb_value(str) == 1)
			return (1);
	return (0);
}

int	parse_information_rgb(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (is_identifier_rgb(str + i) == 1)
		return (1);
	return (0);
}

int	check_rgb(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (parse_information_rgb(mlx->textures[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}