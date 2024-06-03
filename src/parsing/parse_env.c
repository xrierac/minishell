/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:36:36 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/30 14:12:45 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Creates path directory 2d array
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
	return (atoi(temp));
}

void	get_lvl(t_sh *msh, char **temp, int i)
{
	char	*lvl;

	msh->env->shlvl = cur_lvl(temp[i]) + 1;
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
		exit_error(msh, "malloc: ", 127);
	while (ev[i] || i < len)
	{
		temp[i] = ft_strdup(ev[i]);
		if (!temp[i])
			exit_error(msh, "ft_strdup: ", 127);
		get_path(msh, env, ev, i);
		if (ft_strncmp(ev[i], "SHLVL=", 6) == 0)
			get_lvl(msh, temp, i);
		i++;
	}
	env->env_arr = temp;
}

int	env_memory(t_sh *msh)
{
	int		i;
	int		j;
	int		bytes;
	char	**env;

	i = -1;
	j = -1;
	env = msh->env->env_arr;
	while (env[++i])
	{
		bytes += 8;
		while (env[i][++j])
			bytes++;
		i++;
	}
	return (bytes);
}
