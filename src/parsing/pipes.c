/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:29:23 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/23 14:42:37 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	count_pipes(t_sh *msh, char *input)
{
	int	i;

	i = 0;
	msh->pipes = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			i = find_quote(input, input[i], i + 1);
		}
		if ((input[i] == '|' && input[i + 1] == '|') \
			|| (input[i] == '|' && input[i + 1] == '\0'))
		{
			ft_printf(2, RED":( "END SYNTAX_ERROR" `|'\n");
			msh->error = true;
			return ;
		}
		else if (input[i] == '|')
			msh->pipes++;
		i++;
	}
}

char	*check_pipes(t_sh *msh, char *input)
{
	if ((*input == '|' && *(input + 1) == '|') \
		|| (*input == '|' && *(input + 1) == '\0'))
	{
		ft_printf(2, RED":( "END SYNTAX_ERROR" `|'\n");
		msh->error = true;
		return (0);
	}
	input++;
	return (input);
}
