/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:04 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/25 15:55:40 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_delimeter(t_sh *msh, char *str, int i)
{
	int		start;
	char	*delim;

	while (ft_isspace(str[i]) == true && str[i])
		i++;
	start = i;
	while (check_delim(str[i]) == 1 && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = skip_quotes(str, i);
		else
			i++;
	}
	delim = ft_substr(str, start, i - start);
	if (!delim)
		exit_error(msh, "malloc", 2);
	if (quote_search(delim))
		delim = remove_quotes(msh, delim, 0);
	return (delim);
}

static int	open_heredoc(t_sh *msh, char *delim, int *fd)
{
	char	*input;
	int		stdin_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	if (stdin_cpy == -1)
		return (-1);
	while (1)
	{
		input = tcsetreadline(msh, 1);
		if (g_num == SIGINT)
		{
			when_sigint(msh, fd, stdin_cpy);
			break ;
		}
		if ((!ft_strncmp(input, delim, ft_strlen(input)) && \
		ft_strlen(input) == ft_strlen(delim)) || !input)
			break ;
		if (ft_strchr(input, '$'))
			input = expand_env(msh, input);
		ft_printf(fd[1], "%s\n", input);
		free(input);
		input = NULL;
	}
	return (heredoc_cleaning(fd, stdin_cpy, delim, input));
}

void	count_hd(t_sh *msh, char *str)
{
	int		hd_count;
	int		i;

	hd_count = 0;
	i = 0;
	while (str[i])
	{
		i = skip_quotes(str, i);
		if (str[i] == '<' && str[i + 1] == '<')
			hd_count++;
		if (str[i])
			i++;
	}
	if (hd_count > 16)
		exit_error(msh, "maximum here-document count exceeded", 2);
}

void	open_pipe_and_hd(t_sh *msh, char *delim, char *str, int i)
{
	receive_signal(1);
	if (pipe(msh->hd_fd[msh->valid_hd]) == -1)
		exit_error(msh, "pipe", 1);
	if (check_heredoc(str, i) == true)
	{
		if (open_heredoc(msh, delim, msh->hd_fd[msh->valid_hd]) == -1)
			exit_error(msh, "dup", 1);
		msh->valid_hd++;
	}
	else
	{
		open_heredoc(msh, delim, msh->hd_fd[msh->valid_hd]);
		close_hd_fd(msh->hd_fd[msh->valid_hd][0]);
	}
}

void	heredoc(t_sh *msh, char *str)
{
	int		i;
	char	*delim;

	i = 0;
	msh->valid_hd = 0;
	count_hd(msh, str);
	while (str[i])
	{
		i = skip_quotes(str, i);
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			delim = find_delimeter(msh, str, i);
			if (!delim)
			{
				close_all_hd_fd(msh);
				free(delim);
				return ;
			}
			i = is_eof(str, i);
			open_pipe_and_hd(msh, delim, str, i);
		}
		else
			i++;
	}
}
