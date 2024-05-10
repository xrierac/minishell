/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:21:51 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/10 12:16:48 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_cmd(char *cmd, t_env *env)
{
	char	*prog;
	char	*path;
	int		i;

	prog = ft_strjoin("/", cmd);
	if (!prog)
		exit(0);
	i = 0;
	while (env->path_arr[i])
	{
		path = ft_strjoin(env->path_arr[i], prog);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		i++;
	}
	if (env->path_arr[i] == 0)
		path = 0;
	free(prog);
	return (path);
}

int	execute(t_lex *lex, t_env *env)
{
	if (builtin_check(lex, env) == 0)
		return (0);
	if (execve(lex->cmd_arr[0], lex->cmd_arr, env->env_arr))
		if (execve(find_cmd(lex->cmd_arr[0], env), lex->cmd_arr, env->env_arr))
			return (-1);
	return (0);
}
