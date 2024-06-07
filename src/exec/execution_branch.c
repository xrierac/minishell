/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_branch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:21 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/06 18:19:44 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	wait_processes(pid_t cpid[], int nproc)
{
	int	i;
	int	status;

	i = 0;
	while (i < nproc)
	{
		if (waitpid(cpid[i], &status, 0) == -1)
			perror("ERROR");
		i++;
	}
	return (WEXITSTATUS(status));
}

static int	check_token(t_lex *lex)
{
	if (lex->token == R_INPUT)
		return (r_input(lex->cmd_arr));
	if (lex->token == R_OUTPUT)
		return (r_output(lex->cmd_arr));
	if (lex->token == APPEND)
		return (r_append(lex->cmd_arr));
	if (lex->token == VALID_HD)
		return (r_heredoc(lex));
	if (lex->token == AMB_RD)
		return (1);
	return (0);
}

static void	child_start(t_sh *sh, int index, int in, int fd[])
{
	int	i;
	int	cmd_id;

	i = 0;
	cmd_id = -1;
	if (sh->processes == 1)
		close_pipes(in, fd[0], fd[1]);
	pipe_management(sh, index, in, fd[1]);
	while (sh->lex_arr[index][i])
	{
		if (sh->lex_arr[index][i]->token == CMD)
			cmd_id = i;
		else
		{
			if (check_token(sh->lex_arr[index][i]) == 1)
				exit_child(sh);
		}
		i++;
	}
	if (cmd_id != -1)
		i = execute(sh->lex_arr[index][cmd_id], sh->env);
	else
		i = 0;
	free_all(sh);
	exit(i);
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
			close_pipes(in, fd[0], fd[1]);
			wait_processes(cpid, i + 1);
			return (generic_error("", "fork"));
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
	val = -1;
	receive_signal(2);
	if (sh->processes > 899)
	{
		ft_putstr_fd("Too many pipes. This is not Super Mario Bros\n", 2);
		return (1);
	}
	if (sh->lex_arr[0][0])
		val = run_builtin(sh, sh->lex_arr[0][0]->cmd_arr);
	if (val >= 0)
		return (val);
	val = start_proc(sh, in, i);
	if (g_num == SIGINT)
		return (130);
	if (g_num == SIGQUIT)
		return (131);
	return (val);
}
