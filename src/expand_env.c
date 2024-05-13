/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/03 18:31:36 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_env_var(t_sh *msh, t_env *env, char *var)
{
	int		i;
	int		k;
	char	*temp;

	i = -1;
	while (env->env_arr[++i])
	{
		k = 0;
		while (env->env_arr[i][k] != '=')
			k++;
		if (ft_strncmp(env->env_arr[i], var, k) == 0)
		{
			temp = ft_substr(env->env_arr[i], ft_strlen(var) + 1, \
					ft_strlen(env->env_arr[i]) - ft_strlen(var) + 1);
			if (!temp)
				exit_error(msh, "ft_substr", 127);
			break ;
		}
	}
	if (env->env_arr[i] == NULL)
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
		var_name = ft_strdup("");
		if (!var_name)
			exit_error(msh, "ft_strdup", 127);
	else
	{
		var_name = ft_substr(start, 0, len);
		if (!var_name)
			exit_error(msh, "ft_substr", 127);
	}
	return (var_name);
}

char	*expand_env(t_sh *msh, char *cmd)
{
	int		var_len;
	int		exp_len;
	int		buf_len;
	char	*buffer;
	char	*ptr;
	char	*start;
	char	*var;

	ptr = cmd;
	start = NULL;
	buf_len = 0;
	buffer = ft_calloc(ft_strlen(cmd) + 1, 1);
	if (!buffer)
		exit_error(msh, "calloc", 127);
	while (*ptr)
	{
		var_len = 0;
		if (*ptr == '$' && (*(ptr + 1) != ' ' && *(ptr + 1)) != '\0')
		{
			ptr++;
			start = ptr;
			while (*ptr && ((ft_isalnum(*ptr) == 1) || *ptr == '_'))
				ptr++;
			var_len = ptr - start;
		}
		var = check_env_var(msh, msh->env, extract_var(msh, start, var_len));
		if (var[0] != '\0')
		{
			exp_len = ft_strlen(var);
			buffer = ft_strjoin_free(buffer, var);
			if (!buffer)
				exit_error(msh, "ft_strjoin_free", 127);
			buf_len += exp_len;
			if (ft_isspace(*ptr))
			{
				buffer[buf_len++] = *ptr++;
				buffer[buf_len] = '\0';
			}
		}
		else if (var[0] == '\0' && *ptr == '\0')
		{
			free (var);
			break ;
		}
		else
		{
			buffer[buf_len++] = *ptr++;
			buffer[buf_len] = '\0';
		}
		free(var);
	}
	free (cmd);
	return (buffer);
}


char	*check_exit_code(t_sh *msh, char *str, int i)
{
	return (ft_strdup("123"));
}
