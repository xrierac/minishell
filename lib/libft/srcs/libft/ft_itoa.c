/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:12:14 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/20 16:15:47 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_counter(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*mod_str(long n, char *str, int len)
{
	str[len] = 0;
	if (n < 0)
	{
		*str = '-';
		n *= -1;
		while (--len)
		{
			str[len] = (n % 10) + 48;
			n /= 10;
		}
		return (str);
	}
	while (len--)
	{
		str[len] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		len;

	n = nb;
	len = len_counter(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (n == 0)
	{
		*str++ = '0';
		*str = '\0';
		return (str - 1);
	}
	mod_str(n, str, len);
	return (str);
}
