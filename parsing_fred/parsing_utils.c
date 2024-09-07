/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:16:25 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/07 16:26:58 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	has_alpha_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	is_not_space(char c)
{
	if (c != ' ' && c != '\0' && c != '\t')
		return (1);
	else
		return (0);
}

size_t	ft_strlen_word(const char *s)
{
	size_t	i;

	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}