/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:00:36 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/21 16:46:56 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_e_op(t_sh *msh, char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return ("<<");
	else if (str[i] == '>' && str[i + 1] == '>')
		return (">>");
	else if (str[i] == '<')
		return ("<");
	else if (str[i] == '>')
		return (">");
	else if (str[i] == '|')
		return ("|");
	else
		return ("");
}

void	heredoc_syntax(t_sh *msh, char *str, int i)
{
	char	*e_op;

	e_op = find_e_op(msh, str, i);
	if (msh->error == 1)
	{
		if (!e_op[0])
			ft_printf(2, RED":( "END SYNTAX_ERROR" `newline'\n");
		else
			ft_printf(2, RED":( "END SYNTAX_ERROR" `%s'\n", e_op);
	}
}

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