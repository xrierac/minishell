/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:21:51 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/06 18:18:29 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_dir(char *str)
{
	DIR	*ptr;

	ptr = opendir(str);
	if (!ptr)
		return (1);
	errno = EISDIR;
	closedir(ptr);
	return (0);
}

static char	*find_cmd(char *cmd, t_env *env)
{
	char	*prog;
	char	*path;
	int		i;

	prog = ft_strjoin("/", cmd);
	if (!prog)
		return (cmd);
	i = 0;
	while (env->path_arr[i])
	{
		path = ft_strjoin(env->path_arr[i], prog);
		if (!path)
		{
			generic_error("", "malloc");
			break ;
		}
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		i++;
	}
	if (env->path_arr[i] == 0)
		path = cmd;
	free(prog);
	return (path);
}

int	check_access(char *str, t_lex *lex, t_env *env)
{
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) == 0)
		{
			if (is_dir(str) == 0)
			{
				generic_error("", str);
				return (126);
			}
			execve(str, lex->cmd_arr, env->env_arr);
			return (generic_error("", str));
		}
		generic_error("", str);
		return (126);
	}
	return (0);
}

int	execute(t_lex *lex, t_env *env)
{
	int		val;

	if (lex->cmd_arr[0][0] == '\0')
		return (error_cmd_not_found(lex->cmd_arr[0]));
	if (builtin_check(lex->cmd_arr, env) != -1)
		return (0);
	if (ft_strchr(lex->cmd_arr[0], '/'))
	{
		val = check_access(lex->cmd_arr[0], lex, env);
		if (val != 0)
			return (val);
		generic_error("", lex->cmd_arr[0]);
		return (127);
	}
	else
	{
		val = check_access(find_cmd(lex->cmd_arr[0], env), lex, env);
		if (val != 0)
			return (val);
	}
	return (error_cmd_not_found(lex->cmd_arr[0]));
}
