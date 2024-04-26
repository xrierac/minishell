/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:42:09 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/22 10:21:23 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_counter(unsigned long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

int	ft_puthex_count(unsigned long nb, char flag, int *ptr, int fd)
{
	char	*dict;

	dict = "0123456789abcdef";
	if (nb < 16)
	{
		if (flag == 'X' && dict[nb] >= 97 && dict[nb] <= 102)
			ft_putchar_count(dict[nb] - 32, ptr, fd);
		else
			ft_putchar_count(dict[nb], ptr, fd);
	}
	else
	{
		ft_puthex_count(nb / 16, flag, ptr, fd);
		ft_puthex_count(nb % 16, flag, ptr, fd);
	}
	return (hex_counter(nb));
}
