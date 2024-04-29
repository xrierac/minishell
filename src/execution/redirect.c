/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:48:01 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/29 11:54:09 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	r_input(t_lex *file)
{
	int	infile;

	infile = open(file->cmd_arr[0], O_RDONLY, 0444);
	if (infile == -1)
		exit(0);
	if (dup2(infile, STDIN_FILENO) == -1)
		exit(0);
}
