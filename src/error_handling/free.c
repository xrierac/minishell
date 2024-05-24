/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/20 15:59:13 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		free_msh(msh);
}

void	free_lex(t_sh *msh, t_lex ***lex_arr)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (lex_arr[++i] != NULL)
	{
		j = -1;
		while (lex_arr[i][++j] != NULL)
		{
			if (lex_arr[i][j]->cmd_arr != NULL)
				ft_free_array(lex_arr[i][j]->cmd_arr);
			if (lex_arr[i][j] != NULL)
				free(lex_arr[i][j]);
			lex_arr[i][j] = NULL;
		}
		if (lex_arr[i] != NULL)
			free(lex_arr[i]);
		lex_arr[i] = NULL;
	}
	free(lex_arr);
	lex_arr = NULL;
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

void	free_msh(t_sh *msh)
{
	if (msh->pipe_arr)
		ft_free_array(msh->pipe_arr);
	free(msh);
}