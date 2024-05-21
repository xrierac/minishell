/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:04 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/21 16:52:30 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_all_hd_fd(t_sh *msh)
{
	int	i;
	int len;

	i = 0;
	len = msh->pipes + 1;
	while (i < len)
	{
		if (msh->hd_fd[i][0] > 0)
			close(msh->hd_fd[i][0]);
	}
}

void	close_hd_fd(int fd)
{
	if (fd > 0)
		close(fd);
}

static char	*find_delimeter(t_sh *msh, char *str, int i)
{
	int		start;
	char	*delim;
	int		quotes;

	quotes = 0;
	while (ft_isspace(str[i]) == true && str[i])
		i++;
	if (!str[i])
	{
		msh->error = 1;
		return ("");
	}
	start = i;
	while (check_delim(str[i]) == 1 && msh->error == 0 && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quotes = 1;
			i = find_quote(str, str[i], i + 1);
		}
		else
			i++;
	}
	delim = ft_substr(str, start, i - start);
	if (!delim)
		exit_error(msh, "ft_substr", 127);
	if (quotes)
		delim = remove_quotes(msh, delim);
	return (delim);
}

void	open_hd_pipe(t_sh *msh)
{
	int	i;

	i = 0;
	while (i < (msh->pipes + 1))
	{
		if (pipe(msh->hd_fd[i]) == -1)
		{
			close_all_hd_fd(msh);
			exit_error(msh, "pipe", 1);
		}
		i++;
	}
}

void	open_heredoc(t_sh *msh, char *delim, int *fd)
{
	char	*input;

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
		ft_printf(fd[1], "%s\n", input);
		free(input);
	}
	close (fd[1]);
	free(delim);
	free(input);
}

void	count_hd(t_sh *msh, char *str)
{
	int		hd_count;
	int		i;

	hd_count = 0;
	while (str[i])
	{
		i = skip_quotes(str, i);
		if (str[i] == '<' && str[i + 1] == '<')
			hd_count++;
		i++;
	}
	if (hd_count > 16)
		exit_error(msh, "maximum here-document count exceeded", 1);
}

void	heredoc(t_sh *msh, char *str)
{
	int		i;
	int		j;
	int		valid_hd_count;
	char	*delim;

	i = 0;
	valid_hd_count = 0;
	count_hd(msh, str);
	while (str[i])
	{
		i = skip_quotes(str, i);
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			delim = find_delimeter(msh, str, i);
			heredoc_syntax(msh, delim, i);
			if (msh->error == 1)
			{
				close_all_hd_fd(msh);
				return ;
			}
			i = is_file(msh, str, i);
			// open_hd_pipe(msh);
			// if (check_heredoc(str, i) == true)
			// {
			// 	open_heredoc(msh, delim, msh->hd_fd[valid_hd_count]);
			// 	valid_hd_count++;
			// }
			// else
			// {
			// 	open_heredoc(msh, delim, msh->hd_fd[valid_hd_count]);
			// 	close_hd_fd(msh->hd_fd[valid_hd_count][0]);
			// }
		}
		else
			i++;
	}
}
