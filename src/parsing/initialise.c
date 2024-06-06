/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/06 11:13:46 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_sh	*init_msh(char **ev)
{
	t_sh	*msh;

	msh = ft_calloc(1, sizeof(t_sh));
	if (!msh)
		exit_error(msh, "malloc", 2);
	msh->env = ft_calloc(1, sizeof(t_env));
	if (!msh->env)
		exit_error(msh, "malloc", 2);
	init_env(msh->env);
	msh->pipes = 0;
	msh->processes = 0;
	msh->tok_count = 0;
	msh->error = false;
	msh->pipe_arr = NULL;
	msh->buffer = NULL;
	msh->var = NULL;
	msh->buf_len = 0;
	msh->exit_code = 0;
	msh->lex_arr = NULL;
	msh->cmd = NULL;
	ft_envcpy(msh, msh->env, ev);
	get_home(msh, msh->env->env_arr);
	return (msh);
}

void	init_env(t_env *env)
{
	env->env_arr = NULL;
	env->env_path = NULL;
	env->path_arr = NULL;
	env->var_len = 0;
	env->home = NULL;
}

void	init_lex(t_sh *msh)
{
	int	i;

	i = -1;
	msh->processes = msh->pipes + 1;
	msh->lex_arr = (t_lex ***)malloc((msh->processes + 1) * sizeof(t_lex **));
	if (!msh->lex_arr)
		exit_error(msh, "malloc", 2);
	msh->lex_arr[msh->processes] = NULL;
}

t_lex	**init_token(t_sh *msh)
{
	t_lex	**arr;
	int		i;

	i = -1;
	arr = malloc(sizeof(t_lex *) * (msh->tok_count + 1));
	if (!arr)
		exit_error(msh, "malloc", 2);
	while (++i < msh->tok_count)
	{
		arr[i] = malloc(sizeof(t_lex));
		if (!arr[i])
			exit_error(msh, "malloc", 2);
	}
	arr[msh->tok_count] = NULL;
	return (arr);
}

char	**init_cmd_arr(t_sh *msh)
{
	char	**temp;

	temp = ft_calloc(sizeof(char *), 2);
	if (!temp)
		exit_error(msh, "malloc", 2);
	temp[1] = NULL;
	return (temp);
}
