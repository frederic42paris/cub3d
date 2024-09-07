/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:12:28 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 13:36:50 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen_word_error(const char *s)
{
	size_t	i;

	i = 0;
	while (is_not_space(s[i]))
		i++;
	return (i);
}

int	is_identifier_error(t_mlx *mlx, char *str)
{
	int len;

	len = ft_strlen_word_error(str);
	if (len == 2 && ft_strncmp(str, "NO",2) == 0)
		mlx->count_no++;
	else if (len == 2 && ft_strncmp(str, "SO",2) == 0)
		mlx->count_so++;
	else if (len == 2 && ft_strncmp(str, "EA",2) == 0)
		mlx->count_ea++;
	else if (len == 2 && ft_strncmp(str, "WE",2) == 0)
		mlx->count_we++;
	else if (len == 1 && ft_strncmp(str, "C",1) == 0)
		mlx->count_c++;
	else if (len == 1 && ft_strncmp(str, "F",1) == 0)
		mlx->count_f++;
	else
	{
		printf("Error\nWrong ID\n");
		return (1);
	}
	return (0);
}

int	parse_information_error(t_mlx *mlx, char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (is_identifier_error(mlx, str + i) == 1)
		return (1);
	return (0);
}

int	check_identifier(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (parse_information_error(mlx, mlx->textures[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}