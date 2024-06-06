/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:44:06 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/06 14:25:55 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	check_amb_rd(t_lex *lex, char *cmd, int j)
{
	while (ft_isspace(cmd[j]) && cmd[j])
		j++;
	if (cmd[j] == '$' && cmd[j + 1] != '\0')
		lex->token = AMB_RD;
}

void	token_type(t_sh *msh, t_lex *lex, char *cmd, int j)
{
	if (cmd[j] == '<' && cmd[j + 1] != '<')
	{
		lex->token = R_INPUT;
		check_amb_rd(lex, cmd, j + 1);
	}
	else if (cmd[j] == '>' && cmd[j + 1] != '>')
	{
		lex->token = R_OUTPUT;
		check_amb_rd(lex, cmd, j + 1);
	}
	else if (cmd[j] == '>' && cmd[j + 1] == '>')
	{
		lex->token = APPEND;
		check_amb_rd(lex, cmd, j + 2);
	}
	else if (cmd[j] == '<' && cmd[j + 1] == '<')
	{
		if (check_heredoc(cmd, j + 2) == true)
			lex->token = VALID_HD;
		else
			lex->token = SKIP_HD;
	}
}

int	tokenise_cmd(t_sh *msh, t_lex *lex, char *cmd, int j)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = -1;
	temp = ft_substr(cmd, j, find_op(cmd, j) - j);
	if (!temp)
		exit_error(msh, "malloc", 2);
	j = find_op(cmd, j);
	lex->cmd_arr = ft_strtok(temp, ' ', "'\'''\"'");
	free(temp);
	if (!lex->cmd_arr)
		exit_error(msh, "malloc", 2);
	while (lex->cmd_arr[++i])
	{
		lex->cmd_arr[i] = ft_strtrim(lex->cmd_arr[i], " ");
		if (!lex->cmd_arr[i])
			exit_error(msh, "malloc", 2);
		if (quote_search(lex->cmd_arr[i]) == 1)
			lex->cmd_arr[i] = remove_quotes(msh, lex->cmd_arr[i], 0);
	}
	lex->token = CMD;
	return (j);
}

int	tokenise_op(t_sh *msh, t_lex *lex, char *cmd, int j)
{
	char	*temp;

	temp = NULL;
	lex->cmd_arr = init_cmd_arr(msh);
	token_type(msh, lex, cmd, j);
	if (lex->token == R_INPUT || lex->token == R_OUTPUT)
		j++;
	else if (lex->token == APPEND || lex->token == VALID_HD \
			|| lex->token == SKIP_HD)
		j += 2;
	temp = ft_substr(cmd, j, find_space(cmd, j) - j);
	if (!temp)
		exit_error(msh, "malloc", 2);
	j = find_space(cmd, j);
	while (ft_isspace(cmd[j]) == true && cmd[j])
		j++;
	lex->cmd_arr[0] = ft_strtrim(temp, " ");
	if (!lex->cmd_arr[0])
		exit_error(msh, "malloc", 2);
	if (quote_search(lex->cmd_arr[0]) == 1)
		lex->cmd_arr[0] = remove_quotes(msh, lex->cmd_arr[0], 0);
	return (j);
}
