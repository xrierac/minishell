/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:06 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/22 16:00:37 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <signal.h>

static void	parent_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_error = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	child_handler(int signal)
{
	if (signal == SIGINT)
		g_error = 130;
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_error = 131;
	}
}

void	receive_signal(int	val)
{
	struct sigaction	sa;

	if (val)
		sa.sa_handler = &parent_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
