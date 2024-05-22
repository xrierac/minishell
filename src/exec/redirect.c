/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:48:01 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/22 17:22:11 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	r_input(char **cmd_arr)
{
	int	infile;

	infile = open(cmd_arr[0], O_RDONLY, 0444);
	if (infile == -1)
		exit(0);
	if (dup2(infile, STDIN_FILENO) == -1)
		exit(0);
	close(infile);
}

void	r_output(char **cmd_arr)
{
	int	outfile;

	outfile = open(cmd_arr[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile == -1)
		exit(0);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		exit(0);
	close(outfile);
}

void	r_append(char **cmd_arr)
{
	int	outfile;

	outfile = open(cmd_arr[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (outfile == -1)
		exit(0);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		exit(0);
	close(outfile);
}

