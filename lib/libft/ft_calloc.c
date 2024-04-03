/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:58:33 by xriera-c          #+#    #+#             */
/*   Updated: 2023/11/09 11:58:30 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	len;
	int		i;
	char	*str;

	i = 0;
	if ((count > 2147483648 && size > 1) || (count > 1 && size > 2147483648))
		return (0);
	len = count * size;
	str = malloc(len);
	if (!str)
		return (0);
	while (len > 0)
	{
		str[i++] = '\0';
		len--;
	}
	return (str);
}
