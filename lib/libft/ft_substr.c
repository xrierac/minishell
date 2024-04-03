/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:04:32 by xriera-c          #+#    #+#             */
/*   Updated: 2023/11/06 12:03:47 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;

	if (!s || start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if ((len + start) > ft_strlen(s))
		len = ft_strlen(s) - start;
	substring = malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (0);
	ft_memmove(substring, &s[start], len);
	substring[len] = '\0';
	return (substring);
}
