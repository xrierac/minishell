/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:42 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/06 12:10:51 by xriera-c         ###   ########.fr       */
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

int	ft_cd(char *str, char **env)
{
	size_t	size;
	char *ptr;
	char *buf;

	chdir(str);
	size = 2000;
	buf = (char *)malloc(size);
	if (!buf)
		return 0;
	ptr = getcwd(buf, size);
	printf("%s\n", ptr);
	change_pwd(env, ptr);
	free(ptr);
	return (0);
}
