/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 12:19:19 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->map_char = NULL;
	if (check_argument(argv[1], argc) == 1)
		return (1);
	if (open_file(mlx, argv[1]) == 1)
		return (1);

	parse_elements(mlx);
	parse_map(mlx);
	// check_file(mlx);
	analyse_map(mlx);
	copymap(mlx);
	display_parsing(mlx);
	free(mlx);
	return (0);
}

// OLD VERSION

// int	check_file(t_mlx *mlx)
// {
// 	char	*string;
// 	char	*temp;
// 	char	*concat;
// 	int		i;

// 	while (1)
// 	{
// 		string = get_next_line(mlx->fd);
// 		if (string)
// 		{
// 			if (ft_strncmp(string, "NO", 2) == 0)
// 				mlx->path_north = ft_strdup_path(string + 3);
// 			else if (ft_strncmp(string, "SO", 2) == 0)
// 				mlx->path_south = ft_strdup_path(string + 3);
// 			else if (ft_strncmp(string, "WE", 2) == 0)
// 				mlx->path_west = ft_strdup_path(string + 3);
// 			else if (ft_strncmp(string, "EA", 2) == 0)
// 				mlx->path_east = ft_strdup_path(string + 3);
// 			else if (ft_strncmp(string, "F", 1) == 0)
// 			{
// 				i = 2;
// 				while (string[i] != '\0')
// 				{
// 					mlx->floor_r = ft_strdup_digit(string + i, &i);
// 					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
// 						i++;
// 					mlx->floor_g = ft_strdup_digit(string + i, &i);
// 					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
// 						i++;
// 					mlx->floor_b = ft_strdup_digit(string + i, &i);
// 					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
// 						i++;
// 				}
// 				mlx->floor_color = 	create_argb(0, mlx->floor_r, mlx->floor_g, mlx->floor_b);
// 			}
// 			else if (ft_strncmp(string, "C", 1) == 0)
// 			{
// 				i = 2;
// 				while (string[i] != '\0')
// 				{
// 					mlx->ceiling_r = ft_strdup_digit(string + i, &i);
// 					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
// 						i++;
// 					mlx->ceiling_g = ft_strdup_digit(string + i, &i);
// 					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
// 						i++;
// 					mlx->ceiling_b = ft_strdup_digit(string + i, &i);
// 					while(string[i] != '\0' && (string[i] > '9' || string[i] < '0'))
// 						i++;
// 				}
// 				mlx->ceiling_color = 	create_argb(0, mlx->ceiling_r, mlx->ceiling_g, mlx->ceiling_b);		
// 			}
// 			else if (ft_strrchr(string, '1'))
// 				break;
// 		}
// 		else
// 			break;
// 	}
// 	concat = ft_strdup("");
// 	temp = concat;
// 	concat = ft_strjoin(temp, string);
// 	free(string);
// 	free(temp);
// 	while (1)
// 	{
// 		string = get_next_line(mlx->fd);
// 		if (string)
// 		{
// 			concat = ft_strjoin(temp, string);
// 			free(string);
// 			free(temp);
// 		}
// 		else
// 			break;
// 	}
// 	if (is_empty(mlx, temp, concat) == 1)
// 		return (1);
// 	return (0);
// }