/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/20 15:56:30 by tcampbel         ###   ########.fr       */
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


char	*handle_squote(t_sh *msh, char *ptr)
{
	msh->buffer[msh->buf_len++] = *ptr++;
	while (*ptr && *ptr != '\'')
	{
		msh->buffer[msh->buf_len++] = *ptr++;
	}
	if (*ptr == '\'')
		msh->buffer[msh->buf_len++] = *ptr++;
	return (ptr);
}

char	*deref_var(t_sh *msh, char *ptr)
{
	int		var_len;
	int		exp_len;
	char	*start;

	var_len = 0;
	start = ptr;
	while (*ptr && ((ft_isalnum(*ptr) == 1) || *ptr == '_') && *ptr != '\"')
		ptr++;
	var_len = ptr - start;
	msh->var = check_env_var(msh, msh->env, extract_var(msh, start, var_len));
	exp_len = ft_strlen(msh->var);
	if (msh->var[0] != '\0')
	{
		msh->buffer = ft_strjoin_free(msh->buffer, msh->var);
		if (!msh->buffer)
			exit_error(msh, "ft_strjoin_free", 127);
		msh->buf_len += exp_len;
		while (ft_isspace(*ptr))
		{
			msh->buffer[msh->buf_len++] = *ptr++;
			msh->buffer[msh->buf_len] = '\0';
		}
	}
	if (msh->var)
		free (msh->var);
	return (ptr);
}

char	*handle_dquote(t_sh *msh, char *ptr)
{
	if (*ptr == '\"')
		msh->buffer[msh->buf_len++] = *ptr++;
	while (*ptr && *ptr != '\"')
	{
		if (*ptr == '$' && *(ptr + 1) != ' ' && *(ptr + 1) \
				&& *(ptr + 1) != '\"')
			ptr = deref_var(msh, ptr + 1);
		else
			msh->buffer[msh->buf_len++] = *ptr++;
	}
	if (*ptr == '\"')
		msh->buffer[msh->buf_len++] = *ptr++;
	return (ptr);
}

char	*expand_env(t_sh *msh, char *cmd)
{
	char	*ptr;

	ptr = cmd;
	msh->buf_len = 0;
	msh->buffer = ft_calloc(ft_strlen(cmd), 1);
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

// char	*expand_env(t_sh *msh, char *cmd)
// {
// 	int		var_len;
// 	int		exp_len;
// 	int		buf_len;
// 	char	*buffer;
// 	char	*ptr;
// 	char	*start;
// 	char	*var;
// 	char	quote;

// 	ptr = cmd;
// 	start = NULL;
// 	buf_len = 0;
// 	buffer = ft_calloc(ft_strlen(cmd) + 1, 1);
// 	if (!buffer)
// 		exit_error(msh, "calloc", 127);
// 	while (*ptr)
// 	{
// 		var_len = 0;
// 		if (*ptr == '\"' || *ptr == '$')
// 		{
// 			if (check_dquote(ptr))
// 			{
// 				while (*ptr && *ptr != '$' && *ptr != '\"' && (ft_isspace(*ptr) || *ptr == '\''))
// 				{
// 					buffer[buf_len++] = *ptr++;
// 					if (*ptr == '$' && (*(ptr + 1) != ' ' && *(ptr + 1)) != '\0')
// 					{
// 						ptr++;
// 						start = ptr;
// 						while (*ptr && ((ft_isalnum(*ptr) == 1) || *ptr == '_') && *ptr != '\"')
// 							ptr++;
// 						var_len = ptr - start;
// 					}
// 				}
// 			}
// 		}
// 		var = check_env_var(msh, msh->env, extract_var(msh, start, var_len));
// 		if (var[0] != '\0')
// 		{
// 			exp_len = ft_strlen(var);
// 			buffer = ft_strjoin_free(buffer, var);
// 			if (!buffer)
// 				exit_error(msh, "ft_strjoin_free", 127);
// 			buf_len += exp_len;
// 			if (ft_isspace(*ptr))
// 			{
// 				buffer[buf_len++] = *ptr++;
// 				buffer[buf_len] = '\0';
// 			}
// 		}
// 		else if (var[0] == '\0' && *ptr == '\0')
// 		{
// 			free (var);
// 			break ;
// 		}
// 		else if (*ptr == '\'')
// 		{
// 			ptr++;
// 			while (*ptr != '\'' && *ptr)
// 				buffer[buf_len++] = *ptr++;
// 			buffer[buf_len] = '\0';
// 		}
// 		else
// 		{
// 			buffer[buf_len++] = *ptr++;
// 			buffer[buf_len] = '\0';
// 		}
// 		free(var);
// 	}
// 	free (cmd);
// 	return (buffer);
// }

char	*check_exit_code(t_sh *msh, char *str, int i)
{
	return (ft_strdup("123"));
}
