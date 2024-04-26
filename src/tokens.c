/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/22 17:40:58 by tcampbel         ###   ########.fr       */
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
		else if ((str[i] == '<' && str[i + 1] == '<') \
			|| (str[i] == '>' && str[i + 1] == '>') \
			|| (str[i] == '!' && str[i + 1] == '?'))
		{
			msh->tok_count++;
			i += 2;
			i = is_file(msh, str, i);
		}
		else if ((str[i] == '<' && str[i + 1] != '<') \
					|| (str[i] == '>' && str[i + 1] != '>'))
		{
			msh->tok_count++;
			i++;
			i = is_file(msh, str, i);
		}
		else if (is_op(str, i) == false && str[i])
		{
			msh->tok_count++;
			while (is_op(str, i) == false && str[i])
				i++;
		}
	}
}

void	lexer(char *input, t_sh *msh)
{
	int		i;
	char	**temp;

	i = -1;
	if (msh->error == true)
		return ;
	msh->lex_arr = init_lex(msh);
	temp = ft_strtok(input, '|', "'\'''\"'");
	if (!temp)
	{
		free_all(msh);
		exit_error(msh, "ft_strtok\n", 127);
	}
	while (++i < msh->len) //allocates memory for cmd structs
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
		printf("tok->%i\n", msh->tok_count);
	}
	//assign_token(msh, msh->lex_arr[i], temp);
}
