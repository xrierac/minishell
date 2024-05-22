/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:34:19 by tcampbel         #+#    #+#             */
/*   Updated: 2024/05/02 15:45:28 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void	exit_error(t_sh *msh, char *msg, int status)
{
	if (msh)
	{
		free_all(msh);
		ft_printf(2, RED":( %s\n"END, msg);
	}
	exit(status);
}

void	close_all_hd_fd(t_sh *msh)
{
	int	i;
	int	len;

	i = 0;
	len = msh->pipes + 1;
	while (i < len)
	{
		if (msh->hd_fd[i][0] > 0)
			close(msh->hd_fd[i][0]);
		i++;
	}
}

void	close_hd_fd(int fd)
{
	if (fd > 0)
		close(fd);
}
