/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:29:23 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/04 10:19:25 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_between_pipes(t_sh *msh, char *input, int i)
{
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|' || input[i] == '\0')
	{
		msh->error = 1;
		return (1);
	}
	return (0);
}

void	count_pipes(t_sh *msh, char *input)
{
	int	i;

	i = 0;
	msh->pipes = 0;
	while (input[i] && msh->error == 0)
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = find_quote(input, input[i], i + 1);
		if (input[i] == '|')
		{
			if (check_between_pipes(msh, input, i + 1))
				ft_printf(2, RED":( "END SYNTAX_ERROR" `|'\n");
			else
				msh->pipes++;
		}
		if (input[i])
			i++;
	}
}
