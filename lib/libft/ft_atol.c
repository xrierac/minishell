/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:07:16 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/26 12:18:07 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

long	ft_atol(const char *nptr)
{
	long	i;
	int		sign;

	i = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		i = (i * 10) + (*nptr - '0');
		if (i > LONG_MAX && sign == 1)
			return (-1);
		else if (i > LONG_MAX && sign == -1)
			return (0);
		nptr++;
	}
	return (i * sign);
}
