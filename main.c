/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:58:17 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 19:19:43 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	ender(t_mlx *mlx)
// {
// 	if (mlx->map_int != NULL)
// 		double_free((void **)mlx->map_int);
// 	if (mlx->map_char != NULL)
// 		double_free((void **)mlx->map_char);
// 	if (mlx->path_north != NULL)
// 		free(mlx->path_north);
// 	if (mlx->path_south != NULL)
// 		free(mlx->path_south);
// 	if (mlx->path_east != NULL)
// 		free(mlx->path_east);
// 	if (mlx->path_west != NULL)
// 		free(mlx->path_west);
// 	free(mlx);
// }


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

int	is_empty2(t_mlx *mlx, char *temp, char *concat)
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
	mlx->textures = ft_split(concat, '\n');
	free(concat);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	char	*string;
	int		counter;
	char	*temp;
	char	*concat;
	char	*concat2;

	check_argument(argv[1], argc);
	mlx = malloc(sizeof(t_mlx));
	mlx->textures = malloc(6 * sizeof(char *) + 1);
	open_file(mlx, argv[1]);
	counter = 0;
	concat2 = ft_strdup("");
	while (1)
	{
		if (counter == 6)
			break;
		string = NULL;
		temp = concat2;
		string = get_next_line(mlx->fd);
		if (string)
		{
			if (has_alpha_num(string))
			{
				concat2 = ft_strjoin(temp, string);
				free(string);
				free(temp);
				// mlx->textures[counter] = ft_strdup(string);
				// parse_information(mlx, string);
				counter++;
			}
			else
				free(string);
		}
		else
			break;
	}
	if (is_empty2(mlx, temp, concat2) == 1)
		return (1);
	while (1)
	{
		string = get_next_line(mlx->fd);
		if (string)
		{
			if (!has_alpha_num(string))
			{
				free(string);
				continue;
			}
			else
				break;
		}
		else
			break;
	}
	if (string == NULL)
		return (1);
	else
	{
		concat = ft_strdup("");
		temp = concat;
		concat = ft_strjoin(temp, string);
		free(string);
		free(temp);
	}
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

	int k;
	k = 0;
	while(k < 6)
	{
		printf("[%s]\n", mlx->textures[k]);
		k++;
	}
	k = 0;
	while (mlx->map_char[k])
	{
		printf("[%s]\n", mlx->map_char[k]);
		k++;
	}		
	// if (mlx == NULL)
		// return (printf("Error: memory allocation for shared data struct failed\n"), 1);
	
	// mlx->map_int = parser(argv[1], mlx);
	// if (mlx->map_int == NULL)
	// 	return (ender(mlx), 1);
	// display_parsing(mlx);
	// ender(mlx);
	return (0);
}
