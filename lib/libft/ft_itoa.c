/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:01:22 by xriera-c          #+#    #+#             */
/*   Updated: 2023/11/03 15:01:29 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sizeint(int n)
{
	int	i;

	if (n <= 0)
		i = 2;
	else
		i = 1;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	num;
	int				sign;
	unsigned int	i;

	if (n == 0)
		return (ft_strdup("0"));
	str = malloc(sizeof(char) * sizeint(n));
	if (!str)
		return (0);
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	num = sign * n;
	i = 0;
	while (num != 0)
	{
		str[i++] = (num % 10) + '0';
		num = num / 10;
	}
	if (sign == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
