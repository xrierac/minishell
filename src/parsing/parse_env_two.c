/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:03:47 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/06 15:44:41 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	new_pwd(t_sh *msh, t_env *env_s)
{
	char	*str;
	char	**arr;
	char	*buf;

	buf = return_ptr_cwd(env_s);
	if (!buf)
		exit_error(msh, "malloc", 2);
	str = ft_strjoin("export PWD=", buf);
	free(buf);
	if (!str)
		exit_error(msh, "malloc", 2);
	arr = ft_split(str, ' ');
	free(str);
	if (!arr)
		exit_error(msh, "malloc", 2);
	ft_export(env_s, arr, 0);
	ft_free_array(arr);
}

void	get_home(t_sh *msh, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			msh->env->home = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			if (!msh->env->home)
				exit_error(msh, "malloc", 2);
			break ;
		}
	}
}
