/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:54:17 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/14 15:23:53 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	new_envarr(t_env *env_s, char *str)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(array_size(env_s->env_arr) + 2, sizeof(char *));
	if (!new_env)
		return (generic_error("", "export"));
	while (env_s->env_arr[++i])
		new_env[i] = env_s->env_arr[i];
	new_env[i] = ft_strdup(str);
	if (!new_env[i])
		generic_error("", "export");
	new_env[++i] = NULL;
	free(env_s->env_arr);
	env_s->env_arr = new_env;
	return (0);
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
			if (!env_struct->env_arr[i])
				return (generic_error("", "export"));
			return (0);
		}
		i++;
	}
	return (-1);
}

static int	check_validity(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i != 0)
			break ;
		if (ft_isalpha(str[i]) == 0)
		{
			generic_error(str, "export");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_export(t_env *env_s, char *str)
{
	int		i;
	char	*name;

	i = -1;
	while (env_s->env_arr[++i])
	{
		if (find_equal_sign(env_s->env_arr[i]) != -1)
		{
			name = get_name(env_s->env_arr[i]);
			printf("declare -x %s=\"%s\"\n", name,
				ft_getenv(name, env_s->env_arr));
			free(name);
		}
		else
			printf("declare -x %s\n", env_s->env_arr[i]);
	}
	return (0);
}

int	ft_export(t_env *env_s, char **cmd, int arg)
{
	int	exit;
	int	status;

	exit = 0;
	if (cmd[arg + 1])
		exit += ft_export(env_s, cmd, arg + 1);
	if (arg == 0 && cmd[1] == NULL)
		return (check_export(env_s, cmd[1]));
	if (arg > 0)
	{
		if (check_validity(cmd[arg]) == 1)
			return (1);
		status = existing_var(env_s, cmd[arg]);
		if (status == -1)
			exit += new_envarr(env_s, cmd[arg]);
		new_path_arr(env_s, cmd[arg]);
		if (status == 1)
			exit++;
	}
	return (exit);
}
