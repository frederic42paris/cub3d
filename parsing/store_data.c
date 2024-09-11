/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:52:01 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/11 11:44:03 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	split_string_1(t_mlx *mlx, char *concat)
{
	mlx->textures = ft_split(concat, '\n');
	free(concat);
	return (0);
}

int	store_six_line(t_mlx *mlx, char **string)
{
	int		counter;
	char	*concat;
	char	*temp;

	counter = 0;
	concat = ft_strdup("");
	while (1)
	{
		if (counter == 6)
			break ;
		temp = concat;
		*string = get_next_line(mlx->fd);
		if (*string)
		{
			if (has_alpha_num(*string))
				ssl_subrountine(string, &concat, &temp, &counter);
			else
				free(*string);
		}
		else
			return (free(concat), printf("Error\nIncomplete file\n"), 1);
	}
	if (split_string_1(mlx, concat) == 1)
		return (1);
	return (0);
}

int	skip_empty_line(t_mlx *mlx, char **string)
{
	while (1)
	{
		*string = get_next_line(mlx->fd);
		if (*string)
		{
			if (!has_alpha_num(*string))
			{
				free(*string);
				continue ;
			}
			else
				break ;
		}
		else
		{
			printf("Error\nIncomplete file\n");
			return (1);
		}
	}
	return (0);
}

int	store_map_char(t_mlx *mlx, char **string)
{
	char	*temp;
	char	*concat;

	concat = ft_strdup("");
	temp = concat;
	concat = ft_strjoin(temp, *string);
	free(*string);
	free(temp);
	while (1)
	{
		*string = NULL;
		temp = concat;
		*string = get_next_line(mlx->fd);
		if (*string)
		{
			concat = ft_strjoin(temp, *string);
			free(*string);
			free(temp);
		}
		else
			break ;
	}
	if (split_string_2(mlx, concat) == 1)
		return (1);
	return (0);
}

int	store_data(t_mlx *mlx)
{
	char	*string;

	string = NULL;
	if (store_six_line(mlx, &string))
		return (1);
	if (skip_empty_line(mlx, &string))
		return (1);
	if (string == NULL)
	{
		printf("Error\nIncomplete file\n");
		return (1);
	}
	else
		store_map_char(mlx, &string);
	return (0);
}
