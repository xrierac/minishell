/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:13:51 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/13 13:52:44 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	close_other_hd_fd(t_sh *msh)
{
	int	i;
	int	j;

	i = -1;
	while (msh->lex_arr[++i])
	{
		j = -1;
		while (msh->lex_arr[i][++j])
		{
			if (msh->lex_arr[i][j]->token == VALID_HD)
			{
				if (msh->lex_arr[i][j]->fd > 0)
					close(msh->lex_arr[i][j]->fd);
			}
		}
	}
	return (0);
}

int	close_pipes(int in, int fda, int fdb)
{
	if (in > 0)
		close(in);
	close(fda);
	close(fdb);
	return (0);
}

int	pipe_management(t_sh *sh, int index, int in, int fd[])
{
	if (sh->pipes == 0)
	{
		close_pipes(in, fd[0], fd[1]);
		return (0);
	}
	if (index > 0)
	{
		if (dup2(in, STDIN_FILENO) == -1)
		{
			close_pipes(in, fd[0], fd[1]);
			return (1);
		}
		close(in);
	}
	if (index < sh->processes - 1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			close_pipes(in, fd[0], fd[1]);
			return (1);
		}
	}
	close_pipes(0, fd[0], fd[1]);
	return (0);
}
