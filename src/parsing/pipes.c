/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:29:23 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/03 16:51:38 by tcampbel         ###   ########.fr       */
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
		if (msh->error == 1)
			ft_printf(2, RED":( "END SYNTAX_ERROR" `|'\n");
		if (input[i] == '\'' || input[i] == '\"')
			i = find_quote(input, input[i], i + 1);
		if (input[i] == '|' && input[i + 1] == '|')
			msh->error = 1;
		else if (input[i] == '|' && input[i + 1] == '\0')
			msh->error = 1;
		else if (input[i] == '|')
			msh->pipes++;
		if (input[i])
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
