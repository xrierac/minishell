/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:52:14 by xriera-c          #+#    #+#             */
/*   Updated: 2023/11/03 15:34:28 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst2;
	const unsigned char	*src2;
	int					i;

	i = len - 1;
	if (dst > src && (dst - src) <= i)
	{
		dst2 = dst;
		src2 = src;
		while (i >= 0)
		{
			dst2[i] = src2[i];
			i--;
		}
	}
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}
