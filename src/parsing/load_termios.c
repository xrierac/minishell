/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_termios.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:05:14 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/29 15:14:04 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	load_termios(t_sh *msh)
{
	tcgetattr(STDIN_FILENO, &msh->old);
	msh->new = msh->old;
	msh->new.c_lflag &= ~ECHOCTL;
}
