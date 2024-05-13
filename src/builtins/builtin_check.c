/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:48:20 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/13 10:56:03 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parent_builtin(char **cmd, t_env *env)
{
	int	i;
	
	i = 0;
	if (!ft_strncmp(cmd[0],"cd", 2) && ft_strlen(cmd[0]) == 2)
		return (ft_cd(cmd[1], env));
	if (!ft_strncmp(cmd[0], "export", 6) && ft_strlen(cmd[0]) == 6)
	{
		ft_export(env, cmd[1]);
		while (cmd[++i])
			ft_export(env, cmd[i]);
		return (0);
	}
	if (!ft_strncmp(cmd[0], "unset", 5) && ft_strlen(cmd[0]) == 5)
		return (ft_unset(env, cmd, 0));
	return (1);
}

int	builtin_check(char **cmd, t_env *env)
{	
	if (!ft_strncmp(cmd[0], "echo", 4) && ft_strlen(cmd[0]) == 4)
		return (ft_echo(cmd, env->env_arr));
	if (!ft_strncmp(cmd[0], "pwd", 3) && ft_strlen(cmd[0]) == 3)
		return (ft_pwd());
	if (!ft_strncmp(cmd[0],"env", 3) && ft_strlen(cmd[0]) == 3)
		return (ft_env(env->env_arr));
	return (1);
}