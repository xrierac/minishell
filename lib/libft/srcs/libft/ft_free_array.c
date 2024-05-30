/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:36:48 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/30 15:50:12 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return ;
	else
	{
		if (str[i])
		{
			while (str[i])
			{
				free(str[i]);
				str[i] = NULL;
				i++;
			}
		}
		free(str);
		str = NULL;
	}
}
