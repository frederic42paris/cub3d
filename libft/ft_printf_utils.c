/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:39:50 by arguez            #+#    #+#             */
/*   Updated: 2024/02/08 16:02:57 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(int n)
{
	int	counter;

	if (n == 0)
		return (1);
	counter = 0;
	if (n < 0)
	{
		n = n * -1;
		counter++;
	}
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	new;

	new = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		new = -n;
	}
	if (new >= 10)
	{
		ft_putnbr_fd(new / 10, fd);
		ft_putnbr_fd(new % 10, fd);
	}
	else
		ft_putchar_fd(new + '0', fd);
}

int	ft_numput(int n, int fd)
{
	ft_putnbr_fd(n, fd);
	return (count_digits(n));
}
