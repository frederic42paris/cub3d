/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:18:26 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 10:20:18 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_argument(char *filename, int inputnumber)
{
	char	*string;

	if (inputnumber != 2)
	{
		error_message(1);
		return (1);
	}
	string = ft_strrchr(filename, '.');
	if (string == 0)
	{
		error_message(2);
		return (1);
	}
	if (ft_strncmp(string, ".cub", 4) != 0)
	{
		error_message(2);
		return (1);
	}
	return (0);
}