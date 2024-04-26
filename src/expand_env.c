/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/25 13:55:53 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_env_var(t_sh *msh, t_env *env, char *input, int j)
{
	int		i;
	int		k;
	int		end;
	char	*temp;
	char	*var;

	i = -1;
	temp = ft_strdup("");
	end = j;
	while (input[end] && ft_isspace(input[end]) == false && input[end] != '$')
		++end;
	var = ft_substr(input, j, end);
	if (!var)
	{
		free_all(msh);
		exit_error(msh, "ft_substr", 127);
	}
	while (env->env_arr[++i])
	{
		k = 0;
		while (env->env_arr[i][k] != '=')
			k++;
		if (ft_strncmp(env->env_arr[i], var, k) == 0)
			temp = ft_substr(env->env_arr[i], ft_strlen(var) + 1, \
					ft_strlen(env->env_arr[i]) - ft_strlen(var) + 1);
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

char	*expand_env(t_sh *msh, char *res)
{
	int		i;
	int		j;
	char	*var;
	char	*temp;

	i = 0;
	j = 0;
	temp = malloc(ft_strlen(res) + 1);
	if (!temp)
	{
		free_all(msh);
		exit_error(msh, "malloc", 127);
	}
	if (!ft_strchr(res, '$'))
		return (res);
	while (res[i])
	{
		// else if ((res[i] == '$' && res[i + 1] == '\'') \
		// || (res[i] == '$' && res[i + 1] == '\"'))
		// 	i += find_quote(res, res[i + 1], i + 1); //need to remove quotes and $
		if (res[i] == '$' && res[i + 1] != '\0' && res[i + 1] != ' ')
		{
			if (res[i] == '$' && res[i + 1] == '?')
			{
				var = check_exit_code(msh, res, i); //need to build)
				i += 2;
			}
			else
			{
				var = check_env_var(msh, msh->env, res, i + 1);
				i += var_len(res, i);
			}
			temp = ft_strjoin(temp, var);
			free(var);
		}
		else
			temp[j] = res[i];
		i++;
		j++;
			//temp = update_str(msh, var, res);
	}
	free(res);
	printf("%s\n", temp);
	return (temp);
}

//Update the string the dereference env var

char	*update_str(t_sh *msh, char *var, char *str)
{
	int		i;
	int		end;
	char	*temp;
	char	*res;

	end = 0;
	i = 0;
	if (str[i] == '$')
	{
		i++;
		end++;
		while (str[i] != '$' && ft_isspace(str[i]) == false && str[i])
		{
			i++;
			end++;
		}
	}
	msh->env->var_len = ft_strlen(var) + ft_strlen(str) - end;
	printf("Strlen = %zu end = %i Malloced bytes = %i str=%s\n", ft_strlen(str), end, msh->env->var_len + 1, str);
	temp = ft_calloc(1, msh->env->var_len + 1);
	if (!temp)
	{
		free_all(msh);
		exit_error(msh, "malloc", 127);	
	}
	res = insert_str(var, str, temp, end);
	free(str);
	return (res);
}

char	*insert_str(char *var, char *str, char *temp, int end)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			res = ft_strjoin(temp, var);
			//printf("var = %s res= %s\n", var, res);
			while (end-- >= 0)
				i++;
		}
		res[j++] = str[i++];
	}
	//free(str);
	return (res);
}

char	*check_exit_code(t_sh *msh, char *str, int i)
{
	return ("123");
}
