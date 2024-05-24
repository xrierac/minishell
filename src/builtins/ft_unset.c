/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:02:56 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/24 14:59:42 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	new_envarr(t_env *env_s, int index)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = -1;
	new_env = ft_calloc(array_size(env_s->env_arr), sizeof(char *));
	if (!new_env)
		return (generic_error("", "unset"));
	while (env_s->env_arr[++i])
	{
		if (i != index)
			new_env[++j] = env_s->env_arr[i];
		else
			free(env_s->env_arr[i]);
	}
	new_env[++j] = NULL;
	free(env_s->env_arr);
	env_s->env_arr = new_env;
	return (0);	
}

static int	check_validity(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (1);
	while (s[i])
	{
		if (ft_isdigit(s[0]) == 1 || (ft_isalnum(s[i]) == 0 && s[i] != '_'))
		{
			ft_printf(2, "minishell: unset: '%s': ", s);
			ft_printf(2, "not a valid identifier\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_exist(char **env, char *str)
{
	char	**arr;
	int		i;
	int		witness;

	i = -1;
	witness = -1;
	while (env[++i])
	{
		arr = ft_split(env[i], '=');
		if (!arr)
			return (-1);
		if (ft_strncmp(arr[0], str, ft_strlen(str)) == 0
		&& ft_strlen(str) == ft_strlen(arr[0]))
			witness = i;
		ft_free_array(arr);
	}
	if (witness == -1)
		return (-1);
	return (witness);
}

int	ft_unset(t_env *env_s, char **cmd, int arg)
{
	int	exit;
	int	index;
	
	exit = 0;
	if (cmd[arg + 1])
		exit += ft_unset(env_s, cmd, arg + 1);
	if (arg == 0)
		return (exit);
	if (check_validity(cmd[arg]) == 1)
		return (1);
	index = check_exist(env_s->env_arr, cmd[arg]);
	if (index == -1)
		return (0);
	if (new_envarr(env_s, index) == 1)
		exit++;
	return (exit);
}
