/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:43:43 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/06 10:59:51 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pre_check(t_sh *msh, char *str)
{
	if (str[0] == '|')
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `|'\n");
		msh->error = 1;
	}
	if (str[0] == '\0')
		msh->error = 1;
}

static void	env_variable(t_sh *msh)
{
	if (ft_strchr(msh->cmd, '$') || ft_strchr(msh->cmd, '~'))
	{
		msh->cmd = expand_env(msh, msh->cmd);
		msh->buffer = NULL;
		if (!msh->cmd[0])
			msh->error = 1;
	}
}

char	*syntax_check(t_sh *msh, char *temp)
{
	msh->cmd = ft_strtrim(temp, " ");
	if (!msh->cmd)
	{
		free(temp);
		exit_error(msh, "malloc", 2);
	}
	pre_check(msh, msh->cmd);
	if (msh->error == 0)
	{
		count_quotes(msh, msh->cmd);
		count_pipes(msh, msh->cmd);
		if (msh->error == 0 && find_hd(msh->cmd))
			heredoc(msh, msh->cmd);
		if (msh->error == 1)
			return (msh->cmd);
		env_variable(msh);
		check_str(msh, msh->cmd);
		return (msh->cmd);
	}
	return (msh->cmd);
}

void	check_str(t_sh *msh, char *res)
{
	int		i;
	char	*temp;

	i = 0;
	temp = res;
	while (*temp)
	{
		if ((*temp == '\'' || *temp == '\"') && msh->error == 0)
			temp = find_quote_ptr(temp, *temp);
		else if (current_op(temp) && msh->error == 0)
			temp = check_op_syntax(msh, temp);
		else
			temp++;
		if (msh->error == 1)
			return ;
	}
}
