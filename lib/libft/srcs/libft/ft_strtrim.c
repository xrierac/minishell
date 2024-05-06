/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:01:30 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/06 14:02:36 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	char		*res;
	const char	*temp;

	if (!s1 || !set)
		return (0);
	temp = s1;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	res = ft_substr(s1, 0, i + 1);
	if (!res)
		return (0);
	s1 = temp;
	if (s1)
		free((char *)s1);
	return (res);
}
