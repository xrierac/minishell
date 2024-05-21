/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:06 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/20 14:37:28 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <signal.h>

void	handle_sigtstp(int sig)
{
	/*
	int	j;

	j = 0;
	while (j < i)
	{
		kill(cpid[j], SIGINT);
		j++;
	}
	*/
	ft_putstr_fd("Hello\n", 2);
}

