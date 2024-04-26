/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:15:56 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/22 14:35:35 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_split(t_sh *msh, t_lex *lex_arr, char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (is_op(input, i) == true)
		{
			lex_arr = init_tok(msh, lex_arr);
		}
	}
}

t_lex	*init_tok(t_sh *msh, t_lex *lex_arr)
{
	t_lex	*token;

	token = ft_calloc(1, sizeof(t_lex));
	if (!token)
	{
		free_all(msh);
		exit_error(msh, "calloc", 127);
	}
}
