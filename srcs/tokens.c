/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/16 17:32:32 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	is_str(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '$' || str[i] == '\'' \
			|| str[i] == '\"')
			return (false);
	}
	return (true);
}

int	iter_str(char *str, int i)
{
	while (str[i] != ft_isspace(str[i]) && str[i])
		++i;
	return (i);
}

void	is_token(t_sh *msh, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = find_quote(str, str[i], i);
			msh->tok_count++;
		}
		if ((str[i] == '<' && str[i + 1] == '<') \
			|| (str[i] == '>' && str[i + 1] == '>') \
			|| (str[i] == '$' && str[i + 1] == '?'))
		{
			i += 2;
			msh->tok_count++;
		}
		else if (str[i] == '<' || str[i] == '>')
			msh->tok_count++;
		else if (str[i] == '$' && (str[i + 1] != '\'' || str[i + 1] != '\"'))
		{
			i = iter_str(str, i + 1);
			msh->tok_count++;
		}
		else if (is_str(str, i) == true)
		{
			msh->tok_count++;
			i = iter_str(str, i);
		}
	}
}

t_bool	ft_isspace(char str)
{
	if (str == ' ' || str == '\t' || str == '\n')
		return (true);
	return (false);
}


void	lexer(char *input, t_sh *msh)
{
	int		i;
	int		j;
	char	**temp;

	i = -1;
	j = -1;
	count_pipes(msh, input);
	msh->lex_arr = init_lex(msh);
	temp = ft_strtok(input, '|', "'\'''\"'");
	if (!temp)
	{
		free_all(msh);
		exit_error(msh, "ft_strtok\n", 127);
	}
	while (temp[++j])
	{
		msh->tok_count = 0;
		temp[j] = ft_strtrim(temp[j], " ");
		is_token(msh, temp[j]);
		printf("%s\n", temp[j]);
		printf("tok->%i\n", msh->tok_count);
	}
	// while (msh->lex_arr[++i])
	// {
		//init_token(msh); //Needs to be built, will allocate memory based on token count
	// }
	// count_tokens(input, msh);
	// 	format_input(msh, msh->lex_arr[i][j], input);
}
