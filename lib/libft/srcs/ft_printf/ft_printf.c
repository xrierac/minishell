/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:13:37 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/22 10:46:49 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, const char *str, ...)
{
	int		arg_count;
	va_list	ap;
	int		ptr;

	ptr = 1;
	arg_count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			arg_count += str_handler(*str, ap, &ptr, fd);
		}
		else
			arg_count += ft_putchar_count(*str, &ptr, fd);
		str++;
	}
	if (ptr == -1)
	{
		va_end(ap);
		return (-1);
	}
	va_end(ap);
	return (arg_count);
}
