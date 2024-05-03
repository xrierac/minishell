/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_branch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:46:29 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/03 10:43:03 by xriera-c         ###   ########.fr       */
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

static void	child_start(t_sh *sh_data, int index, int **pipefd)
{
	int	i;
	int	cmd_id;

	i = 0;
	pipe_management(sh_data, index, pipefd);
	while (sh_data->lex_arr[index][i])
	{
		if (sh_data->lex_arr[index][i]->token == CMD)
			cmd_id = i;
		else
			check_token(sh_data->lex_arr[index][i], sh_data->env);
		i++;
	}
	execute(sh_data->lex_arr[index][cmd_id], sh_data->env);
}

int	execution_branch(t_sh *sh_data)
{
	int		i;
	int		pipefd[MAX_FD][2];
	pid_t	cpid[MAX_FD];

	i = -1;
	while (++i < sh_data->pipes)
		if (pipe(pipefd[i]) == -1)
			exit(0);
	i = -1;
	while (++i < sh_data->len)
	{
		cpid[i] = fork();
		if (cpid[i] < 0)
			exit(0);
		if (cpid[i] == 0)
			child_start(sh_data, i, pipefd);
	}
	while (--i >= sh_data->len)
		wait(NULL);
	return (1);
}
