/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:26:20 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/02 10:27:18 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*str3;

	i = 0;
	j = 0;
	str3 = (char *)malloc((ft_strlen(str1) + ft_strlen(str2)) + 1);
	if (!str3)
		return (NULL);
	while (str1[i])
	{
		str3[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		str3[i] = str2[j];
		j++;
		i++;
	}
	str3[i] = '\0';
	free(str1);
	free(str2);
	return (str3);
}
