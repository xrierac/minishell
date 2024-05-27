/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:32:22 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/27 15:21:34 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_sh *msh, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 1)
	{
		ft_printf(1, "exit\n");
		ft_printf(2, "exit: too many arguments\n");
		return ;
	}
	else
	{
		free_all(msh);
		ft_printf(1, "exit\n");
		exit(0);
	}
}