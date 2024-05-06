/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:42 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/06 15:41:10 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	change_pwd(char **env, char *pwd, int signal)
{
	int	i;

	i = -1;
	if (signal == 0)
	{
		while (env[++i])
			if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
				break ;
		if (!env[i])
			return ;
		free(env[i]);
		env[i] = ft_strjoin("OLDPWD=", pwd);
	}
	else
	{
		while (env[++i])
			if (ft_strncmp(env[i], "PWD=", 4) == 0)
				break ;
		if (!env[i])
			return ;
		free(env[i]);
		env[i] = ft_strjoin("PWD=", pwd);
	}
}

int	ft_cd(char *str, char **env)
{
	size_t	size;
	char	*ptr;
	char	*buf;

	size = 2000;
	buf = (char *)malloc(size);
	if (!buf)
		return (0);
	ptr = getcwd(buf, size);
	change_pwd(env, ptr, 0);
	if (chdir(str))
		printf("Error\n");
	ptr = getcwd(buf, size);
	change_pwd(env, ptr, 1);
	free(ptr);
	return (0);
}
