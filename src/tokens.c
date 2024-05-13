/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/06 13:57:15 by tcampbel         ###   ########.fr       */
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
			|| (str[i] == '$' && str[i + 1] == '?'))
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

void	create_tok_struct(t_sh *msh)
{
	int		i;

	i = -1;
	while (++i < msh->processes)
	{
		msh->tok_count = 0;
		msh->pipe_arr[i] = ft_strtrim(msh->pipe_arr[i], " ");
		if (!msh->pipe_arr[i])
			exit_error(msh, "ft_strtrim\n", 127);
		is_token(msh, msh->pipe_arr[i]);
		init_token(msh, msh->lex_arr[i]);
		assign_token(msh, msh->lex_arr[i], msh->pipe_arr[i]);
	}
	ft_free_array(msh->pipe_arr);
}


void	assign_token(t_sh *msh, t_lex **lex_arr, char *cmd)
{
	char	*temp;
	int		i;
	int		j;

	temp = NULL;
	i = -1;
	j = 0;
	while (++i < msh->tok_count)
	{
		if (cmd[j] == '<' && cmd[j + 1] != '<')
		{
			lex_arr[i]->cmd_arr = init_cmd_arr(msh);
			lex_arr[i]->token = R_INPUT;
			j += 1;
			lex_arr[i]->cmd_arr[0] = ft_substr(cmd, j, find_space(cmd, j));
			j = find_space(cmd , j);
		}
		else if (cmd[j] == '>' && cmd[j + 1] != '>')
		{
			lex_arr[i]->cmd_arr = init_cmd_arr(msh);
			lex_arr[i]->token = R_OUTPUT;
			j += 1;
			lex_arr[i]->cmd_arr[0] = ft_substr(cmd, j, find_space(cmd, j));
			j = find_space(cmd , j);
		}
		else if (cmd[j] == '>' && cmd[j + 1] == '>')
		{
			lex_arr[i]->cmd_arr = init_cmd_arr(msh);
			lex_arr[i]->token = APPEND;
			j += 2;
			lex_arr[i]->cmd_arr[0] = ft_substr(cmd, j, find_space(cmd, j));
			j = find_space(cmd , j);
		}
		else if (cmd[j] == '<' && cmd[j + 1] == '<')
		{
			lex_arr[i]->cmd_arr = init_cmd_arr(msh);
			lex_arr[i]->token = HEREDOC;
			j += 2;
			lex_arr[i]->cmd_arr[0] = ft_substr(cmd, j, find_space(cmd, j));
			j = find_space(cmd , j);
		}
		else if (is_op(cmd, j) == false)
		{
			temp = ft_substr(cmd, j, find_op(cmd, j));
			j = find_op(cmd, j);
			lex_arr[i]->cmd_arr = ft_split(temp, ' ');
			free(temp);
			if (!lex_arr)
				exit_error(msh, "ft_split", 127);
			lex_arr[i]->token = CMD;
		}
	}
}

void	lexer(char *input, t_sh *msh)
{
	char	**pipe_arr;

	count_pipes(msh, input);
	msh->lex_arr = init_lex(msh);
	msh->pipe_arr = ft_strtok(input, '|', "'\'''\"'");
	if (!msh->pipe_arr)
		exit_error(msh, "ft_strtok\n", 127);
	create_tok_struct(msh);
	//free(input);
}
