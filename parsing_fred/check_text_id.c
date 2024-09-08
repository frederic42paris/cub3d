/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:12:28 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/08 13:32:31 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



int	check_text_id(t_mlx *mlx, char *texture)
{
	int len;

	len = ft_strlen_word(texture);
	if (len == 2 && ft_strncmp(texture, "NO",2) == 0)
		mlx->count_no++;
	else if (len == 2 && ft_strncmp(texture, "SO",2) == 0)
		mlx->count_so++;
	else if (len == 2 && ft_strncmp(texture, "EA",2) == 0)
		mlx->count_ea++;
	else if (len == 2 && ft_strncmp(texture, "WE",2) == 0)
		mlx->count_we++;
	else if (len == 1 && ft_strncmp(texture, "C",1) == 0)
		mlx->count_c++;
	else if (len == 1 && ft_strncmp(texture, "F",1) == 0)
		mlx->count_f++;
	else
	{
		printf("Error\nWrong ID\n");
		return (1);
	}
	return (0);
}