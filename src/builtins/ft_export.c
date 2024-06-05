/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:54:17 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/05 11:32:56 by xriera-c         ###   ########.fr       */
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
	new_path_arr(env_s, str);
	return (0);
}

static int	existing_var(t_env *env_s, char *str)
{
	int		i;
	int		old;
	int		new;

	i = 0;
	new = find_equal_sign(str);
	while (env_s->env_arr[i])
	{
		old = find_equal_sign(env_s->env_arr[i]);
		if (old == -1)
			old = ft_strlen(env_s->env_arr[i]);
		if (ft_strncmp(env_s->env_arr[i], str, old) == 0 && new == -1)
			return (0);
		if (ft_strncmp(env_s->env_arr[i], str, old) == 0 && new == old)
		{
			new_path_arr(env_s, str);
			free(env_s->env_arr[i]);
			env_s->env_arr[i] = ft_strdup(str);
			if (!env_s->env_arr[i])
				return (generic_error("", "export"));
			return (0);
		}
		i++;
	}
	return (-1);
}

static int	check_validity(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
	{
		ft_printf(2, "minishell: export: `%s': not a valid identifier\n", s);
		return (1);
	}
	while (s[i])
	{
		if (s[i] == '=' && i != 0)
			break ;
		if (ft_isdigit(s[0]) == 1 || (ft_isalnum(s[i]) == 0 && s[i] != '_'))
		{
			ft_printf(2, "minishell: export: `%s': ", s);
			ft_printf(2, "not a valid identifier\n");
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
			if (!name)
				return (1);
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
		if (cmd[arg][0] == '_' && (cmd[arg][1] == '\0' || cmd[arg][1] == '='))
			return (0);
		if (check_validity(cmd[arg]) == 1)
			return (1);
		status = existing_var(env_s, cmd[arg]);
		if (status == -1)
			exit += new_envarr(env_s, cmd[arg]);
		if (status == 1)
			exit++;
	}
	return (exit);
}
