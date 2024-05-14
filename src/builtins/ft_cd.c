/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:42 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/14 12:04:46 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	change_oldpwd(t_env *env_s, char *pwd)
{
	char **arr;
	
	arr = malloc(3 * sizeof(char *));
	if (!arr)
		return ;
	arr[0] = ft_strdup("export");
	arr[1] = ft_strjoin("OLDPWD=", pwd);
	arr[2] = NULL;
	ft_export(env_s, arr, 1);
	ft_free_array(arr);
}

static void	change_pwd(t_env *env_s, char *pwd)
{
	char **arr;
	
	arr = malloc(3 * sizeof(char *));
	if (!arr)
		return ;
	arr[0] = ft_strdup("export");
	arr[1] = ft_strjoin("PWD=", pwd);
	arr[2] = NULL;
	ft_export(env_s, arr, 1);
	ft_free_array(arr);
}

static int	check_dir(char *str)
{
	DIR	*ptr;

	ptr = opendir(str);
	if (!ptr)
	{
		generic_error(str, "cd");
		return (1);
	}
	closedir(ptr);
	return (0);
}

int	ft_cd(char *str, t_env *env_s)
{
	size_t	size;
	char	*ptr;
	char	*buf;

	if (check_dir(str) == 1)
		return (-1);
	size = 2000;
	buf = (char *)malloc(size);
	if (!buf)
		return (0);
	ptr = getcwd(buf, size);
	change_oldpwd(env_s, ptr);
	if (!str)
		str = ft_getenv("HOME", env_s->env_arr);
	if (chdir(str))
		return (-1);
	ptr = getcwd(buf, size);
	change_pwd(env_s, ptr);
	free(ptr);
	return (0);
}
