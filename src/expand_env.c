/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:08 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/02 14:52:49 by tcampbel         ###   ########.fr       */
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
	int		len;
	char	*var;
	char	*temp;
	char	*temp2;

	i = 0;
	temp = ft_strdup("");
	temp2 = ft_strdup("");
	if (!ft_strchr(res, '$'))
		return (res);
	while (res[i])
	{
		// else if ((res[i] == '$' && res[i + 1] == '\'') \
		// || (res[i] == '$' && res[i + 1] == '\"'))
		// 	i += find_quote(res, res[i + 1], i + 1); //need to remove quotes and $
		if (res[i] == '$' && (res[i + 1] != '\0' || res[i + 1] != ' '))
		{
			if (res[i] == '$' && res[i + 1] == '?')
			{
				var = check_exit_code(msh, res, i); //need to build)
				i += 2;
			}
			else
			{
				var = check_env_var(msh, msh->env, res, i + 1);
			}
			i += var_len(res, i);
			printf("%i\n", i);
			temp = ft_strjoin(temp2, var);
		}
		else
		{
			i = find_dollar(res, i);
			len = i;
			temp2 = ft_substr(res, i, len);
			if (!temp2)
			{
				free_all(msh);
				exit_error(msh, "ft_substr", 127);
			}
			temp2 = ft_strjoin_free(temp2, temp);
		}
	}
	printf("temp2=%s\ntemp = %s\n", temp2, temp);
	free(res);
	return (temp2);
}

int	find_dollar(char *str, int i)
{
	while (str[i] != '$' && str[i])
		i++;
	return (i);
}

char	*check_exit_code(t_sh *msh, char *str, int i)
{
	return (ft_strdup("123"));
}
