/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:44:06 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/29 14:24:04 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*redirect_in(t_sh *msh, char *input)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_substr(input, i, 1);
	return (temp);
}

void	get_token(t_sh *msh, t_lex *lex_arr, char *str)
{
	if (ft_strncmp(str, "$?", 3))
		lex_arr->token = STATUS;
	else if (ft_strncmp(str, "<", 2))
		lex_arr->token = R_INPUT;
	else if (ft_strncmp(str, ">", 2))
		lex_arr->token = R_OUTPUT;
	else if (ft_strncmp(str, "<<", 3))
		lex_arr->token = HEREDOC;
	else if (ft_strncmp(str, ">>", 3))
		lex_arr->token = APPEND;
	// else if (first_str(str) == true)
	// 	lex_arr->token = CMD;
}

