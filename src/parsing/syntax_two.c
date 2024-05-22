/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:30:53 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/22 14:31:54 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	current_op(char *str)
{
	if (*str == '<' && *(str + 1) != '<')
		return (1);
	else if (*str == '>' && *(str + 1) != '>')
		return (2);
	else if (*str == '>' && *(str + 1) == '>')
		return (3);
	else if (*str == '<' && *(str + 1) == '<')
		return (4);
	return (0);
}

char	*choose_op(char *c)
{
	if (*c == '<' && *(c + 1) == '<')
		return ("<<");
	else if (*c == '>' && *(c + 1) == '>')
		return (">>");
	else if (*c == '<')
		return ("<");
	else if (*c == '>')
		return (">");
	else if (*c == '|')
		return ("|");
	return ("");
}

char	*check_op_syntax(t_sh *msh, char *str)
{
	int		op;
	int		i;
	char	*e_op;

	op = current_op(str);
	if (op > 2)
		str += 2;
	else if (op)
		str += 1;
	while (ft_isspace(*str) && *str)
		str++;
	if (*str == '\0' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `newline'\n");
		msh->error = 1;
	}
	e_op = choose_op(str);
	if (e_op[0] != '\0' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `%s'\n", e_op);
		msh->error = 1;
	}
	return (str);
}
