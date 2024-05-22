/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:40:55 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/22 11:59:30 by xriera-c         ###   ########.fr       */
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

static int	check_flag(char *str)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (str && str[0] == '-' && str[++j])
	{
		if (str[j] == 'n')
			i = 1;
		if (str[j] != 'n')
		{
			i = 0;
			break ;
		}
	}
	return (i);
}

int	ft_echo(char **arr, char **env)
{
	int		i;
	char	*str;
	
	i = check_flag(arr[1]);
	while (arr[++i])
	{
		if (ft_strchr(arr[i], '$') != 0)
			ft_echo_variable(arr[i], env);
		else
			ft_putstr_fd(arr[i], 1);
		if (arr[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (check_flag(arr[1]) == 1)
		return (0);
	printf("\n");
	return (0);
}
