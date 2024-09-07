/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:39:00 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 15:11:21 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen_word_path(const char *s)
{
	size_t	i;

	i = 0;
	while (is_not_space(s[i]))
		i++;
	return (i);
}

int	open_xpm(char *str)
{
	int	path_xpm;
	int	i;
	char	*path;
	int j;

	path = NULL;
	i = 0;
	j = 0;
	while (is_not_space(str[i]))
		i++;
	while (is_space(str[i]))
		i++;
	while (is_not_space(str[i + j]))
		j++;
	path = ft_substr(str, i, j);
	path_xpm = open(path, O_RDONLY);
	if (path_xpm < 0)
	{
		printf("Xpm not found\n");
		close(path_xpm);
		return (1);
	}
	close(path_xpm);
	return (0);
}

int	is_identifier_path(char *str)
{
	int len;

	len = ft_strlen_word_path(str);
	if (len == 2
		&& (
			ft_strncmp(str, "NO",2) == 0
			|| ft_strncmp(str, "SO",2) == 0
			|| ft_strncmp(str, "EA",2) == 0
			|| ft_strncmp(str, "WE",2) == 0
			))
		if (open_xpm(str) == 1)
			return (1);
	return (0);
}

int	parse_information_path(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (is_identifier_path(str + i) == 1)
		return (1);
	return (0);
}

int	check_path(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (parse_information_path(mlx->textures[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}