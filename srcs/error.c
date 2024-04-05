/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:45:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/05 13:46:08 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_error(t_sh *msh, char *msg, int status)
{
	if (msh)
	{
		free_all(msh);
		ft_printf(2, HRED":( %s\n"RESET, msg);
	}
	exit(status);
}