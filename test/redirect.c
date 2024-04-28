/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:48:01 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/28 12:23:52 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	r_input(char **cmd, char *pathfile, char **env )
{
	int	infile;
	char *path;

	infile = open(pathfile, O_RDONLY, 0444);
	if (infile == -1)
		printf("ERROR");
	if (dup2(infile, STDIN_FILENO) == -1)
		printf("ERROR");
	path = ft_strjoin("/usr/bin/", cmd[0]);
	execve(path, cmd, env);
}

int	main(int argc, char *argv[], char **env)
{
	char	*input;
	char	**arr;

	while (1)
	{
		input = readline("\e[0;32mminishell>\e[0;37m");
		if (input == NULL)
			break ;
		arr = ft_split(input, ' ');
		if (!arr)
			return (0);
		r_input(arr, "infile", env);
		ft_free_array(arr);
		free(input);
	}
	return (0);
}
