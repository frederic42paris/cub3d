/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:18:57 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/06 13:35:05 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_message(int num)
{
	if (num == 1)
		ft_printf("Error\nNumber of arguments incorrect\n");
	else if (num == 2)
		ft_printf("Error\nFile name incorrect\n");
	else if (num == 3)
		ft_printf("Error\nFile not found\n");
	else if (num == 4)
		ft_printf("Error\nEmpty map\n");
	else if (num == 5)
		ft_printf("Error\nEmpty line in map\n");
	else if (num == 6)
		ft_printf("Error\nElements number incorrect\n");
	else if (num == 7)
		ft_printf("Error\nMap not rectangular\n");
	else if (num == 8)
		ft_printf("Error\nWalls incorrect\n");
	else if (num == 9)
		ft_printf("Error\nWindow closed due to invalid path.\n");
	else if (num == 10)
		ft_printf("Error\nUnknown element\n");
	else if (num == 11)
		ft_printf("Error\nWrong id\n");
	else if (num == 12)
		ft_printf("Error\nToo many id\n");
	else if (num == 13)
		ft_printf("Error\nDup id\n");
	else if (num == 14)
		ft_printf("Error\nXpm not found\n");
	else if (num == 15)
		ft_printf("Error\nWrong rgb\n");
}