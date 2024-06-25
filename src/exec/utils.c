/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:54:17 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/25 15:55:57 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] == '=')
			return (i);
	}
	return (-1);
}

char	*get_name(char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(find_equal_sign(str) + 1);
	if (!ptr)
	{
		perror("");
		return (NULL);
	}
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	new_path_arr(t_env *env_s, char *str)
{
	if (ft_strncmp(str, "PATH=", 5) == 0)
	{
		ft_free_array(env_s->path_arr);
		env_s->path_arr = ft_split(str + 5, ':');
		if (!env_s->path_arr)
			return (generic_error("", "Error updating path array"));
	}
	if (ft_strncmp(str, "PATH", 4) == 0 && str[4] == '\0')
	{
		ft_free_array(env_s->path_arr);
		env_s->path_arr = ft_split("", ' ');
	}
	return (0);
}

size_t	array_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*ft_getenv(const char *name, char **env)
{
	int		i;
	int		len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && len == find_equal_sign(env[i]))
			break ;
		i++;
	}
	if (!env[i])
		return (0);
	return (env[i] + len + 1);
}
