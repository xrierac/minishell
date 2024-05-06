/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/03 18:14:40 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_sh *msh)
{
	if (msh->lex_arr != NULL)
	{
		free_lex(msh, msh->lex_arr);
		msh->lex_arr = NULL;
	}
	if (msh->env != NULL)
		free_env(msh->env);
	if (msh != NULL)
		free(msh);
}

void	free_lex(t_sh *msh, t_lex ***lex_arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < msh->len)
	{
			while (j < msh->tok_count)
			{
				if (lex_arr[i][j]->cmd_arr != NULL)
					ft_free_array(lex_arr[i][j]->cmd_arr);
				free(lex_arr[i][j]);
				j++;
			}
		free(lex_arr[i]);
		lex_arr[i] = NULL;
		i++;
	}
	free(lex_arr);
}

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
