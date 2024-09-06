/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:13:05 by arguez            #+#    #+#             */
/*   Updated: 2024/09/06 17:52:12 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	args_checker(int argc, char *filename)
{
	char	*tmp;
	int		tmp_fd;

	if (argc != 2)
	{
		printf("Error: expected 1 argument, received %d\n", argc - 1);
		return (0);
	}
	tmp = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (tmp == NULL)
		return (printf("Error: file is not in format .cub\n"), 0);
	tmp += 4;
	if (*tmp != '\0')
		return (printf("Error: file is not in format .cub\n"), 0);
	tmp_fd = open(filename, O_RDONLY);
	if (tmp_fd == -1)
		return (printf("Error: cannot open %s\n", filename), 0);
	close(tmp_fd);
	return (1);
}

static char	**file_to_array(char *filename)
{
	char	**res;
	int		i;
	int		fd;

	res = malloc((count_lines(filename) + 1) * sizeof(char *));
	if (res == NULL)
		return (printf("Error: memory allocation failed\n"), NULL);
	i = 0;
	fd = open(filename, O_RDONLY);
	while (1)
	{
		res[i] = get_next_line(fd);
		if (res[i] == NULL)
			break ;
		i++;
	}
	close(fd);
	return (res);
}

static int	checkfor_textures(char **map)
{
	int	i;
	int	*textures;

	textures = malloc (6 * sizeof(int));
	ft_memset(textures, 0, 6);
	count_texture_tags(map, &textures);
	i = 0;
	while (i < 6)
	{
		if (textures[i] != 1)
		{
			free(textures);
			return (printf("Error: there needs to be exactly \
				1 path per texture\n"), 1);
		}
		i++;
	}
	free(textures);
	return (0);
}

static int	check_files_access(char **map)
{
	int	errors;

	errors = 0;
	errors += test_access(map, "NO ");
	errors += test_access(map, "SO ");
	errors += test_access(map, "EA ");
	errors += test_access(map, "WE ");
	if (errors != 0)
		return (printf("Error: can't open one or more texture files\n"), 1);
	return (0);
}

int	**parser(char *filename, t_mlx *mlx)
{
	int		errors;
	char	**map;

	errors = 0;
	map = file_to_array(filename);
	errors += checkfor_textures(map);
	errors += check_files_access(map);
	if (errors != 0)
		return (NULL);
	textures_loader(mlx, map);
	errors += rgb_checker(mlx, map);
	errors += get_map_size(map, mlx);
	errors += check_valid_map(map);
	if (errors != 0)
		return (NULL);
	mlx->map_int = malloc (mlx->map_height * sizeof(int *));
	if (mlx->map_int == NULL)
		return (printf("Error: malloc failed\n"), NULL);
	map_filler(mlx, map);
	if (errors == 0)
		return (mlx->map_int);
	return (NULL);
}
