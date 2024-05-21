/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:43:43 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/21 15:59:11 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pre_check(t_sh *msh, char *str)
{
	if (!str)
		exit_error(msh, "ft_strtrim", 127);
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
	char	*trim_str;
	char	*res;

	trim_str = ft_strtrim(temp, " ");
	pre_check(msh, trim_str);
	if (msh->error == 0)
	{
		count_quotes(msh, trim_str);
		count_pipes(msh, trim_str);
		if (msh->error == 1)
			return (trim_str);
		heredoc(msh, trim_str);
		if (msh->error == 1)
			return (trim_str);
		res = env_variable(msh, trim_str);
		if (msh->error == 1)
			return (res);
		check_str(msh, res);
		return (res);
	}
	return (trim_str);
}

void	check_str(t_sh *msh, char *temp)
{
	int	i;

	i = 0;
	while (*temp)
	{
		if ((*temp == '\'' || *temp == '\"') && msh->error == 0)
			temp = find_quote_ptr(temp, *temp);
		else if (*temp == '|' && msh->error == 0)
			check_pipes(msh, temp);
		else if (current_op(temp) && msh->error == 0)
			temp = check_op_syntax(msh, temp);
		if (msh->error == 1)
			return ;
		temp++;
	}
}
