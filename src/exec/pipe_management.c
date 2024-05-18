/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:13:51 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/18 18:16:33 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	close_pipes(int in, int fda, int fdb)
{
	if (in > 0)
		close(in);
	close(fda);
	close(fdb);
	return (0);
}

int	pipe_management(t_sh *sh, int index, int in, int out)
{
	if (sh->pipes == 0)
		return (0);
	if (index > 0)
	{
		if (dup2(in, STDIN_FILENO) == -1)
			return (1);
		close(in);
	}
	if (index < sh->processes - 1)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
			return (1);
		close(out);
	}
	return (0);
}
