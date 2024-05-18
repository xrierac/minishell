/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_branch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:21 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/18 18:21:20 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	wait_processes(pid_t cpid[], int i)
{
	int	status;

	while (--i >= 0)
	{
		if (waitpid(cpid[i], &status, 0) == -1)
			perror("ERROR");
	}
	return (WEXITSTATUS(status));
}

static void	check_token(t_lex *lex, t_env *env)
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

static void	child_start(t_sh *sh, int index, int in, int fd[])
{
	int	i;
	int	cmd_id;

	i = 0;
	if (sh->processes == 1)
		close_pipes(in, fd[0], fd[1]);
	pipe_management(sh, index, in, fd[1]);
	while (sh->lex_arr[index][i])
	{
		if (sh->lex_arr[index][i]->token == CMD)
			cmd_id = i;
		else
			check_token(sh->lex_arr[index][i], sh->env);
		i++;
	}
	if (execute(sh->lex_arr[index][cmd_id], sh->env) == -1)
		error_cmd_not_found(sh->lex_arr[index][0]->cmd_arr[0]);
	exit(1);
}

static int	start_proc(t_sh *sh, int in, int i)
{
	int		fd[2];
	pid_t	cpid[900];

	while (++i < sh->processes)
	{
		if (pipe(fd) == -1)
			return (generic_error("", "pipe"));
		cpid[i] = fork();
		if (cpid[i] < 0)
		{
			generic_error("", "fork");
			close_pipes(in, fd[0], fd[1]);
			wait_processes(cpid, i);
			return (1);
		}
		if (cpid[i] == 0)
			child_start(sh, i, in, fd);
		if (in > 0)
			close(in);
		in = fd[0];
		close(fd[1]);
	}
	if (in > 0)
		close(in);
	return (wait_processes(cpid, i));
}

int	execution_branch(t_sh *sh)
{
	int	val;
	int	in;
	int	i;
	
	i = -1;
	in = 0;
	val = run_builtin(sh, sh->lex_arr[0][0]->cmd_arr);
	if (val >= 0)
		return (val);
	val = start_proc(sh, in, i);
	return (val);
}
