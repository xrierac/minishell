/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:34 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/30 14:12:35 by tcampbel         ###   ########.fr       */
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

char	**create_tok_struct(t_sh *msh, char **temp)
{
	int	i;

	i = -1;
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
	return (temp);
}

void	fill_tok_structs(t_sh *msh, t_lex ***lex_arr, char **temp)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (lex_arr[++i] && temp[++j])
		assign_token(msh, lex_arr[i], temp[j]);
	//ft_free_array(temp);
}

void	assign_token(t_sh *msh, t_lex **lex_arr, char *cmd)
{
	char	*temp;
	int		i;
	int		j;

	temp = NULL;
	i = -1;
	j = 0;
	while (++i <= msh->tok_count && lex_arr[i])
	{
		lex_arr[i]->cmd_arr = init_cmd_arr(msh);
		if (cmd[j] == '<' && cmd[j + 1] != '<')
		{
			lex_arr[i]->token = R_INPUT;
			j += 1;
			lex_arr[i]->cmd_arr[0] = ft_substr(cmd, j, find_space(cmd, j));
			j = find_space(cmd , j);
		}
		else if (cmd[j] == '>' && cmd[j + 1] != '>')
		{
			lex_arr[i]->token = R_OUTPUT;
			j += 1;
			lex_arr[i]->cmd_arr[0] = ft_substr(cmd, j, find_space(cmd, j));
			j = find_space(cmd , j);
		}
		else if (cmd[j] == '>' && cmd[j + 1] == '>')
		{
			lex_arr[i]->token = APPEND;
			j += 2;
			lex_arr[i]->cmd_arr[0] = ft_substr(cmd, j, find_space(cmd, j));
			j = find_space(cmd , j);
		}
		else if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			lex_arr[i]->token = HEREDOC;
			j += 2;
			lex_arr[i]->cmd_arr[0] = ft_substr(cmd, j, find_space(cmd, j));
			j = find_space(cmd , j);
		}
		else
		{
			lex_arr[i]->token = CMD;
			temp = ft_substr(cmd, j, find_op(cmd, j));
			j = find_op(cmd, j);
			lex_arr[i]->cmd_arr = ft_split(temp, ' ');
		}
	}
}

void	lexer(char *input, t_sh *msh)
{
	char	**temp;
	char	**res;

	count_pipes(msh, input);
	msh->lex_arr = init_lex(msh);
	temp = ft_strtok(input, '|', "'\'''\"'");
	if (!temp)
	{
		free_all(msh);
		exit_error(msh, "ft_strtok\n", 127);
	}
	res = create_tok_struct(msh, temp);
	fill_tok_structs(msh, msh->lex_arr, res);
	free(input);
}
