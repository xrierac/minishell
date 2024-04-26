/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:42 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/09 17:07:39 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	change_pwd(char **env, char *pwd)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PWD=", 4))
			break ;
	if (!env[i])
		return ;
	free(env[i]);
	env[i] = ft_strjoin("PWD=", pwd);
}

void	ft_cd(char *str, char **env)
{
	size_t	size;
	char *ptr;
	char *buf;

	chdir(str);
	size = 2000;
	buf = (char *)malloc(size);
	if (!buf)
		return ;
	ptr = getcwd(buf, size);
	printf("%s\n", ptr);
	change_pwd(env, ptr);
	free(ptr);
}
