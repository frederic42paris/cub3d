/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:52:01 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 11:02:05 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	store_data(t_mlx *mlx)
{
	char	*string;
	int		counter;
	char	*temp;
	char	*concat;
	char	*concat2;

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

	// int k;
	// k = 0;
	// while(k < 6)
	// {
	// 	printf("[%s]\n", mlx->textures[k]);
	// 	k++;
	// }
	// k = 0;
	// while (mlx->map_char[k])
	// {
	// 	printf("[%s]\n", mlx->map_char[k]);
	// 	k++;
	// }		

	return (0);
}