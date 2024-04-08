/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:18:59 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/12 11:36:51 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char	*get_conversion(char c, va_list ap)
{
	if (c == 'p')
		return (ft_dec_to_xhex(va_arg(ap, unsigned long), "0123456789abcdef"));
	if (c == 'd')
		return (ft_itoa(va_arg(ap, int)));
	if (c == 'i')
		return (ft_itoa(va_arg(ap, int)));
	if (c == 'u')
		return (ft_utoa(va_arg(ap, unsigned int)));
	if (c == 'x')
		return (ft_dec_to_hex(va_arg(ap, unsigned int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_dec_to_hex(va_arg(ap, unsigned int), "0123456789ABCDEF"));
	if (c == '%')
		return (ft_strdup("%"));
	return (NULL);
}

int	print_buffer(const char *format, va_list ap, int len)
{
	int		size;
	char	*buffer;

	if (format[len + 1] == 's')
	{
		buffer = va_arg(ap, char *);
		if (buffer == NULL)
			return (write(1, "(null)", 6));
		return (write(1, &buffer[0], ft_strlen(buffer)));
	}
	else
		buffer = get_conversion(format[len + 1], ap);
	if (buffer == NULL)
		return (-1);
	else
		size = write(1, &buffer[0], ft_strlen(buffer));
	free(buffer);
	return (size);
}

int	print_chrs(const char *format, va_list ap, int len)
{
	int		size;
	int		check;

	size = 0;
	while (format[++len])
	{
		check = 0;
		if (format[len] == '%' && format[len + 1] == 'c')
		{
			check = ft_putchar(va_arg(ap, int));
			len++;
		}
		else if (format[len] == '%' && ft_inset(format[len + 1], "spdiuxX%"))
		{
			check = print_buffer(format, ap, len);
			len++;
		}
		else if (format[len] != '%')
			check = write(1, &format[len], 1);
		if (check == -1)
			return (-1);
		size += check;
	}
	return (size);
}

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	int				len;
	int				bytes;

	len = -1;
	if (!format)
		return (-1);
	va_start(ap, format);
	bytes = print_chrs(format, ap, len);
	va_end(ap);
	return (bytes);
}
