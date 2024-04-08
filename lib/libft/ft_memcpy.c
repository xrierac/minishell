/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:58:06 by xriera-c          #+#    #+#             */
/*   Updated: 2023/11/06 10:37:43 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst2;
	const unsigned char	*src2;

	if (dst == '\0' && src == '\0')
		return (dst);
	dst2 = dst;
	src2 = src;
	while (n > 0)
	{
		*dst2 = *src2;
		n--;
		dst2++;
		src2++;
	}
	return (dst);
}
