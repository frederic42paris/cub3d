/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:13:22 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/09 17:08:04 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_rgb_value(char *str)
{
	int	i;
	char *path;
	long nb;

	path = NULL;
	i = 0;
	nb = 0;
	while (ft_isalnum(str[i]))
		i++;
	path = ft_substr(str, 0, i);
	nb = parse_input(path);
	free(path);
	if (nb > 255 || nb < 0)
	{
		printf("wrong rgb value\n");
		return (1);
	}
	return (0);
}

int	check_text_rgb(char *str)
{
	int len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen_word(str);
	if (len == 1
		&& (
			ft_strncmp(str, "C",1) == 0
			|| ft_strncmp(str, "F",1) == 0
			))
	{
		while (i < 3)
		{
			while (ft_isalnum(str[j]))
				j++;
			while (!ft_isalnum(str[j]))
				j++;
			if (check_rgb_value(str + j) == 1)
				return (1);
			i++;
		}
	}
	return (0);
}