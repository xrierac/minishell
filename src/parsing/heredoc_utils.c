/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:49:18 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/30 15:49:30 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	heredoc_cleaning(int *fd, int stdin_cpy, char *delim, char *input)
{
	close(stdin_cpy);
	close(fd[1]);
	free(delim);
	if (input)
		free(input);
	return (0);
}

void	when_sigint(t_sh *msh, int *fd, int stdin_cpy)
{
	g_num = 0;
	msh->error = 1;
	if (dup2(stdin_cpy, 0) == -1)
		generic_error("", "dup2");
	close(fd[0]);
}
