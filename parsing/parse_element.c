/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:15:31 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 14:05:59 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	open_xpm(char *string)
{
	int	path_xpm;
	
	path_xpm = open(string, O_RDONLY);
	if (path_xpm < 0)
	{
		error_message(14);
		close(path_xpm);
		return (1);
	}
	close(path_xpm);
	return (0);
}

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

int	count_letters(char *str)
{
	int i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]))
			counter++;
		i++;
	}
	return (counter);
}

int	is_identifier(t_mlx *mlx, char *str, int *counter)
{
	int len;

	len = ft_strlen_word(str);
	if (len == 2 && ft_strncmp(str, "NO",2) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->path_north = ft_strdup_path(str + len);
		if (open_xpm(mlx->path_north) == 1)
			return (1);
		mlx->count_no++;
		(*counter)++;
	}
	else if (len == 2 && ft_strncmp(str, "SO",2) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->path_south = ft_strdup_path(str + len);
		if (open_xpm(mlx->path_south))
			return (1);
		mlx->count_so++;
		(*counter)++;
	}
	else if (len == 2 && ft_strncmp(str, "EA",2) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->path_east = ft_strdup_path(str + len);
		if (open_xpm(mlx->path_east))
			return (1);
		mlx->count_ea++;
		(*counter)++;
	}
	else if (len == 2 && ft_strncmp(str, "WE",2) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->path_west = ft_strdup_path(str + len);
		if (open_xpm(mlx->path_west))
			return (1);
		mlx->count_we++;
		(*counter)++;
	}
	else if (len == 1 && ft_strncmp(str, "C",1) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->ceiling_r = ft_strdup_digit(str + len, &len);
		if (mlx->ceiling_r > 255 || mlx->ceiling_r < 0)
		{
			error_message(15);
			return (1);
		}
		while(str[len] != '\0' && (str[len] > '9' || str[len] < '0'))
			len++;
		mlx->ceiling_g = ft_strdup_digit(str + len, &len);
		if (mlx->ceiling_g > 255 || mlx->ceiling_g < 0)
		{
			error_message(15);
			return (1);
		}
		while(str[len] != '\0' && (str[len] > '9' || str[len] < '0'))
			len++;
		mlx->ceiling_b = ft_strdup_digit(str + len, &len);
		if (mlx->ceiling_b > 255 || mlx->ceiling_b < 0)
		{
			error_message(15);
			return (1);
		}
		mlx->ceiling_color = 	create_argb(0, mlx->ceiling_r, mlx->ceiling_g, mlx->ceiling_b);
		mlx->count_c++;
		(*counter)++;
	}
	else if (len == 1 && ft_strncmp(str, "F",1) == 0)
	{
		while (is_space(str[len]))
			len++;
		mlx->floor_r = ft_strdup_digit(str + len, &len);
		if (mlx->floor_r > 255 || mlx->floor_r < 0)
		{
			error_message(15);
			return (1);
		}
		while(str[len] != '\0' && (str[len] > '9' || str[len] < '0'))
			len++;
		mlx->floor_g = ft_strdup_digit(str + len, &len);
		if (mlx->floor_g > 255 || mlx->floor_g < 0)
		{
			error_message(15);
			return (1);
		}
		while(str[len] != '\0' && (str[len] > '9' || str[len] < '0'))
			len++;
		mlx->floor_b = ft_strdup_digit(str + len, &len);
		if (mlx->floor_b > 255 || mlx->floor_b < 0)
		{
			error_message(15);
			return (1);
		}
		mlx->floor_color = 	create_argb(0, mlx->floor_r, mlx->floor_g, mlx->floor_b);
		mlx->count_f++;
		(*counter)++;
	}
	else
	{
		if (count_letters(str) > 1)
		{
			return (1);
		}
		else
		{
			printf("MAP\n");
			return (0);
		}
	}
	return (0);
}

int	parse_information(t_mlx *mlx, char *str, int *counter)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (is_identifier(mlx, str + i, counter) == 1)
	{
		
		error_message(11);
		return (1);
	}
	return 0;
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

int	parse_elements(t_mlx *mlx)
{
	char	*string;
	int		counter;
	// char	*temp;
	// char	*concat;

	counter = 0;
	mlx->count_no = 0;
	mlx->count_so = 0;
	mlx->count_ea = 0;
	mlx->count_we = 0;
	mlx->count_c = 0;
	mlx->count_f = 0;
	while (1)
	{
		if (counter > 6)
		{
			error_message(12);
			return (1);
		}
		else if (mlx->count_c > 1 || mlx->count_f > 1 || mlx->count_no > 1
			|| mlx->count_ea > 1 || mlx->count_we > 1 || mlx->count_so > 1)
		{
			error_message(13);
			return (1);
		}
		string = get_next_line(mlx->fd);
		if (string)
		{
			if (has_alpha_num(string))
			{
				// printf("[%s]", string);
				if (parse_information(mlx, string, &counter) == 1)
					return (1);
			}
			free(string);
		}
		else
			break;
		
	}
	printf("%s\n", string);
	// concat = ft_strdup("");
	// temp = concat;
	// concat = ft_strjoin(temp, string);
	// free(string);
	// free(temp);
	// while (1)
	// {
	// 	string = get_next_line(mlx->fd);
	// 	if (string)
	// 	{
	// 		if (has_alpha_num(string))
	// 		{
	// 			concat = ft_strjoin(temp, string);
	// 			free(temp);
	// 		}
	// 		free(string);
	// 	}
	// 	else
	// 		break;
	// }
	// if (is_empty(mlx, temp, concat) == 1)
	// 	return (1);
	return (0);
}

