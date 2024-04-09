/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/09 18:02:54 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_sh	*initialise(char **ev)
{
	t_sh	*msh;

	msh = ft_calloc(1, sizeof(t_sh));
	if (!msh)
		exit_error(msh, "calloc: ", 127);
	msh->env = ft_calloc(1, sizeof(t_env));
	if (!msh->env)
	{
		free_all(msh);
		exit_error(msh, "calloc: ", 127);
	}
	msh->pipes = 0;
	msh->tok_count = 0;
	ft_envcpy(msh, msh->env, ev);
	return (msh);
}

void	init_env(t_env *env)
{
	env->env_arr = NULL;
	env->env_path = NULL;
	env->path_arr = NULL;
}

t_lex **init_lex(t_sh *msh)
{
	int i;

	msh->len = msh->pipes + 1;
	i = -1;
	msh->lex_arr = ft_calloc(msh->len + 1, sizeof(t_lex *));
	if (!msh->lex_arr)
	{
		free_all(msh);
		exit_error(msh, "ft_calloc\n", 127);
	}
	while (++i < msh->len)
	{
		msh->lex_arr[i] = ft_calloc(1, sizeof(t_lex));
		if (!msh->lex_arr[i])
		{
			free_all(msh);
			exit_error(msh, "ft_calloc\n", 127);
		}
	}
	return (msh->lex_arr);
}