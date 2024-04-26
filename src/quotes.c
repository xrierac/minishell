/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:00:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/22 17:27:05 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_quote(char *str, char q, int i)
{
	while (str[i] != q && str[i])
		++i;
	return (i + 1);
}

char	set_quote(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
	}
	return (0);
}

void	count_quotes(t_sh *msh, char *str)
{
	int		i;
	char	q;

	msh->count = 0;
	i = -1;
	q = set_quote(str);
	while (str[++i])
	{
		if (str[i] == q)
			msh->count++;
	}
	if (msh->count % 2 != 0)
	{
		ft_printf(2, "Close your quotes puta!\n");
		msh->error = 1;
	}
}
