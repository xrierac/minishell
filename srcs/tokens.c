/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/09 17:52:36 by tcampbel         ###   ########.fr       */
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
		|| (str[i] == '>' && str[i + 1] == '>'))
		return (true);
	else if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '$')
		return (true);
	return (false);
}

void	is_cmd(t_sh *msh, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		while (ft_isspace(str[i] && str[i]) && (!is_op(str, i)))
			++i;
		if ((!is_op(str, i)) && str[i] != '\0')
		{
			while (str[i] && (!(is_op(str, i))) && (!ft_isspace(str[i])))
				++i;
			msh->tok_count++;
		}
	}
}

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
	printf("%i\n", msh->tok_count);
}

void	lexer(char *input, t_sh *msh)
{
	int	i;
	int	j;

	i = 0;
	j = msh->len + 1;
	while (j > 0)
	{
		printf("len-%i\n i-%i\n", i, msh->len);
		msh->lex_arr[i]->tok_arr = ft_split(input, ' ');
		if (!msh->lex_arr[i]->tok_arr)
			printf("malloc error\n");
		i++;
		j--;
	}
	// i = 0;
	// while (msh->lex_arr[i]->tok_arr[i])
	// {
	// 	printf("%s\n", msh->lex_arr[i]->tok_arr[i]);
	// 	i++;
	// 	j++;
	// }
}