/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:22:28 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/25 15:53:43 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
	}
	return (0);
}
