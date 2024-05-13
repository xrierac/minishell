/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:44:06 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/13 17:57:16 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_type(t_sh *msh, t_lex *lex, char *cmd, int j)
{
	if (cmd[j] == '<' && cmd[j + 1] != '<')
		lex->token = R_INPUT;
	else if (cmd[j] == '>' && cmd[j + 1] != '>')
		lex->token = R_OUTPUT;
	else if (cmd[j] == '>' && cmd[j + 1] == '>')
		lex->token = APPEND;
	else if (cmd[j] == '<' && cmd[j + 1] == '<')
		lex->token = HEREDOC;
}

int	tokenise_cmd(t_sh *msh, t_lex *lex, char *cmd, int j)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = -1;
	temp = ft_substr(cmd, j, find_op(cmd, j));
	j = find_op(cmd, j);
	lex->cmd_arr = ft_strtok(temp, ' ', "\'\"");
	free(temp);
	if (!lex->cmd_arr)
		exit_error(msh, "ft_strtok", 127);
	while (lex->cmd_arr[++i])
	{
		lex->cmd_arr[i] = ft_strtrim(lex->cmd_arr[i], " ");
		lex->cmd_arr[i] = remove_quotes(msh, lex->cmd_arr[i]);
	}
	lex->token = CMD;
	return (j);
}

int	tokenise_op(t_sh *msh, t_lex  *lex, char *cmd, int j)
{
	char	*temp;

	temp = NULL;
	lex->cmd_arr = init_cmd_arr(msh);
	token_type(msh, lex, cmd, j);
	if (lex->token == R_INPUT || lex->token == R_OUTPUT)
		j++;
	else if (lex->token == APPEND || lex->token == HEREDOC)
		j += 2;
	temp = ft_substr(cmd, j, find_space(cmd, j));
	if (!temp)
		exit_error(msh, "ft_substr", 127);
	lex->cmd_arr[0] = ft_strtrim(temp, " ");
	if (!lex->cmd_arr[0])
		exit_error(msh, "ft_strtrim", 127);
	j = find_space(cmd, j);
	return (j);
}