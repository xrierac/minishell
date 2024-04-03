/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:12:27 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/12 11:37:52 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dec_to_hex(unsigned int n, char *base)
{
	char	*hex;
	char	coded;
	int		i;

	hex = malloc(20);
	if (hex == NULL)
		return (NULL);
	if (n == 0)
	{
		hex[0] = '0';
		hex[1] = '\0';
		return (hex);
	}
	i = 0;
	while (n != 0)
	{
		coded = base[n % 16];
		n = n / 16;
		hex[i] = coded;
		i++;
	}
	hex[i] = '\0';
	return (ft_strrev(hex));
}

char	*ft_dec_to_xhex(unsigned long n, char *base)
{
	char	*hex;
	char	coded;
	int		i;

	hex = malloc(25);
	if (hex == NULL)
		return (NULL);
	i = 0;
	if (n == 0)
		hex[i++] = '0';
	else
	{
		while (n != 0)
		{
			coded = base[n % 16];
			n = n / 16;
			hex[i] = coded;
			i++;
		}
	}
	hex[i++] = 'x';
	hex[i++] = '0';
	hex[i] = '\0';
	return (ft_strrev(hex));
}

char	*ft_utoa(unsigned int n)
{
	char	*str;
	size_t	i;

	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	str = malloc(15);
	if (!str)
		return (NULL);
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n = n / 10;
	}
	str[i] = '\0';
	return (ft_strrev(str));
}
