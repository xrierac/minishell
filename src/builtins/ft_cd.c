/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:42 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/05 14:42:25 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	change_oldpwd(t_env *env_s, char *pwd)
{
	char	**arr;

	arr = malloc(3 * sizeof(char *));
	if (!arr)
		return (generic_error("", "cd"));
	arr[0] = ft_strdup("export");
	if (!arr[0])
	{
		free(arr);
		return (generic_error("", "cd"));
	}
	arr[1] = ft_strjoin("OLDPWD=", pwd);
	if (!arr[1])
	{
		ft_free_array(arr);
		return (generic_error("", "cd"));
	}
	arr[2] = NULL;
	ft_export(env_s, arr, 1);
	ft_free_array(arr);
	return (0);
}

static int	change_pwd(t_env *env_s, char *pwd)
{
	char	**arr;

	arr = malloc(3 * sizeof(char *));
	if (!arr)
		return (generic_error("", "cd"));
	arr[0] = ft_strdup("export");
	if (!arr[0])
	{
		free(arr);
		return (generic_error("", "cd"));
	}
	arr[1] = ft_strjoin("PWD=", pwd);
	if (!arr[1])
	{
		ft_free_array(arr);
		return (generic_error("", "cd"));
	}
	arr[2] = NULL;
	ft_export(env_s, arr, 1);
	ft_free_array(arr);
	return (0);
}

static int	check_dir(char *str)
{
	DIR	*ptr;

	ptr = opendir(str);
	if (!ptr)
		return (generic_error(str, "cd"));
	closedir(ptr);
	return (0);
}

int	ft_cd(char *str, t_env *env_s)
{
	char	*ptr;
	char	*buf;

	if (!str)
		str = ft_getenv("HOME", env_s->env_arr);
	if (!str)
		return (non_perror("HOME not set", "cd"));
	if (check_dir(str) == 1)
		return (1);
	buf = (char *)malloc(2097152);
	if (!buf)
		return (generic_error("", "cd"));
	ptr = getcwd(buf, 2097152);
	if (!ptr)
		return (generic_error("", "cd"));
	if (change_oldpwd(env_s, ptr) == 1)
		return (1);
	chdir(str);
	ptr = getcwd(buf, 2097152);
	if (!ptr)
		return (generic_error("", "cd"));
	if (change_pwd(env_s, ptr) == 1)
		return (1);
	free(ptr);
	return (0);
}
