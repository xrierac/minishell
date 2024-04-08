/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:03:36 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/04 12:15:32 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo(t_lex *cmd)
{
	int	i;

	i
	if (ft_strncmp(cmd->lex[1], "-n", 2))
		   cmd->lex++;
	while (cmd->++lex)
		ft_printf("%s", cmd->lex);
	if (ft_strncmp(cmd->lex[1], "-n", 2))

}

void	pwd(char *envp[])
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (ft_strncmp(envp[i], "PWD=", 4) != 0 && envp[i])
		i++;
	ft_printf("%s\n", ft_strchr(envp[i], '='));
}

void	cd(char *envp[], t_lex *cmd)
{
	int	i;

	i = 0;
	if (!cmd->lex[)
		return (NULL);
	chdir(str);
	
}

void	unset(char *envp[]
