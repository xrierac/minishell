/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:48:02 by tcampbel          #+#    #+#             */
/*   Updated: 2023/12/21 11:51:36 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	char	a;

	a = c;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == a)
			return ((char *)str);
		str++;
	}
	if (*str == a)
		return ((char *)str);
	return (0);
}
