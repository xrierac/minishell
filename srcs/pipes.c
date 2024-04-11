/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:59:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/11 14:24:14 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	find_quote(t_sh *msh, char *input, int i, char q)
// {
// 	ft_strrchr(input, q);
// }

void	count_pipes(t_sh *msh, char *input)
{
	int	i;

	i = -1;
	msh->pipes = 0;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = find_quote(input, input[i], i);
		if (input[0] == '|' || (input[i] == '|' && input[i + 1] == '|') \
			|| (input[i] == '|' && input[i + 1] == '\0'))
		{
			ft_printf(2, ":): syntax error near unexpected token `|'\n");
			return ;
		}
		else if (input[i] == '|')
			msh->pipes++;
	}
}
