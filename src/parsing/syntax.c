/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:43:43 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/30 17:30:47 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pre_check(t_sh *msh, char *str)
{
	if (!str)
		exit_error(msh, "malloc", 2);
	if (str[0] == '|' && msh->error == 0)
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `|'\n");
		msh->error = 1;
	}
	if (str[0] == '\0')
		msh->error = 1;
}

char	*env_variable(t_sh *msh, char *str)
{
	char	*result;

	if (ft_strchr(str, '$'))
	{
		result = expand_env(msh, str);
		if (!result[0])
			msh->error = 1;
	}
	else
		result = str;
	return (result);
}

char	*syntax_check(t_sh *msh, char *temp)
{
	char	*res;

	msh->cmd = ft_strtrim(temp, " ");
	pre_check(msh, msh->cmd);
	if (msh->error == 0)
	{
		count_quotes(msh, msh->cmd);
		count_pipes(msh, msh->cmd);
		if (msh->error == 1)
			return (msh->cmd);
		heredoc(msh, msh->cmd);
		if (msh->error == 1)
			return (msh->cmd);
		res = env_variable(msh, msh->cmd);
		if (msh->error == 1)
			return (res);
		check_str(msh, res);
		return (res);
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
		else if (*temp == '|' && msh->error == 0)
			temp = check_pipes(msh, temp);
		else if (current_op(temp) && msh->error == 0)
			temp = check_op_syntax(msh, temp);
		else
			temp++;
		if (msh->error == 1)
			return ;
	}
}
