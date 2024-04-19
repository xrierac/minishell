/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/18 13:40:50 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	is_token(t_sh *msh, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == true)
			i++;
		else if (is_op(str, i) == false)
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				i = find_quote(str, str[i], i) + 1;
				msh->tok_count++;
			}
			else
			{
				i = iter_str(str, i) + 1;
				msh->tok_count++;
			}
		}
		else if ((str[i] == '<' && str[i + 1] == '<') \
			|| (str[i] == '>' && str[i + 1] == '>') \
			|| (str[i] == '!' && str[i + 1] == '?'))
		{
			i += 2;
			msh->tok_count++;
		}
		else if ((str[i] == '<' && str[i + 1] != '<') \
					|| (str[i] == '>' && str[i + 1] != '>'))
		{
			msh->tok_count++;
			i++;
		}
		else if (str[i] == '$' && (str[i + 1] != '\'' || str[i + 1] != '\"'))
		{
			i = iter_str(str, i + 1);
			msh->tok_count++;
		}
	}
}

void	lexer(char *input, t_sh *msh)
{
	int		i;
	char	**temp;

	i = -1;
	count_pipes(msh, input);
	if (msh->error == true)
		return ;
	msh->lex_arr = init_lex(msh);
	temp = ft_strtok(input, '|', "'\'''\"'");
	if (!temp)
	{
		free_all(msh);
		exit_error(msh, "ft_strtok\n", 127);
	}
	while (++i < msh->len)
	{
		msh->tok_count = 0;
		temp[i] = ft_strtrim(temp[i], " ");
		if (!temp[i])
		{
			free_all(msh);
			exit_error(msh, "ft_strtrim\n", 127);
		}
		is_token(msh, temp[i]);
		init_token(msh, msh->lex_arr[i]);
	}
	//assign_token(msh, msh->lex_arr[i], temp);
}
