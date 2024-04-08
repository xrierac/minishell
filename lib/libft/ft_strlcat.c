/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:50:42 by xriera-c          #+#    #+#             */
/*   Updated: 2023/11/06 09:10:52 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	size_t			lendest;
	size_t			lensrc;

	if (!dst && dstsize == 0)
		return (0);
	lendest = ft_strlen(dst);
	lensrc = ft_strlen(src);
	i = lendest;
	j = 0;
	if (dstsize == 0 || lendest >= dstsize)
		return (dstsize + lensrc);
	while (src[j] && j < (dstsize - lendest - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (lendest + lensrc);
}
