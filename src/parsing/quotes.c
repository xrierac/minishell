/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:00:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/20 15:56:52 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_quote(char *str, char q, int i)
{
	while (str[i] != q && str[i])
		i++;
	return (i + 1);
}

char	set_quote(char	*str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
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
		i++;
	}
	if (msh->count % 2 != 0)
	{
		ft_printf(2, "Close your quotes puta!\n");
		msh->error = 1;
	}
}

char	*remove_quotes(t_sh *msh, char *str)
{
	int		i;
	int		j;
	char	*result;
	char	quote;

	i = 0;
	j = 0;
	result = ft_calloc(ft_strlen(str), 1);
	if (!result)
		exit_error(msh, "ft_calloc", 127);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			if (str[i] == quote)
				i++;
			while (str[i] != quote && str[i])
			{
				result[j] = str[i];
				j++;
				i++;
			}
		}
		i++;
	}
	result[j] = '\0';
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

char	*find_quote_ptr(char *str, char q)
{
	str++;
	while (*str != q && *str)
		str++;
	return (str + 1);
}
