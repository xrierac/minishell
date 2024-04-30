/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:40:55 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/26 12:30:56 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	find_end(char *str)
{
	size_t	n;
	int	i;

	n = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			while (ft_isalnum(str[++i]))
				n++;
	}
	return (n);
}

static void	ft_echo_variable(char *str, char **env)
{
	char	*var;
	char 	*sub;
	unsigned int	i;

	i = 0;
	while (*str)
	{
		if (*str != '$')
			write(1, str, 1);
		else
		{
			sub = ft_substr(str + 1, 0, find_end(str));
			var = ft_getenv(sub, env);
			if (var)
				printf("%s", var);
			str += ft_strlen(sub);
			free(sub);
		}
		str++;
	}
}

void	ft_echo(char **arr, char **env)
{
	int		i;
	char	*str;

	i = 0;
	if (arr[1] && ft_strncmp(arr[1], "-n", 3) == 0)
		i++;
	while (arr[++i])
	{
		if (ft_strchr(arr[i], '$') != 0)
			ft_echo_variable(arr[i], env);
		else
			ft_putstr_fd(arr[i], 1);
	}
	if (arr[1] && !ft_strncmp(arr[1], "-n", 3) )
		return ;
	printf("\n");
}
