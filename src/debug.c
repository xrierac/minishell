/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:37:50 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/04 17:55:16 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_arr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("%s\n", str[i]);
}

void	print_lex(t_sh *msh, t_lex	***lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < msh->processes)
	{
		j = 0;
		while (msh->tok_count > j)
		{
			print_arr(lex[i][j]->cmd_arr);
			j++;
		}
		i++;
	}
}
