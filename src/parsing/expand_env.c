/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/04 13:55:34 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*add_var(t_sh *msh, t_env *env, char *var)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	temp = NULL;
	while (env->env_arr[++i])
	{
		j = 0;
		while (env->env_arr[i][j] != '=')
			j++;
		if (ft_strncmp(env->env_arr[i], var, j + 1) == 0)
		{
			temp = ft_substr(env->env_arr[i], ft_strlen(var), \
					ft_strlen(env->env_arr[i]) - ft_strlen(var));
			if (!temp)
			{
				free(var);
				exit_error(msh, "malloc,", 2);
			}
			return (temp);
		}
	}
	return (temp);
}

char	*check_env_var(t_sh *msh, t_env *env, char *var)
{
	char	*temp;

	if (msh->exit_code_flag)
	{
		msh->exit_code_flag = 0;
		return (var);
	}
	var = ft_strjoin_free(var, "=");
	if (!var)
	{
		free(var);
		exit_error(msh, "malloc", 2);
	}
	temp = add_var(msh, env, var);
	if (temp == NULL)
	{
		free(var);
		return (temp);
	}
	free(var);
	return (temp);
}

char	*extract_var(t_sh *msh, char *start, int len)
{
	char	*var_name;

	if (len == 0 || start == NULL)
	{
		var_name = ft_strdup("");
		if (!var_name)
			exit_error(msh, "malloc", 1);
	}
	else if (start[0] == '?')
		var_name = fetch_exit_code(msh, start);
	else
	{
		var_name = ft_substr(start, 0, len);
		if (!var_name)
			exit_error(msh, "malloc", 1);
	}
	return (var_name);
}

char	*deref_var(t_sh *msh, char *ptr)
{
	int		var_len;
	int		exp_len;
	char	*start;

	var_len = 0;
	start = ptr;
	ptr = env_var_type_check(ptr);
	var_len = ptr - start;
	msh->var = check_env_var(msh, msh->env, extract_var(msh, start, var_len));
	exp_len = ft_strlen(msh->var);
	if (msh->var)
	{
		msh->buf_len += exp_len;
		if (msh->buf_len > msh->max_len)
		{
			free_and_null(msh->var);
			exit_error(msh, "max_arg limit exceeded", 2);
		}
		ft_strlcat(msh->buffer, msh->var, msh->buf_len + 1);
		while (ft_isspace(*ptr))
			msh->buffer[msh->buf_len++] = *ptr++;
	}
	if (msh->var)
		free_and_null(msh->var);
	return (ptr);
}

char	*expand_env(t_sh *msh, char *cmd)
{
	msh->buf_len = 0;
	msh->max_len = MAX_ARGS - env_memory(msh) - ft_strlen(cmd);
	msh->buffer = ft_calloc(msh->max_len, 1);
	if (!msh->buffer)
		exit_error(msh, "malloc", 2);
	handle_expansion(msh, cmd);
	free_and_null(cmd);
	return (msh->buffer);
}
