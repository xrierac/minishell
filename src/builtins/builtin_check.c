/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:48:20 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/06 15:47:20 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parent_builtin(t_lex *lex, t_env *env)
{
	if (!ft_strncmp(lex->cmd_arr[0],"cd", ft_strlen(lex->cmd_arr[0])))
		return (ft_cd(lex->cmd_arr[1], env->env_arr));
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
	//if (!ft_strncmp(lex->cmd_arr[0], "export", ft_strlen(lex->cmd_arr[0])))
	//	return (ft_export(lex->cmd_arr));
	return (1);
}