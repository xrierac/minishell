/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:54:50 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/16 10:41:39 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if ((len + start) > ft_strlen(str))
		len = ft_strlen(str) - start;
	if (!str || ft_strlen(str) <= start || len == 0)
		return (ft_strdup(""));
	sub = (char *)malloc((len + 1));
	if (!sub)
		return (NULL);
	while (str[start + i] && len - i > 0)
	{
		sub[i] = str[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
