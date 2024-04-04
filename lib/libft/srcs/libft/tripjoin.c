/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tripjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:28:01 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/21 14:29:00 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*tripjoin(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*s4;

	i = -1;
	j = -1;
	k = -1;
	if (!s1 || !s2 || !s3)
		return (NULL);
	s4 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	if (!s4)
		return (NULL);
	while (s1[++i])
		s4[i] = s1[i];
	while (s2[++j])
		s4[i++] = s2[j];
	while (s3[++k])
		s4[i++] = s3[k];
	s4[i] = '\0';
	return (s4);
}
