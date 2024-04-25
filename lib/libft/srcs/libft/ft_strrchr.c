/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:47:28 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/15 16:18:38 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	a;
	int		i;

	i = 0;
	a = c;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == a)
			return ((char *)str + i);
		i--;
	}
	return (0);
}
