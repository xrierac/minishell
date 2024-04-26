/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/12 15:50:47 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_sh *msh)
{
	// if (msh->lex_arr != NULL)
	// {
	// 	free_lex(msh->lex_arr);
	// 	msh->lex_arr = NULL;
	// }
	if (msh->env != NULL)
		free_env(msh->env);
	if (msh != NULL)
		free(msh);
}

// void	free_lex(t_lex **lex_arr)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = -1;
// 	while (lex_arr[++i])
// 	{
// 		if (lex_arr[i][j] != NULL)
// 		{
// 			while (lex_arr[i][++j])
// 			{
// 				if (lex_arr[i][j]->cmd_arr != NULL)
// 					ft_free_array(lex_arr[i][j]->cmd_arr);
// 				ft_free_array(lex_arr[i][j]);
// 			}
// 		}
// 		ft_free_array(lex_arr[i]);
// 	}
// 	free(lex_arr);
// }

void	free_env(t_env *env)
{
	if (env->env_arr != NULL)
		ft_free_array(env->env_arr);
	if (env->env_path != NULL)
		free(env->env_path);
	if (env->path_arr != NULL)
		ft_free_array(env->path_arr);
	free(env);
}
