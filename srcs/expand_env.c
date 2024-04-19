/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/17 18:41:44 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_env_var(t_sh *msh, t_env *env, char *input, int j)
{
	int		i;
	int		end;
	char	*temp;
	char	*var;

	i = -1;
	temp = ft_strdup("");
	end = j;
	while (input[end] && ft_isspace(input[end]) == false)
		++end;
	var = ft_substr(input, j + 1, end);
	if (!var)
	{
		free_all(msh);
		exit_error(msh, "ft_substr", 127);
	}
	while (env->env_arr[++i])
	{
		if (ft_strncmp(env->env_arr[i], var, ft_strlen(var)) == 0)
			temp = ft_substr(env->env_arr[i], ft_strlen(var) + 1, \
					ft_strlen(env->env_arr[i]) - ft_strlen(var) + 1);
	}
	free(var);
	return (temp);
}

char	*deref_env_var(t_sh *msh, char *input)
{
	int		i;
	int		end;
	char	*var;

	i = 0;
	if ((ft_strncmp(input, "$", 2) == 0) || ft_isspace(input[i + 1]))
		return (ft_strdup("$"));
	else if (ft_strncmp(input, "$?", 3) == 0)
		return (ft_strdup("$?"));
	else if (input[i + 1] == '\'' || input[i + 1] == '\"')
	{
		end = find_quote(input, input[i + 1], i + 2) - 2;
		var = ft_substr(input, i + 2, end);
	}
	else
		var = check_env_var(msh, msh->env, input, i);
	return (var);
}

