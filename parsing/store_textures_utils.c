/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:08:05 by arguez            #+#    #+#             */
/*   Updated: 2024/09/11 12:48:16 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_argb(int a, int r, int g, int b)
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
	if (dest == NULL)
		return (-1);
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		dest[i] = s[i];
		i++;
	}
	*j = *j + i;
	dest[i] = '\0';
	final = ft_atoi(dest);
	free(dest);
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
