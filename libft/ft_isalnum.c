/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:19:41 by arguez            #+#    #+#             */
/*   Updated: 2023/11/06 11:21:55 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (((c >= 65) && (c <= 90))
		|| ((c >= 97) && (c <= 122))
		|| ((c >= 48) && (c <= 57)))
		return (1);
	return (0);
}