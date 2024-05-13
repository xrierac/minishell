/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:48:20 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/13 09:56:19 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parent_builtin(t_lex *lex, t_env *env)
{
	int	i;
	
	i = 0;
	if (!ft_strncmp(lex->cmd_arr[0],"cd", ft_strlen(lex->cmd_arr[0])))
		return (ft_cd(lex->cmd_arr[1], env));
	if (!ft_strncmp(lex->cmd_arr[0], "export", ft_strlen(lex->cmd_arr[0])))
	{
		ft_export(env, lex->cmd_arr[1]);
		while (lex->cmd_arr[++i])
			ft_export(env, lex->cmd_arr[i]);
		return (0);
	}
	if (!ft_strncmp(lex->cmd_arr[0], "unset", 5)
	&& ft_strlen(lex->cmd_arr[0]) == 5)
		return (ft_unset(env, lex->cmd_arr, 0));
	return (1);
}

int	builtin_check(t_lex *lex, t_env *env)
{	
	if (!ft_strncmp(lex->cmd_arr[0], "echo", ft_strlen(lex->cmd_arr[0])))
		return (ft_echo(lex->cmd_arr, env->env_arr));
	if (!ft_strncmp(lex->cmd_arr[0], "pwd", ft_strlen(lex->cmd_arr[0])))
		return (ft_pwd());
	if (!ft_strncmp(lex->cmd_arr[0],"env", ft_strlen(lex->cmd_arr[0])))
		return (ft_env(env->env_arr));
	return (1);
}