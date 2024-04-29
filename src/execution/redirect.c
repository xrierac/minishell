/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:48:01 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/29 11:33:42 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	r_input(t_lex *lex)
{
	int	infile;

	infile = open(lex->cmd_arr[1], O_RDONLY, 0444);
	if (infile == -1)
		error_exit();
	if (dup2(infile, STDIN_FILENO) == -1)
		error_exit("", 127);

}
