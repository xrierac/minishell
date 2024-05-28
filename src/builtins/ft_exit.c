/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:32:22 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/28 16:21:31 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit(t_sh *msh, char **cmd)
{
	ft_printf(1, "exit\n");
	if (!cmd)
	{
		free_all(msh);
		exit(0);
	}
	else if (cmd[1])
	{
		ft_printf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	else
		exit(0);
	return (0);
}
