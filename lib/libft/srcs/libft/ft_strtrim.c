/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:01:30 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/16 15:28:11 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t		i;
	char		*res;
	char		*temp;

	if (!s1 || !set)
		return (0);
	temp = s1;
	while (*temp && ft_strchr(set, *temp))
		temp++;
	i = ft_strlen(temp);
	while (i && ft_strchr(set, temp[i]))
		i--;
	res = ft_substr(temp, 0, i + 1);
	if (!res)
		return (0);
	free(s1);
	return (res);
}
