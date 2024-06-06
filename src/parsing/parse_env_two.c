/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:03:47 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/06 11:16:44 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_pwd(t_sh *msh, char **temp, int i)
{
	char	*pwd;

	pwd = return_ptr_cwd(msh->env);
	if (!pwd)
		exit_error(msh, "malloc", 2);
	free(temp[i]);
	temp[i] = ft_strjoin("PWD=", pwd);
	if (!temp[i])
		exit_error(msh, "malloc", 2);
}

void	get_home(t_sh *msh, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			printf("%s\n", env[i]);
			msh->env->home = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			if (!msh->env->home)
				exit_error(msh, "malloc", 2);
			break ;
		}
	}
}