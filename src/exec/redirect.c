/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:48:01 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/13 14:09:53 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	r_input(char **cmd_arr)
{
	int	infile;

	infile = open(cmd_arr[0], O_RDONLY, 0444);
	if (infile == -1)
		return (generic_error("", cmd_arr[0]));
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		return (generic_error("", cmd_arr[0]));
	}
	close(infile);
	return (0);
}

int	r_output(char **cmd_arr)
{
	int	outfile;

	outfile = open(cmd_arr[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile == -1)
		return (generic_error("", cmd_arr[0]));
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		return (generic_error("", cmd_arr[0]));
	}
	close(outfile);
	return (0);
}

int	r_append(char **cmd_arr)
{
	int	outfile;

	outfile = open(cmd_arr[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (outfile == -1)
		return (generic_error("", cmd_arr[0]));
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		return (generic_error("", cmd_arr[0]));
	}
	close(outfile);
	return (0);
}

int	r_heredoc(t_lex *lex)
{
	if (dup2(lex->fd, STDIN_FILENO) == -1)
	{
		close(lex->fd);
		lex->fd = 0;
		return (generic_error("", lex->cmd_arr[0]));
	}
	close(lex->fd);
	lex->fd = 0;
	return (0);
}
