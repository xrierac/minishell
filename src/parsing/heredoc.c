/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:04 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/20 18:25:04 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_bool	check_delim(char c)
{
	if (c >= 33 && c <= 126)
	{
		if (c == '<' || c == '>' || c == '|')
			return (false);
		return (true);
	}
	else
		return (false);
}

static char	*find_delimeter(t_sh *msh, char *str, int i)
{
	int		start;
	char	*delim;
	int		quotes;

	while (ft_isspace(str[i]) == true && str[i])
		i++;
	if (str[i] == '\0' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `newline'\n");
		msh->error = 1;
	}
	start = i;
	if (check_delim(str[i]) == true && msh->error == 0)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quotes = 1;
			i = find_quote(str, str[i], i + 1);
		}
		while (check_delim(str[i]) == true && str[i])
			i++;
		printf("i=%i\n", i);
		delim = ft_substr(str, start, i - start);
		if (!delim)
			exit_error(msh, "ft_substr", 127);
		if (quotes)
			delim = remove_quotes(msh, delim);
	}
	else
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `CHECK'\n");
		msh->error = 1;
	}
	return (delim);
}

void	open_heredoc(t_sh *msh, char *delim)
{
	char	*input;

	if (pipe(msh->hd_fd) == -1)
		exit_error(msh, "pipe", 1);
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit_error(msh, "readline", 127);
		if (!ft_strncmp(input, delim, ft_strlen(input)) && \
		ft_strlen(input) == ft_strlen(delim))
			break ;
		// if (ft_strchr(input, '$'))
		// 	input = expand_env(msh, input);
		ft_printf(msh->hd_fd[1], "%s\n", input);
		free(input);
	}
	close (msh->hd_fd[1]);
	free(delim);
	free(input);
}

void	heredoc(t_sh *msh, char *str)
{
	int		i;
	char	*delim;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = find_quote(str, str[i], i + 1);
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			delim = find_delimeter(msh, str, i);
			printf("Delim=%s\n", delim);
			if (msh->error == 1 || !delim)
				return ;
			i = is_file(msh, str, i);
			if (check_heredoc(str, i) == true)
				open_heredoc(msh, delim);
			else
			{
				open_heredoc(msh, delim);
				close_hd_fd(msh);
			}
		}
		else
			i++;
	}
}

t_bool	is_hd_valid(char *cmd, int j)
{
	if (cmd[j] == '<' || (cmd[j] == '<' && cmd[j + 1] == '<'))
		return (false);
	return (true);
}

t_bool	check_heredoc(char *cmd, int j)
{
	while (cmd[j])
	{
		if (is_hd_valid(cmd, j) == false)
			return (false);
		j++;
	}
	return (true);
}

void	close_hd_fd(t_sh *msh)
{
	if (msh->hd_fd[0] > 0)
		close(msh->hd_fd[0]);
}
