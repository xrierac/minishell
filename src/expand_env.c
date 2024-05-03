/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/03 16:00:04 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_env_var(t_sh *msh, t_env *env, char *var)
{
	int		i;
	int		k;
	char	*temp;

	i = -1;
	temp = ft_strdup("");
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
			{
				free_all(msh);
				exit_error(msh, "ft_substr", 127);
			}
		}
	}
	free(var);
	return (temp);
}

int	var_len(char *str, int i)
{
	if (str[i] == '$')
		i++;
	while (str[i] != '$' && ft_isspace(str[i]) == false && str[i])
		i++;
	return (i);
}

char	*extract_var(t_sh *msh, char *start, int len)
{
	char	*var_name;

	var_name = ft_substr(start, 0, len);
	if (!var_name)
	{
		free_all(msh);
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
	char	*result;

	ptr = cmd;
	buf_len = 0;
	if (!ft_strchr(cmd, '$'))
		return (cmd);
	buffer = ft_calloc(ft_strlen(cmd) + 1, 1);
	if (!buffer)
	{
		free_all(msh);
		exit_error(msh, "calloc", 127);
	}
	while (*ptr)
	{
		var_len = 0;
		if (*ptr == '$' && (*(ptr + 1) != ' ' || *(ptr + 1)) != '\0')
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
			buffer = ft_strjoin(buffer, var);
			buf_len += exp_len;
			if (ft_isspace(*ptr))
			{
				buffer[buf_len++] = *ptr++;
				buffer[buf_len] = '\0';
			}
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
// char	*expand_env(t_sh *msh, char *res)
// {
// 	int		i;
// 	int		len;
// 	char	*var;
// 	char	*temp;
// 	char	*temp2;

// 	i = 0;
// 	temp = ft_strdup("");
// 	temp2 = ft_strdup("");
// 	if (!ft_strchr(res, '$'))
// 		return (res);
// 	while (res[i])
// 	{
// 		// else if ((res[i] == '$' && res[i + 1] == '\'') \
// 		// || (res[i] == '$' && res[i + 1] == '\"'))
// 		// 	i += find_quote(res, res[i + 1], i + 1); //need to remove quotes and $
// 		if (res[i] == '$' && (res[i + 1] != '\0' || res[i + 1] != ' '))
// 		{
// 			if (res[i] == '$' && res[i + 1] == '?')
// 			{
// 				var = check_exit_code(msh, res, i); //need to build)
// 				i += 2;
// 			}
// 			else
// 			{
// 				var = check_env_var(msh, msh->env, res, i + 1);
// 			}
// 			i += var_len(res, i);
// 			printf("%i\n", i);
// 			temp = ft_strjoin(temp2, var);
// 		}
// 		else
// 		{
// 			i = find_dollar(res, i);
// 			len = i;
// 			temp2 = ft_substr(res, i, len);
// 			if (!temp2)
// 			{
// 				free_all(msh);
// 				exit_error(msh, "ft_substr", 127);
// 			}
// 			temp2 = ft_strjoin_free(temp2, temp);
// 		}
// 	}
// 	printf("temp2=%s\ntemp = %s\n", temp2, temp);
// 	free(res);
// 	return (temp2);
// }