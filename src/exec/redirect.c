/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:48:01 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/20 12:06:16 by xriera-c         ###   ########.fr       */
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

