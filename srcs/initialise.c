/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:24:02 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/04 17:00:22 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_env(t_sh *msh, t_env *env, char **ev)
{
	int	len;
	int	i;

	len = 0;
	i = -1;

	while (ev[len])
		len++;
	env->env_arr = ft_calloc(sizeof(char *), len + 1);
	if (!env->env_arr)
		exit_error(msh, "malloc: ", 127);
	while (env->env_arr[++i] != NULL)
	{
		env->env_arr[i] = ft_strdup(ev[i]);
		if (ft_strncmp(ev[i], "PATH=", 5) == 0)
		{
			env->env_path = ft_substr(ev[i], 5, ft_strlen(ev[i]) - 5);
			if (!env->env_path)
				exit_error(msh, "ft_substr: ", 127);
		}
		if (ft_strncmp(ev[i], "SHLVL=", 6) == 0)
		{
			free(env->env_arr[i]);
			int lvl = ft_atoi(env->shlvl) + 1;
			env->shlvl = ft_itoa(lvl);
			env->env_arr[i] = ft_strjoin("SHLVL=", env->shlvl);
		}
		if (!env->env_arr[i])
			exit_error(msh, "", 127); 
	}
}


void	initialise(char **ev, t_sh *msh)
{
	msh = ft_calloc(sizeof(t_sh), 1);
	if (!msh)
		exit_error(msh, "malloc: ", 127);
	msh->lex = ft_calloc(sizeof(t_lex), 1);
	if (!msh->lex)
		exit_error(msh, "malloc: ", 127);
	msh->env = ft_calloc(sizeof(t_env), 1);
	if (!msh->env)
		exit_error(msh, "malloc: ", 127);
	msh->env->shlvl = "1";
	get_env(msh, msh->env, ev);
}
