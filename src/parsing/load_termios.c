/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_termios.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:05:14 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/30 15:42:08 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*tcsetreadline(t_sh *msh, int n)
{
	char *input;

	tcsetattr(STDIN_FILENO, 0, &msh->new);
	if (n == 0)
		input = readline("MiNiH3LL> ");
	else
		input = readline("> ");
	tcsetattr(STDIN_FILENO, 0, &msh->old);
	return (input);
}

void	load_termios(t_sh *msh)
{
	tcgetattr(STDIN_FILENO, &msh->old);
	msh->new = msh->old;
	msh->new.c_lflag &= ~ECHOCTL;
}
