/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:18:21 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 12:18:21 by ftanon           ###   ########.fr       */
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

int	parse_map(t_mlx *mlx)
{
	char	*string;
	char	*temp;
	char	*concat;

	concat = ft_strdup("");
	while (1)
	{
		temp = concat;
		string = get_next_line(mlx->fd);
		if (string)
		{
			if (has_alpha_num(string))
			{
				concat = ft_strjoin(temp, string);
				free(temp);
			}
			free(string);
		}
		else
			break;
	}
	if (is_empty(mlx, temp, concat) == 1)
		return (1);
	return (0);
}