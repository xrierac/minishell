/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/04 17:55:40 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_all(t_sh *msh)
{
	if (msh->lex_arr != NULL)
	{
		free_lex(msh->lex_arr);
		msh->lex_arr = NULL;
	}
	if (msh->env != NULL)
		free_env(msh->env);
	if (msh != NULL)
		free_msh(msh);
}

void	free_lex(t_lex ***lex_arr)
{
	int	i;
	int	j;

	i = -1;
	while (lex_arr[++i])
	{
		j = -1;
		while (lex_arr[i][++j])
		{
			if (lex_arr[i][j]->fd > 0)
				close(lex_arr[i][j]->fd);
			ft_free_array(lex_arr[i][j]->cmd_arr);
			free(lex_arr[i][j]);
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
	env = NULL;
}

void	free_msh(t_sh *msh)
{
	if (msh->pipe_arr != NULL)
	{
		ft_free_array(msh->pipe_arr);
		msh->pipe_arr = NULL;
	}
	if (msh->buffer != NULL)
	{
		free(msh->buffer);
		msh->buffer = NULL;
	}
	if (msh->var != NULL)
	{
		free(msh->var);
		msh->var = NULL;
	}
	if (msh->cmd != NULL)
	{
		free(msh->cmd);
		msh->cmd = NULL;
	}
	free(msh);
	msh = NULL;
}

void	free_var(t_sh *msh)
{
	if (msh->var)
	{
		free(msh->var);
		msh->var = NULL;
	}
}
