/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:41:05 by tcampbel          #+#    #+#             */
/*   Updated: 2024/01/02 12:12:51 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned const char	*s1;
	unsigned const char	*s2;

	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	if (n == 0)
		return (0);
	while (*s1 == *s2 && *s1 && --n)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
