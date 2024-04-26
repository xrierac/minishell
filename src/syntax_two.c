/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:30:53 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/22 11:44:54 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_r_input(t_sh *msh, char *str, int i)
{
	char	*op;

	if (str[i] == '\0' || ft_strncmp((str + 1), ">", 2) == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `newline'\n");
		msh->error = 1;
	}
	while (ft_isspace(str[i]) == true && str[i])
		i++;
	op = choose_op(str[i]);
	if (str[i] == '<' && str[i + 1] == '<' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `<<'\n");
		msh->error = 1;
	}
	else if (str[i] == '>' && str[i + 1] == '>' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `>>'\n");
		msh->error = 1;
	}
	else if (str[i] == op[0] && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `%s'\n", op);
		msh->error = 1;
	}
}

void	check_r_output(t_sh *msh, char *str, int i)
{
	char	*op;

	while (ft_isspace(str[i]) == true && str[i])
		i++;
	op = choose_op(str[i]);
	if (str[i] == '\0')
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `newline'\n");
		msh->error = 1;
	}
	else if (str[i] == '<' && str[i + 1] == '<' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `<<'\n");
		msh->error = 1;
	}
	else if (str[i] == '>' && str[i + 1] == '>' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `>>'\n");
		msh->error = 1;
	}
	else if (str[i] == op[0] && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `%s'\n", op);
		msh->error = 1;
	}
}

void	check_append(t_sh *msh, char *str, int i)
{
	char	*op;

	while (ft_isspace(str[i]) == true && str[i])
		i++;
	op = choose_op(str[i]);
	if (str[i] == '\0')
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `newline'\n");
		msh->error = 1;
	}
	else if (str[i] == '<' && str[i + 1] == '<' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `<<'\n");
		msh->error = 1;
	}
	else if (str[i] == '>' && str[i + 1] == '>' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `>>'\n");
		msh->error = 1;
	}
	else if (str[i] == op[0] && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `%s'\n", op);
		msh->error = 1;
	}
}

void	check_heredoc(t_sh *msh, char *str, int i)
{
	char	*op;

	while (ft_isspace(str[i]) == true && str[i])
		i++;
	op = choose_op(str[i]);
	if (str[i] == '\0')
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `newline'\n");
		msh->error = 1;
	}
	else if (str[i] == '<' && str[i + 1] == '<' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `<<'\n");
		msh->error = 1;
	}
	else if (str[i] == '>' && str[i + 1] == '>' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `>>'\n");
		msh->error = 1;
	}
	else if (str[i] == op[0] && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `%s'\n", op);
		msh->error = 1;
	}
}