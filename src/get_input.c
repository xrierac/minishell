/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:47:44 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/03 12:14:11 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_input()
{
	char	*input;

	while (1)
	{
		input = readline("\e[0;32mminishell>\e[0;37m");
		if (input == NULL)
			break ;
		if (!ft_strncmp(input, "exit", 4))
		{
			free(input);
			return ;
		}
		free(input);
	}
}
