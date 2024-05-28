/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_branch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:21 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/28 17:13:09 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <signal.h>

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

static int	check_token(t_lex *lex, t_env *env)
{
	if (lex->token == R_INPUT)
		return (r_input(lex->cmd_arr));
	if (lex->token == R_OUTPUT)
		return (r_output(lex->cmd_arr));
	if (lex->token == APPEND)
		return (r_append(lex->cmd_arr));
	if (lex->token == VALID_HD)
		return (r_heredoc(lex));
	return (0);
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
		{
			if (check_token(sh->lex_arr[index][i], sh->env) == 1)
				exit(1);
		}
		i++;
	}
	exit(execute(sh->lex_arr[index][cmd_id], sh->env));
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
	receive_signal(0);
	if (sh->processes > 899)
	{
		ft_putstr_fd("Too many pipes. This is not Super Mario Bros\n", 2);
		return (1);
	}
	val = run_builtin(sh, sh->lex_arr[0][0]->cmd_arr);
	if (val >= 0)
		return (val);
	val = start_proc(sh, in, i);
	return (val);
}
