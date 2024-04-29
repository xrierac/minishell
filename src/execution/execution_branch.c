/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_branch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:46:29 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/29 11:35:49 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void check_token(t_lex *lex, t_env *env)
{
    if (lex->token == R_INPUT)
		r_input(lex);
}

void	child_start(t_lex **lex_arr, t_env *env)
{
	int	i;
	int	cmd_id;

	i = 0;
	while (lex_arr[i])
	{
		if (lex_arr[i]->token == CMD)
			cmd_id = i;
		else
			check_token(lex_arr[i], env);
	}
	execute(lex_arr[cmd_id], env);
}

void    execution_branch(t_sh *cmd_info)
{
	int 	i;
	int		status;
	pid_t	cpid;

	i = 0;
	while (cmd_info->lex_arr[i])
	{
		cpid = fork();
		if (cpid < 0)
			error_exit();
		if (cpid == 0)
			child_start(cmd_info->lex_arr[i], cmd_info->env);
    	i++;
	}
}