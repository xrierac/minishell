/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:26:42 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/22 10:36:52 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	str_handler(char flag, va_list ap, int *ptr, int fd)
{
	int	count;

	count = 0;
	if (flag == 'c')
		count += ft_putchar_count(va_arg(ap, int), ptr, fd);
	else if (flag == 's')
		count += ft_putstr_count(va_arg(ap, char *), ptr, fd);
	else if (flag == 'd' || flag == 'i')
		count += ft_putnbr_count(va_arg(ap, int), ptr, fd);
	else if (flag == 'x' || flag == 'X')
		count += ft_puthex_count(va_arg(ap, unsigned int), flag, ptr, fd);
	else if (flag == 'u')
		count += ft_putnbr_count(va_arg(ap, unsigned int), ptr, fd);
	else if (flag == 'p')
	{
		count += ft_putstr_count("0x", ptr, fd);
		count += ft_puthex_count(va_arg(ap, unsigned long long), flag, ptr, fd);
	}
	else if (flag == '%')
		count += ft_putchar_count('%', ptr, fd);
	return (count);
}
