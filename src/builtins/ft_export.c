/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:36:11 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/07 10:39:58 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	find_equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] == '=')
			break ;
	}
	return (i);
}

static int	existing_var(t_env *env_struct, char *str)
{
	int		i;
	size_t	len;

	i = 0;
	len = find_equal_sign(str);
	while (env_struct->env_arr[i])
	{
		if (ft_strncmp(env_struct->env_arr[i], str, len) == 0)
		{
			free(env_struct->env_arr[i]);
			env_struct->env_arr[i] = ft_strdup(str);
			return (i);
		}
		i++;
	}
	return (-1);
}

static int	new_path_arr(t_env *env_s, char *str)
{
	if (ft_strncmp(str, "PATH=", 5) == 0)
	{
		ft_free_array(env_s->path_arr);
		env_s->path_arr = ft_split(ft_getenv("PATH=", env_s->env_arr), ':');
		if (!env_s->path_arr)
			return (-1);
	}
	return (0);
}

static int	check_export(t_env *env_s, char *str)
{
	int	i;

	i = -1;
	if (!str)
	{
		while (env_s->env_arr[++i])
			printf("declare -x %s\n", env_s->env_arr[i]);
		return (0);
	}
	return (1);
}

int	ft_export(t_env *env_s, char *str)
{
	char	**new_env;
	int		i;

	if (check_export(env_s, str) != 1)
		return (0);
	if (existing_var(env_s, str) == -1)
	{
		new_env = ft_calloc(array_size(env_s->env_arr) + 2, sizeof(char *));
		if (!new_env)
			return (1);
		i = -1;
		while (env_s->env_arr[++i])
			new_env[i] = env_s->env_arr[i];
		new_env[i] = ft_strdup(str);
		new_env[++i] = NULL;
		free(env_s->env_arr);
		env_s->env_arr = new_env;
	}
	new_path_arr(env_s, str);
	return (0);
}