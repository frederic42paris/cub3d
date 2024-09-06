/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:34:37 by arguez            #+#    #+#             */
/*   Updated: 2024/09/06 20:12:11 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_lines(char *filename)
{
	int		fd;
	int		res;
	char	c;

	c = 0;
	res = 0;
	fd = open(filename, O_RDONLY);
	while (read(fd, &c, 1) == 1)
	{
		if (c == '\n')
			res++;
	}
	close(fd);
	return (res);
}

static int	texture_count_subroutine(char *tmp, int *textures)
{
	if (ft_strncmp(tmp, "NO ", 3) == 0)
		return (textures[0] += 1, 1);
	else if (ft_strncmp(tmp, "EA ", 3) == 0)
		return (textures[1] += 1, 1);
	else if (ft_strncmp(tmp, "SO ", 3) == 0)
		return (textures[2] += 1, 1);
	else if (ft_strncmp(tmp, "WE ", 3) == 0)
		return (textures[3] += 1, 1);
	else if (ft_strncmp(tmp, "F ", 2) == 0)
		return (textures[4] += 1, 1);
	else if (ft_strncmp(tmp, "C ", 2) == 0)
		return (textures[5] += 1, 1);
	else if (tmp[0] == '\n')
		return (1);
	return (0);
}

char	*get_tag(char *line)
{
	int	i;

	if (line == NULL)
		return (NULL);
	if (line[0] == '\0')
		return (NULL);
	i = 0;
	while (line[i] == ' ')
		i++;
	return (&line[i]);
}

void	count_texture_tags(char **map, int *textures)
{
	char	*tmp;
	int		i;

	i = 0;
	while (map[i] != NULL)
	{
		tmp = get_tag(map[i]);
		if (texture_count_subroutine(tmp, textures) == 0)
			return ;
		i++;
	}
}

int	test_access(char **map, char *tag)
{
	int		i;
	int		j;
	int		fd;
	char	*texture_path;
	char	*ftag;

	i = 0;
	while (map[i] != NULL)
	{
		ftag = get_tag(map[i]);
		if (ftag == NULL)
		{
			i++;
			continue ;
		}
		if (ft_strncmp(tag, ftag, ft_strlen(tag)) == 0)
		{
			j = 3;
			while (ftag[j] == ' ')
				j++;
			while ((ftag[j] != ' ') && (ftag[j] != '\n') && (ftag[j] != '\0'))
				j++;
			while (*ftag != ' ')
				ftag += 1;
			while (*ftag == ' ')
				ftag += 1;
			texture_path = ft_substr(ftag, 3, j - 2);
			printf("%s\n", texture_path);
			fd = open(texture_path, O_RDONLY);
			break ;
		}
		i++;
	}
	if (map[i] != NULL)
	{
		free(texture_path);
		if (fd < 0)
			return (1);
		close(fd);
	}
	else
		return (1);
	return (0);
}
