/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:37:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/22 10:30:54 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	digit_counter(long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		count++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

int	ft_putnbr_count(long nb, int *ptr, int fd)
{
	if (nb < 0)
	{
		ft_putchar_count('-', ptr, fd);
		ft_putnbr_count(-nb, ptr, fd);
	}
	else if (nb < 10)
		ft_putchar_count(nb + 48, ptr, fd);
	else if (nb >= 10)
	{
		ft_putnbr_count(nb / 10, ptr, fd);
		ft_putchar_count((nb % 10) + 48, ptr, fd);
	}
	return (digit_counter(nb));
}
