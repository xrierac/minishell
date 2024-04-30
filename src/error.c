/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:22:28 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/26 12:22:28 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_error(t_sh *msh, char *msg, int status)
{
	if (msh)
	{
		free_all(msh);
		ft_printf(2, RED":( %s\n"END, msg);
	}
	exit(status);
}
