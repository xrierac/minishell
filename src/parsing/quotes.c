/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:00:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/06 14:22:16 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_quote(char *str, char q, int i)
{
	while (str[i] != q && str[i])
		i++;
	if (str[i])
		i++;
	return (i);
}

char	set_quote(char	*str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
		if (str[i])
			i++;
	}
	return (0);
}

void	count_quotes(t_sh *msh, char *str)
{
	int		i;
	char	q;

	msh->count = 0;
	i = 0;
	while (str[i])
	{
		q = set_quote(str, i);
		if (str[i] == q)
		{
			msh->count++;
			i++;
			while (str[i] != q && str[i])
				i++;
			if (str[i] == q)
				msh->count++;
		}
		if (str[i])
			i++;
	}
	if (msh->count % 2 != 0)
	{
		ft_printf(2, "I think you dropped this -> %c\n", q);
		msh->error = 1;
	}
}

char	*remove_quotes(t_sh *msh, char *str, int i)
{
	int		j;
	char	*result;
	char	quote;

	j = 0;
	result = ft_calloc(ft_strlen(str), 1);
	if (!result)
		exit_error(msh, "malloc", 2);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			if (str[i] == quote)
				i++;
			while (str[i] != quote && str[i])
				result[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			result[j++] = str[i++];
	}
	free(str);
	return (result);
}

int	quote_search(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}
