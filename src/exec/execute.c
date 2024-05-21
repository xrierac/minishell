/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:21:51 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/21 14:29:23 by xriera-c         ###   ########.fr       */
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
	char	*cmd;

	if (builtin_check(lex->cmd_arr, env) != -1)
		return (0);
	if (access(lex->cmd_arr[0], F_OK) == 0)
	{
		if (access(lex->cmd_arr[0], X_OK) == 0)
		{
			execve(lex->cmd_arr[0], lex->cmd_arr, env->env_arr);
			return (generic_error("", lex->cmd_arr[0]));
		}
		return (127 - generic_error("", lex->cmd_arr[0]));
	}
	cmd = find_cmd(lex->cmd_arr[0], env);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			execve(cmd, lex->cmd_arr, env->env_arr);
			return (generic_error("", cmd));
		}
		return (127 - generic_error("", cmd));
	}
	return (error_cmd_not_found(lex->cmd_arr[0]));
}
