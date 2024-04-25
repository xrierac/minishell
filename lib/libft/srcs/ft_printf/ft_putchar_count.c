/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:05:19 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/22 10:20:37 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_count(char a, int *ptr, int fd)
{
	if (*ptr == -1)
		return (-1);
	if (write(fd, &a, 1) == -1)
	{
		*ptr = -1;
		return (-1);
	}
	return (1);
}
