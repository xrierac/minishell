/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:43:43 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/20 18:07:18 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pre_check(t_sh *msh, char *start)
{
	if (!start)
		exit_error(msh, "ft_strtrim", 127);
	if (start[0] == '|' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `|'\n");
		msh->error = 1;
	}
	if (start[0] == '\0')
		msh->error = 1;
}

char	*syntax_check(t_sh *msh, char *temp)
{
	char	*start;
	char	*input;
	char	*res;

	start = ft_strtrim(temp, " ");
	pre_check(msh, start);
	input = ft_strdup(start);
	if (!input)
		exit_error(msh, "ft_strdup", 127);
	if (msh->error == 0)
	{
		count_quotes(msh, start);
		heredoc(msh, start);
		if (ft_strchr(start, '$'))
		{
			res = expand_env(msh, start);
			if (!res[0])
			{
				msh->error = 1;
				return (res);
			}
		}
		else
			res = start;
		check_str(msh, res);
		free(input);
		return (res);
	}
	free(start);
	return (input);
}

void	check_str(t_sh *msh, char *temp)
{
	int	i;

	i = 0;
	while (*temp)
	{
		if ((*temp == '\'' || *temp == '\"') && msh->error == 0)
			temp = find_quote_ptr(temp, *temp);
		else if ((ft_strncmp(temp, "<<<", 4) == 0 \
			|| ft_strncmp(temp, "<<< ", 4) == 0) && msh->error == 0)
		{
			msh->error = 1;
			ft_printf(2, RED":( "END"Here strings have no power here!\n");
		}
		else if (*temp == '|' && msh->error == 0)
			check_pipes(msh, temp);
		else if (current_op(temp) && msh->error == 0)
			temp = check_op_syntax(msh, temp);
		if (msh->error == 1)
			return ;
		temp++;
	}
}
