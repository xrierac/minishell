/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:13:51 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/03 16:53:25 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	close_pipes(int pipefd[][2], int index, t_sh *sh_data)
{
	int	i;

	i = 0;
	while (i < sh_data->pipes)
	{
		if (i != index)
			close(pipefd[i][1]);
		if (i != index - 1)
			close(pipefd[i][0]);
		i++;
	}
	return (1);
}

int	pipe_management(t_sh *sh_data, int index, int pipefd[][2])
{
	if (sh_data->len == 1)
		return (0);
	if (index > 0 && index <= sh_data->len - 1)
	{
		if (dup2(pipefd[index - 1][0], STDIN_FILENO) == -1)
			return (1);
		close(pipefd[index -1][0]);
	}
	if (index < sh_data->len - 1)
	{
		if (dup2(pipefd[index][1], STDOUT_FILENO) == -1)
			return (1);
		close(pipefd[index][1]);
	}
	return (0);
}
