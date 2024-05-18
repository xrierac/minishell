/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:48:01 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/17 11:44:34 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	r_input(char **cmd_arr)
{
	int	infile;

	infile = open(cmd_arr[0], O_RDONLY, 0444);
	if (infile == -1)
		exit(0);
	if (dup2(infile, STDIN_FILENO) == -1)
		exit(0);
	close(infile);
}

void	r_output(char **cmd_arr)
{
	int	outfile;

	outfile = open(cmd_arr[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile == -1)
		exit(0);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		exit(0);
	close(outfile);
}

void	r_append(char **cmd_arr)
{
	int	outfile;

	outfile = open(cmd_arr[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (outfile == -1)
		exit(0);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		exit(0);
	close(outfile);
}

void	r_heredoc(char **cmd_arr)
{
	char	*input;
	char	**arr;
	int		tmpfd;

	tmpfd = open(".tmpfile", O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (tmpfd == -1)
		exit(0);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			exit(0);
		if (!ft_strncmp(input, cmd_arr[0], ft_strlen(input)) && \
		ft_strlen(input) == ft_strlen(cmd_arr[0]))
			break ;
		ft_putstr_fd(input, tmpfd);
		ft_putstr_fd("\n", tmpfd);
		free(input);
	}
	arr = ft_split(".tmpfile", ' ');
	r_input(arr);
	free(arr);
	unlink(".tmpfile");
}
