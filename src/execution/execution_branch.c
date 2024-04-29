/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_branch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:46:29 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/29 16:20:02 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void check_token(t_lex *lex, t_env *env)
{
    if (lex->token == R_INPUT)
		r_input(lex->cmd_arr);
	if (lex->token == R_OUTPUT)
		r_output(lex->cmd_arr);
	if (lex->token == APPEND)
		r_append(lex->cmd_arr);
	if (lex->token == HEREDOC)
		r_heredoc(lex->cmd_arr);
}

static void	child_start(t_lex **lex_arr, t_env *env)
{
	int	i;
	int	cmd_id;

	i = 0;
	while (lex_arr[i])
	{
		if (lex_arr[i]->token == CMD)
			cmd_id = i;
		else
			check_token(lex_arr[i], env);
		i++;
	}
	execute(lex_arr[cmd_id], env);
}

int	execution_branch(t_sh *cmd_info)
{
	int 	i;
	int		status;
	pid_t	cpid;

	i = 0;
	while (cmd_info->lex_arr[i])
	{
		cpid = fork();
		if (cpid < 0)
			exit(0);
		if (cpid == 0)
			child_start(cmd_info->lex_arr[i], cmd_info->env);
		if (waitpid(cpid, &status, 0) == -1)
			exit(0);
    	i++;
	}
	return (WEXITSTATUS(status));
}