/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:39:00 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/09 17:12:08 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	open_xpm(char *str)
{
	int	fd;
	int	i;
	char	*path;
	int j;

	path = NULL;
	i = 0;
	j = 0;
	while (ft_isalnum(str[i]))
		i++;
	while (is_space(str[i]))
		i++;
	while (is_not_space(str[i + j]))
		j++;
	path = ft_substr(str, i, j);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd < 0)
	{
		printf("Xpm not found\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_text_path(char *str)
{
	int len;

	len = ft_strlen_word(str);
	if (len == 2
		&& (
			ft_strncmp(str, "NO",2) == 0
			|| ft_strncmp(str, "SO",2) == 0
			|| ft_strncmp(str, "EA",2) == 0
			|| ft_strncmp(str, "WE",2) == 0
			))
	{
		if (open_xpm(str) == 1)
			return (1);
	}
	return (0);
}