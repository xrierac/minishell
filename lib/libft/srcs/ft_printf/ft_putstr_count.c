/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:09:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/22 10:28:55 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_count(char *str, int *ptr, int fd)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (ft_putstr_count("(null)", ptr, fd));
	while (*str)
	{
		count += ft_putchar_count(*str, ptr, fd);
		str++;
	}
	return (count);
}
