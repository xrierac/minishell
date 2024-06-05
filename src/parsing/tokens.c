/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/05 17:27:58 by tcampbel         ###   ########.fr       */
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
		if (!pipe_arr[j])
			exit_error(msh, "malloc", 2);
		is_token(msh, pipe_arr[j]);
		msh->lex_arr[i] = init_token(msh);
		assign_token(msh, msh->lex_arr[i], msh->pipe_arr[j], i);
	}
	ft_free_array(pipe_arr);
	msh->pipe_arr = NULL;
}

void	assign_token(t_sh *msh, t_lex **lex, char *cmd, int proc)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < msh->tok_count)
	{
		lex[i]->fd = 0;
		if (is_op(cmd, j) == true)
			j = tokenise_op(msh, lex[i], cmd, j);
		else
			j = tokenise_cmd(msh, lex[i], cmd, j);
		if (lex[i]->token == VALID_HD)
		{
			lex[i]->fd = dup(msh->hd_fd[proc][0]);
			if (lex[i]->fd == -1)
				exit_error(msh, "dup", 1);
			close(msh->hd_fd[proc][0]);
		}
	}
}

void	lexer(char *input, t_sh *msh)
{
	init_lex(msh);
	msh->pipe_arr = ft_strtok(input, '|', "'\'''\"'");
	if (!msh->pipe_arr)
	{
		free(msh->lex_arr);
		msh->lex_arr = NULL;
		exit_error(msh, "malloc", 2);
	}
	create_tok_struct(msh, msh->pipe_arr);
}
