/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:43:43 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/24 11:05:10 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*syntax_check(t_sh *msh, char *temp)
{
	char	*start;
	char	*input;
	char	*res;

	start = ft_strtrim(temp, " ");
	if (!start)
	{
		free_all(msh);
		exit_error(msh, "ft_strtrim", 127);
	}
	if (start[0] == '|' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `|'\n");
		msh->error = 1;
	}
	if (start[0] == '\0')
	{
		msh->error = 1;
		return (input);
	}
	input = start;
	if (msh->error == 0)
	{
		count_quotes(msh, start);
		res = expand_env(msh, start);
		if (!res[0])
		{
			msh->error = 1;
			return (res);
		}
		check_str(msh, res);
		return (res);
	}
	return (input);
}

void	check_str(t_sh *msh, char *temp)
{
	int		i;

	i = 0;
	while (*temp)
	{
		if ((ft_strncmp(temp, "<<<", 4) == 0 \
			|| ft_strncmp(temp, "<<< ", 4) == 0) && msh->error == 0)
		{
			msh->error = 1;
			ft_printf(2, RED":( "END"Here strings have no power here!\n");
		}
		else if (temp[i] == '|' && msh->error == 0)
			count_pipes(msh, temp);
		else if (temp[i] == '<' && temp[i + 1] != '<' && msh->error == 0)
			check_r_input(msh, temp, i + 1);
		else if (temp[i] == '>' && temp[i + 1] != '>' && msh->error == 0)
			check_r_output(msh, temp, i + 1);
		else if (temp[i] == '>' && temp[i + 1] == '>' && msh->error == 0)
			check_append(msh, temp, i + 2);
		else if (temp[i] == '<' && temp[i + 1] == '<' && msh->error == 0)
			check_heredoc(msh, temp, i + 2);
		if (msh->error == 1)
			return ;
		temp++;
	}
}
