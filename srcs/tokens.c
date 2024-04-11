/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/11 17:05:32 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	ft_isspace(char str)
{
	if (str == ' ' || str == '\t' || str == '\n')
		return (true);
	return (false);
}

t_bool	is_op(char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] == '<') \
		|| (str[i] == '>' && str[i + 1] == '>') \
		|| (str[i] == '$' && str[i + 1] == '?'))
		return (true);
	else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		return (true);
	return (false);
}

// t_bool	is_cmd(t_sh *msh, char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (false);
// 	while (ft_isspace(str[i]))
// 		i++;
// 	if (access(str, F_OK) == 0)
// 		return (true);
// 	else if (is_builtin(msh, str))
// 		return (true);
// 	return (false);
// }

t_bool	is_arg(t_sh *msh, char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (false);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			++i;
			while (str[i] && str[i] != '\'')
				++i;
			if (str[i] == '\'')
				return (true);
		}
	}
	return (false);
}

// Probably don't need this anymore, was made to check how many tokens are 
// needed to malloc but now splitting with pipes

void	count_tokens(char *input, t_sh *msh)
{
	int	i;

	i = -1;
	msh->tok_count = 0;
	while (input[++i])
	{
		if (is_op(input, i))
			msh->tok_count++;
	}
	//is_cmd(msh, input);
	//printf("%i\n", msh->tok_count);
}

void	lexer(char *input, t_sh *msh)
{
	int		i;
	char	**tok_check;

	i = 0;
	tok_check = ft_split(input, ' ');
	if (!tok_check)
	{
		free_all(msh);
		exit_error(msh, "ft_split\n", 127);
	}
}

void	get_token(t_sh *msh, t_lex *lex)
{
	if (ft_strncmp(lex->tok_arr, "$", 2)
		lex->token = ENV;
	else if (ft_strncmp(lex->tok_arr, "$?", 3)
		lex->token = STATUS;
	else if (ft_strncmp(lex->tok_arr, "<", 2)
		lex->token = R_INPUT;
	else if (ft_strncmp(lex->tok_arr, ">", 2)
		lex->token = R_OUTPUT;
	else if (ft_strncmp(lex->tok_arr, "<<", 3)
		lex->token = HEREDOC;
	else if (ft_strncmp(lex->tok_arr, ">>", 3)
		lex->token = APPEND;
	else
		lex->token = CMD;
}