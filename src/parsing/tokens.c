/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/27 17:13:20 by xriera-c         ###   ########.fr       */
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
			|| (str[i] == '>' && str[i + 1] == '>'))
			i = is_file(msh, str, i + 2);
		else if ((str[i] == '<' && str[i + 1] != '<') \
					|| (str[i] == '>' && str[i + 1] != '>'))
			i = is_file(msh, str, i + 1);
		else if (is_op(str, i) == false && str[i])
		{
			while (is_op(str, i) == false && str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i = find_quote(str, str[i], i + 1);
				else
					i++;
			}
			msh->tok_count++;
		}
	}
}

void	create_tok_struct(t_sh *msh, char **pipe_arr)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (pipe_arr[++j] && ++i < msh->processes)
	{
		msh->tok_count = 0;
		pipe_arr[j] = ft_strtrim(msh->pipe_arr[j], " ");
		if (pipe_arr[j] == 0)
			exit_error(msh, "ft_strtrim", 127);
		is_token(msh, pipe_arr[j]);
		msh->lex_arr[i] = init_token(msh);
		assign_token(msh, msh->lex_arr[i], msh->pipe_arr[j]);
	}
	ft_free_array(pipe_arr);
}

void	assign_token(t_sh *msh, t_lex **lex, char *cmd)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < msh->tok_count)
	{
		if (is_op(cmd, j) == true)
			j = tokenise_op(msh, lex[i], cmd, j);
		else
			j = tokenise_cmd(msh, lex[i], cmd, j);
	}
}

void	lexer(char *input, t_sh *msh)
{
	init_lex(msh);
	msh->pipe_arr = ft_strtok(input, '|', "'\'''\"'");
	if (!msh->pipe_arr)
		exit_error(msh, "ft_strtok\n", 127);
	create_tok_struct(msh, msh->pipe_arr);
}
