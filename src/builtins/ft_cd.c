/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:42 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/13 15:48:18 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	change_oldpwd(t_env *env_s, char *pwd)
{
	char *temp;
	
	temp = ft_strjoin("OLDPWD=", pwd);
	ft_export(env_s, temp);
	free(temp);
}

static void	change_pwd(t_env *env_s, char *pwd)
{
	char *temp;
	
	temp = ft_strjoin("PWD=", pwd);
	ft_export(env_s, temp);
	free(temp);
}

int	ft_cd(char *str, t_env *env_s)
{
	size_t	size;
	char	*ptr;
	char	*buf;

	size = 2000;
	buf = (char *)malloc(size);
	if (!buf)
		return (0);
	ptr = getcwd(buf, size);
	change_oldpwd(env_s, ptr);
	if (!str)
		str = ft_getenv("HOME", env_s->env_arr);
	if (chdir(str))
		return (1);
	ptr = getcwd(buf, size);
	change_pwd(env_s, ptr);
	free(ptr);
	return (0);
}
