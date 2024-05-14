/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/14 11:26:04 by tcampbel         ###   ########.fr       */
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
			msh->tok_count++;
			while (is_op(str, i) == false && str[i])
				i++;
		}
	}
}

void	create_tok_struct(t_sh *msh)
{
	int		i;

	i = -1;
	while (++i < msh->processes)
	{
		msh->tok_count = 0;
		msh->pipe_arr[i] = ft_strtrim(msh->pipe_arr[i], " ");
		if (!msh->pipe_arr[i])
			exit_error(msh, "ft_strtrim", 127);
		is_token(msh, msh->pipe_arr[i]);
		init_token(msh, msh->lex_arr[i]);
		// printf("After=%s\n", msh->pipe_arr[i]);
		assign_token(msh, msh->lex_arr[i], msh->pipe_arr[i]);
	}
	ft_free_array(msh->pipe_arr);
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
	int		i;
	char	**pipe_arr;

	i = -1;
	count_pipes(msh, input);
	msh->lex_arr = init_lex(msh);
	msh->pipe_arr = ft_strtok(input, '|', "'\'''\"'");
	if (!msh->pipe_arr)
		exit_error(msh, "ft_strtok\n", 127);
	create_tok_struct(msh);
	//free(input);
}
