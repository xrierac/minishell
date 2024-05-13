/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/06 13:52:50 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_sh	*init_msh(char **ev)
{
	t_sh	*msh;

	msh = ft_calloc(1, sizeof(t_sh));
	if (!msh)
		exit_error(msh, "calloc", 127);
	msh->env = ft_calloc(1, sizeof(t_env));
	if (!msh->env)
	{
		free_all(msh);
		exit_error(msh, "calloc", 127);
	}
	init_env(msh->env);
	msh->pipes = 0;
	msh->processes = 0;
	msh->tok_count = 0;
	msh->error = false;
	msh->quotes = 0;
	msh->pipe_arr = NULL;
	ft_envcpy(msh, msh->env, ev);
	return (msh);
}

void	init_env(t_env *env)
{
	env->env_arr = NULL;
	env->env_path = NULL;
	env->path_arr = NULL;
	env->var_len = 0;
}

t_lex	***init_lex(t_sh *msh)
{
	int	i;

	i = -1;
	msh->processes = msh->pipes + 1;
	msh->lex_arr = (t_lex ***)malloc((msh->processes + 1) * sizeof(t_lex **));
	if (!msh->lex_arr)
		exit_error(msh, "malloc", 127);
	while (++i <= msh->processes)
	{
		msh->lex_arr[i] = (t_lex **)malloc(sizeof(t_lex *));
		if (!msh->lex_arr[i])
			exit_error(msh, "malloc", 127);
	}
	msh->lex_arr[msh->processes] = NULL;
	return (msh->lex_arr);
}

void	init_token(t_sh *msh, t_lex **lex_arr)
{
	int	i;

	i = -1;
	while (++i < msh->tok_count)
	{
		lex_arr[i] = ft_calloc(sizeof(t_lex), 1);
		if (!lex_arr[i])
			exit_error(msh, "malloc", 127);
	}
	lex_arr[msh->tok_count] = NULL;
}

char	**init_cmd_arr(t_sh *msh)
{
	char	**temp;

	temp = ft_calloc(sizeof(char *), 1);
	if (!temp)
	{
		free_all(msh);
		exit_error(msh, "ft_calloc", 127);
	}
	return (temp);
}

