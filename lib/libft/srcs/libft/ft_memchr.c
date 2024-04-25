/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:06:57 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/15 17:06:04 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char		a;
	unsigned const char	*str1;

	str1 = str;
	a = c;
	while (n > 0)
	{
		if (*str1 == a)
			return ((unsigned char *)str1);
		str1++;
		n--;
	}
	return (0);
}
