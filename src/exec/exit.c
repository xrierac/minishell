/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:33:02 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/25 15:56:22 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_cmd_not_found(char *str)
{
	ft_printf(2, "minishell: %s: command not found\n", str);
	return (127);
}

int	non_perror(char *str, char *cmd)
{
	ft_printf(2, "minishell: %s: %s\n", cmd, str);
	return (1);
}

int	generic_error(char *str, char *cmd)
{
	ft_printf(2, "minishell: %s: ", cmd);
	perror(str);
	return (1);
}
