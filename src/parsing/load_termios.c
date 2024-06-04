/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_termios.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:05:14 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/04 13:02:55 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*tcsetreadline(t_sh *msh, int n)
{
	char	*input;

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
