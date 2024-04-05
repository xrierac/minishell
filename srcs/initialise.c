/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:50 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/05 14:14:36 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Creates path directory 2d array

void	get_path(t_sh *msh, t_env *env, char **ev, int i)
{
	if (ft_strncmp(ev[i], "PATH=", 5) == 0)
	{
		env->env_path = ft_substr(ev[i], 5, ft_strlen(ev[i]) - 5);
		if (!env->env_path)
			exit_error(msh, "ft_substr: ", 127);
		env->path_arr = ft_split(env->env_path, ':');
		if (env->path_arr == NULL)
			exit_error(msh, "ft_split: ", 127);
		free(env->env_path);
	}
}
//Updates the shell level, super important

void	get_lvl(t_sh *msh, char **temp, char **ev, int i)
{
	char	*lvl;

	if (ft_strncmp(ev[i], "SHLVL=", 6) == 0)
	{
		free(temp[i]);
		lvl = ft_itoa(msh->env->shlvl + 1);
		temp[i] = ft_strjoin("SHLVL=", lvl);
		if (!temp)
			exit_error(msh, "ft_strjoin: ", 127);
	}
}
// gets the environment and stores its in a 2d array

void	get_env(t_sh *msh, t_env *env, char **ev)
{
	int		len;
	int		i;
	char	**temp;

	len = 0;
	i = 0;
	while (ev[len])
		len++;
	temp = ft_calloc(len + 1, sizeof(char *));
	if (!temp)
		exit_error(msh, "malloc: ", 127);
	while (ev[i] || i < len)
	{
		temp[i] = ft_strdup(ev[i]);
		if (!temp[i])
			exit_error(msh, "ft_strdup: ", 127);
		get_path(msh, env, ev, i);
		get_lvl(msh, temp, ev, i);
		i++;
	}
	env->env_arr = temp;
}


void	initialise(char **ev, t_sh *msh)
{
	msh = ft_calloc(sizeof(t_sh), 1);
	if (!msh)
		exit_error(msh, "calloc: ", 127);
	msh->lex = ft_calloc(sizeof(t_lex), 1);
	if (!msh->lex)
	{
		free_all(msh);
		exit_error(msh, "calloc: ", 127);
	}
	msh->env = ft_calloc(sizeof(t_env), 1);
	if (!msh->env)
	{
		free_all(msh);
		exit_error(msh, "calloc: ", 127);
	}
	msh->env->shlvl = 1;
	get_env(msh, msh->env, ev);
}
