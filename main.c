/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 10:14:09 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(int num)
{
	if (num == 1)
		ft_printf("Error\nNumber of arguments incorrect\n");
	else if (num == 2)
		ft_printf("Error\nFile name incorrect\n");
	else if (num == 3)
		ft_printf("Error\nFile not found\n");
	else if (num == 4)
		ft_printf("Error\nEmpty map\n");
	else if (num == 5)
		ft_printf("Error\nEmpty line in map\n");
	else if (num == 6)
		ft_printf("Error\nElements number incorrect\n");
	else if (num == 7)
		ft_printf("Error\nMap not rectangular\n");
	else if (num == 8)
		ft_printf("Error\nWalls incorrect\n");
	else if (num == 9)
		ft_printf("Error\nWindow closed due to invalid path.\n");
	else if (num == 10)
		ft_printf("Error\nUnknown element\n");
}

int	wrong_input(char *filename, int inputnumber)
{
	char	*string;

	if (inputnumber != 2)
	{
		error_message(1);
		return (1);
	}
	string = ft_strrchr(filename, '.');
	if (string == 0)
	{
		error_message(2);
		return (1);
	}
	if (ft_strncmp(string, ".cub", 4) != 0)
	{
		error_message(2);
		return (1);
	}
	return (0);
}

int	open_file(t_mlx	*mlx, char *string)
{
	mlx->fd = open(string, O_RDONLY);
	if (mlx->fd < 0)
	{
		error_message(3);
		return (1);
	}
	return (0);
}

void	find_player(t_mlx *mlx, int i, int j)
{
	if (mlx->map_char[j][i] == 'N')
	{
		mlx->posX = i;
		mlx->posY = j;
		mlx->hasplayer++;
	}
}

void	measure_map(t_mlx *mlx, int i, int j)
{
	mlx->map_width = i;
	mlx->map_height = j;
}

void	analyse_map(t_mlx *mlx)
{
	int		i;
	int		j;

	mlx->hasplayer = 0;
	j = 0;
	while (mlx->map_char[j])
	{
		i = 0;
		while (mlx->map_char[j][i] != '\0')
		{
			find_player(mlx, i, j);
			i++;
		}
		j++;
	}
	measure_map(mlx, i, j);
}

void	copymap(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	mlx->map_int = malloc(sizeof(int *) * (mlx->map_height));
	while (i < mlx->map_height)
	{
		mlx->map_int[i] = malloc(sizeof(int) * (mlx->map_width));
		j = 0;
		while (j < mlx->map_width)
		{
			if (mlx->map_char[i][j] == 'N')
				mlx->map_int[i][j] = 0;
			else
				mlx->map_int[i][j] = mlx->map_char[i][j] - '0';
			j++;
		}
		i++;
	}
}

char	*ft_strdup_path(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	dest = (char *)malloc(i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
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

int create_argb(int a, int r, int g, int b)
{
    return (a << 24 | r << 16 | g << 8 | b);
}

int	is_empty(t_mlx *mlx, char *temp, char *concat)
{
	int	i;

	i = 0;
	if (concat[0] == '\0')
	{
		error_message(4);
		free(temp);
		return (1);
	}
	while (concat[i] != '\0')
	{
		if (concat[i] == '\n' && concat[i + 1] == '\n')
		{
			error_message(5);
			free(temp);
			return (1);
		}
		i++;
	}
	mlx->map_char = ft_split(concat, '\n');
	free(concat);
	return (0);
}

int	store_map(t_mlx *mlx)
{
	char	*string;
	char	*temp;
	char	*concat;

	string = "1";
	concat = ft_strdup("");
	while (string)
	{
		string = NULL;
		temp = concat;
		string = get_next_line(mlx->fd);
		if (string)
		{
			concat = ft_strjoin(temp, string);
			free(string);
			free(temp);
		}
	}
	if (is_empty(mlx, temp, concat) == 1)
		return (1);
	return (0);
}

int	check_file(t_mlx *mlx)
{
	char	*string;
	char	*temp;
	char	*concat;
	int		i;

	while (1)
	{
		string = get_next_line(mlx->fd);
		if (string)
		{
			if (ft_strncmp(string, "NO", 2) == 0)
				mlx->path_north = ft_strdup_path(string + 3);
			else if (ft_strncmp(string, "SO", 2) == 0)
				mlx->path_south = ft_strdup_path(string + 3);
			else if (ft_strncmp(string, "WE", 2) == 0)
				mlx->path_west = ft_strdup_path(string + 3);
			else if (ft_strncmp(string, "EA", 2) == 0)
				mlx->path_east = ft_strdup_path(string + 3);
			else if (ft_strncmp(string, "F", 1) == 0)
			{
				i = 2;
				while (string[i] != '\0')
				{
					mlx->floor_r = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
					mlx->floor_g = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
					mlx->floor_b = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
				}
				mlx->floor_color = 	create_argb(0, mlx->floor_r, mlx->floor_g, mlx->floor_b);
			}
			else if (ft_strncmp(string, "C", 1) == 0)
			{
				i = 2;
				while (string[i] != '\0')
				{
					mlx->ceiling_r = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
					mlx->ceiling_g = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
					mlx->ceiling_b = ft_strdup_digit(string + i, &i);
					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
						i++;
				}
				mlx->ceiling_color = 	create_argb(0, mlx->ceiling_r, mlx->ceiling_g, mlx->ceiling_b);		
			}
			else if (ft_strrchr(string, '1'))
				break;
		}
		else
			break;
	}
	concat = ft_strdup("");
	temp = concat;
	concat = ft_strjoin(temp, string);
	free(string);
	free(temp);
	while (1)
	{
		string = NULL;
		temp = concat;
		string = get_next_line(mlx->fd);
		if (string)
		{
			concat = ft_strjoin(temp, string);
			free(string);
			free(temp);
		}
		else
			break;
	}
	if (is_empty(mlx, temp, concat) == 1)
		return (1);
	return (0);
}

void check_map_int(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	// printf("[%d]", mlx->map_int[1][2]);
	while(i < mlx->map_height)
	{
		j = 0;
		while(j < mlx->map_width)
		{
			printf("%d", mlx->map_int[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;


	mlx = malloc(sizeof(t_mlx));
	mlx->map_char = NULL;
	if (wrong_input(argv[1], argc) == 1)
		return (1);
	if (open_file(mlx, argv[1]) == 1)
		return (0);

	check_file(mlx);
	analyse_map(mlx);
	copymap(mlx);
	check_map_int(mlx);
	printf("%s\n", mlx->path_north);
	printf("%s\n", mlx->path_south);
	printf("%s\n", mlx->path_east);
	printf("%s\n", mlx->path_west);
	printf("%d\n", mlx->floor_r);
	printf("%d\n", mlx->floor_g);
	printf("%d\n", mlx->floor_b);
	printf("%d\n", mlx->ceiling_r);
	printf("%d\n", mlx->ceiling_g);
	printf("%d\n", mlx->ceiling_b);

	return (0);
}



// void check_map_char(t_mlx *mlx)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while(mlx->map[i])
// 	{
// 		j = 0;
// 		while(mlx->map[i][j])
// 		{
// 			printf("%c", mlx->map[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

