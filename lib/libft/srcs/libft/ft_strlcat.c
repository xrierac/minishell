/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:10:31 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/15 15:05:52 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	destlen;
	size_t	j;
	size_t	srclen;

	destlen = 0;
	srclen = ft_strlen(src);
	while (dest[destlen] && dstsize > destlen)
		destlen++;
	if (!dest && dstsize == 0)
		return (0);
	if (dstsize == 0 || dest[destlen])
		return (srclen + destlen);
	j = 0;
	while (src[j] && (dstsize - 1) > (j + destlen))
	{
		dest[destlen + j] = src[j];
		j++;
	}
	dest[destlen + j] = 0;
	return (destlen + srclen);
}
