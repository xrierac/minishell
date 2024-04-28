/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:29:23 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/26 17:23:31 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parent(t_sh *sh)
{
	int		i;
	pid_t	cpid;
	int		status;

	i = 0;
	while (sh->lex_arr[i])
	{
		cpid = fork();
		if (cpid < 0)
			error_exit("", 127);
		if (cpid == 0)
			execute(sh->lex_arr[i], sh->env);
		i++;
	}
	if (waitpid(cpid, &status, 0) == -1)
		error_exit("", 127);
	return (WEXITSTATUS(status));
}