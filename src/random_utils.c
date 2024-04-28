/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:13:46 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/22 17:33:22 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	is_op(char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] == '<') \
		|| (str[i] == '>' && str[i + 1] == '>') \
		|| (str[i] == '!' && str[i + 1] == '?'))
		return (true);
	else if (str[i] == '<' || str[i] == '>')
		return (true);
	return (false);
}

int	iter_str(char *str, int i)
{
	while (str[i])
	{
		if (ft_isspace(str[i]) == true || str[i] == '<' || str[i] == '>' \
						|| str[i] == '$' || str[i] == '!')
			break ;
		i++;
	}
	return (i);
}

t_bool	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

char	*choose_op(char c)
{
	if (c == '<')
		return ("<");
	else if (c == '>')
		return (">");
	else if (c == '|')
		return ("|");
	return ("");
}

int	is_file(t_sh *msh, char *str, int i)
{
	if (str[i] == '\0')
		return (i);
	while (ft_isspace(str[i]) == true)
		i++;
	if (ft_isspace(str[i]) == false)
	{
		msh->tok_count++;
		while (ft_isspace(str[i]) == false && str[i])
			i++;
	}
	return (i);
}