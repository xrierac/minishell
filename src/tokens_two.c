/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:44:06 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/23 13:35:07 by tcampbel         ###   ########.fr       */
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
	if (ft_strncmp(str, "$", 2))
		lex_arr->token = ENV;
	else if (ft_strncmp(str, "$?", 3))
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
	// else
	// 	lex_arr->token = ARG;
}

// void	assign_token(t_sh *msh, t_lex *lex_arr, char **pipe_arr)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;

// 	i = -1;
// 	j = -1;
// 	temp = ft_strdup(pipe_arr[0]);
// 	while (*temp)
// 	{
// 		if (*temp == '$')
// 		{
// 			lex_arr[i].cmd_arr[j] = deref_env_var(msh, temp);
// 			if (!lex_arr[i].cmd_arr)
// 			{
// 				free_all(msh);
// 				exit_error(msh, "malloc\n", 127);
// 			}
// 			get_token(msh, lex_arr, lex_arr[i].cmd_arr[j]);
// 		}
// 		if (*temp == '<' && *temp + 1 != '<')
// 		{
// 			lex_arr[i].cmd_arr[j] = redirect_in(msh, temp);
// 			get_token(msh, lex_arr, lex_arr[i].cmd_arr[j]);
// 		}
// 		temp++;
// 	}
	//free(temp);
//}

