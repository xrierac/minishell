/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:49:18 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/06 10:55:52 by tcampbel         ###   ########.fr       */
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

int	find_hd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = skip_quotes(str, i);
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 1])
			return (1);
		if (str[i])
			i++;
	}
	return (0);
}
