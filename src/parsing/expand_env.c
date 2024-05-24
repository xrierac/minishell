/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/24 16:19:22 by tcampbel         ###   ########.fr       */
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
				exit_error(msh, "ft_substr", 127);
			return (temp);
		}
	}
	return (temp);
}

char	*check_env_var(t_sh *msh, t_env *env, char *var)
{
	char	*temp;

	var = ft_strjoin_free(var, "=");
	if (!var)
		exit_error(msh, "ft_strjoin", 127);
	temp = add_var(msh, env, var);
	if (temp == NULL)
	{
		temp = ft_strdup("");
		if (!temp)
			exit_error(msh, "ft_strdup", 127);
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
			exit_error(msh, "ft_strdup", 127);
	}
	else
	{
		var_name = ft_substr(start, 0, len);
		if (!var_name)
			exit_error(msh, "ft_substr", 127);
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
	if (*(ptr + 1) == '?')
		start++;
	else
	{
		while (*ptr && ((ft_isalnum(*ptr) == 1) || *ptr == '_'))
			ptr++;
		var_len = ptr - start;
	}
	msh->var = check_env_var(msh, msh->env, extract_var(msh, start, var_len));
	exp_len = ft_strlen(msh->var);
	if (msh->var[0] != '\0')
	{
		msh->buf_len += exp_len;
		ft_strlcat(msh->buffer, msh->var, msh->buf_len + 1);
		while (ft_isspace(*ptr))
			msh->buffer[msh->buf_len++] = *ptr++;
	}
	if (msh->var)
		free (msh->var);
	return (ptr);
}


char	*expand_env(t_sh *msh, char *cmd)
{
	char	*ptr;

	ptr = cmd;
	msh->buf_len = 0;
	msh->buffer = ft_calloc(MAX_ARGS, 1);
	if (!msh->buffer)
		exit_error(msh, "calloc", 127);
	while (*ptr)
	{
		if (*ptr == '\'')
			ptr = handle_squote(msh, ptr);
		else if (*ptr == '\"')
			ptr = handle_dquote(msh, ptr);
		else if (*ptr == '$' && (*(ptr + 1) != ' ' && *(ptr + 1)) != '\0')
		{
			ptr = deref_var(msh, ptr + 1);
			if (msh->var[0] == '\0' && *ptr == '\0')
				break ;
		}
		else
			msh->buffer[msh->buf_len++] = *ptr++;
	}
	msh->buffer[msh->buf_len] = '\0';
	free (cmd);
	return (msh->buffer);
}

char	*check_exit_code(t_sh *msh, char *ptr)
{
	char	*exit_code;

	exit_code = ft_itoa(msh->exit_code);
	if (!exit_code)
		exit_error(msh, "malloc", 1);
	return (exit_code);
}
