/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:00:36 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/25 15:55:47 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_delim(char c)
{
	if (c >= 33 && c <= 126)
	{
		if (c == '<' || c == '>' || c == '|')
			return (2);
		return (1);
	}
	else
		return (0);
}

t_bool	check_heredoc(char *cmd, int j)
{
	while (cmd[j] && cmd[j] != '|')
	{
		if (is_hd_valid(cmd, j) == false)
			return (false);
		j++;
	}
	return (true);
}

t_bool	is_hd_valid(char *cmd, int j)
{
	if (cmd[j] == '<' || (cmd[j] == '<' && cmd[j + 1] == '<'))
		return (false);
	return (true);
}

int	is_eof(char *str, int i)
{
	if (str[i] == '\0')
		return (i);
	while (ft_isspace(str[i]) == true)
		i++;
	if (check_delim(str[i]) == 1)
	{
		while (check_delim(str[i]) == 1 && str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = skip_quotes(str, i);
			else
				i++;
		}
	}
	return (i);
}
