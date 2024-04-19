/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:59:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/19 17:54:22 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	count_pipes(t_sh *msh, char *input)
{
	int	i;

	i = -1;
	msh->pipes = 0;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = find_quote(input, input[i], i) + 1;
		if ((input[i] == '|' && input[i + 1] == '|') \
			|| (input[i] == '|' && input[i + 1] == '\0'))
		{
			ft_printf(2, RED":( "END SYNTAX_ERROR" `|'\n");
			msh->error = true;
			return ;
		}
		else if (input[i] == '|')
			msh->pipes++;
	}
}
