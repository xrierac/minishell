/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:21:51 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/24 17:56:24 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
char	*get_path(char *cmd, t_env *env)
{
	char	*prog;
	char	*path;
	int		i;

	prog = ft_strjoin("/", cmd);
	if (!prog)
		error_exit(0);
	i = 0;
	while (env->path_arr[i])
	{
		path = ft_strjoin(arr[i], prog);
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

void	execute(t_lex *lex, t_env *env)
{
	if (execve(lex->cmd_arr[0], lex->cmd_arr, env->env_arr) == -1)
		if (execve(get_path(lex->cmd_arr[0], env), lex->cmd_arr, env->env_arr) == -1)
			error_exit(lex->cmd_arr[0], 127);

}
