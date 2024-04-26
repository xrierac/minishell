/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:54:17 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/08 12:09:09 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"

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
