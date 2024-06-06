/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:36:36 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/06 11:04:10 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_path(t_sh *msh, t_env *env, char **ev, int i)
{
	if (ft_strncmp(ev[i], "PATH=", 5) == 0)
	{
		env->env_path = ft_substr(ev[i], 5, ft_strlen(ev[i]) - 5);
		if (!env->env_path)
		{
			free_all(msh);
			exit_error(msh, "ft_substr: ", 127);
		}
		env->path_arr = ft_split(env->env_path, ':');
		if (env->path_arr == NULL)
		{
			free_all(msh);
			exit_error(msh, "ft_split: ", 127);
		}
		free(env->env_path);
		env->env_path = NULL;
	}
}

int	cur_lvl(char *ev)
{
	char	*temp;
	int		j;

	temp = ev;
	j = 0;
	while (j < 6)
	{
		temp++;
		j++;
	}
	return (ft_atoi(temp));
}

void	get_lvl(t_sh *msh, char **temp, int i)
{
	char	*lvl;

	msh->env->shlvl = cur_lvl(temp[i]) + 1;
	if (msh->env->shlvl < 0 || msh->env->shlvl > INT_MAX)
		msh->env->shlvl = 0;
	else if (msh->env->shlvl > 999)
	{
		ft_printf(2, "minishell: warning: shell level ");
		ft_printf(2, "(%i) too high, resetting to 1\n", msh->env->shlvl);
		msh->env->shlvl = 1;
	}
	free(temp[i]);
	lvl = ft_itoa(msh->env->shlvl);
	if (!lvl)
		exit_error(msh, "ft_itoa\n", 127);
	temp[i] = ft_strjoin("SHLVL=", lvl);
	if (!temp[i])
	{
		free_all(msh);
		exit_error(msh, "ft_strjoin\n", 127);
	}
	free(lvl);
}

void	ft_envcpy(t_sh *msh, t_env *env, char **ev)
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
		exit_error(msh, "malloc", 2);
	while (ev[i])
	{
		temp[i] = ft_strdup(ev[i]);
		if (!temp[i])
			exit_error(msh, "malloc", 2);
		get_path(msh, env, ev, i);
		if (ft_strncmp(ev[i], "SHLVL=", 6) == 0)
			get_lvl(msh, temp, i);
		if (ft_strncmp(ev[i], "PWD=", 4) == 0)
			get_pwd(msh, temp, i);
		i++;
	}
	temp[i] = NULL;
	env->env_arr = temp;
}

int	env_memory(t_sh *msh)
{
	int		i;
	int		j;
	int		bytes;
	char	**env;

	bytes = 0;
	i = -1;
	env = msh->env->env_arr;
	while (env[++i])
	{
		j = -1;
		bytes += 8;
		while (env[i][++j])
			bytes++;
	}
	return (bytes);
}
