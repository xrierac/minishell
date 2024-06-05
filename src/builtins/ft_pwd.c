/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:19 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/05 18:18:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *return_ptr_cwd(t_env *env_s)
{
	char *buf;
	char *ptr;

	buf = (char *)malloc(MAX_ARGS);
	if (!buf)
	{
		generic_error("", "cwd");
		return (NULL);
	}
	ptr = getcwd(buf, MAX_ARGS);
	if (!ptr)
	{
		free(buf);
		buf = ft_getenv("PWD", env_s->env_arr);
		if (buf != 0)
			buf = ft_strdup(buf);
		else
		{
			generic_error("Unable to get working directory", "");
			return (NULL);
		}
	}
	return (buf);
}

int	ft_pwd(t_env *env)
{
	char	*buf;

	buf = return_ptr_cwd(env);
	if (buf)
	{
		printf("%s\n", buf);
		free(buf);
		return (0);
	}
	return (1);
}
