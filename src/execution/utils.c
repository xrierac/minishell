/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:54:17 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/07 09:38:11 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/includes/libft.h"

size_t	array_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*ft_getenv(const char *name, char **env)
{
	int		i;
	size_t	len;
	
	len = ft_strlen(name);
	i = 0;
	while (env[i] && ft_strncmp(env[i], name, len))
		i++;
	if (!env[i])
		return (0);
	return (env[i] + len + 1);
}
