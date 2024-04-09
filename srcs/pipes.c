/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:59:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/09 15:22:05 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	find_quote(t_sh *msh, char *input, int i, char q)
// {
// 	ft_strrchr(input, q);
// }

void count_pipes(t_sh *msh, char *input)
{
	int	d_quote;
	int	s_quote;
	int	i;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	msh->pipes = 0;
	while (input[++i])
	{
		if (input[i] == '|')
			msh->pipes++;
		if (input[i] == '\'')
		{
			++i;
			while (input[i] != '\'' && input[i])
				++i;
			s_quote++;
		}
		if (input[i] == '\"')
		{
			++i;
			while (input[i] != '\"' && input[i])
				++i;
			d_quote++;
		}
	}
	if (s_quote % 2 != 0)
		printf("quote>\n");
	else if (d_quote % 2 != 0)
		printf("dquote>\n");
}
