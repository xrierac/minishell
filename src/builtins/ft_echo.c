/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:40:55 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/05 15:59:17 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_echo_variable(char *str)
{
	while (*str)
	{
		if (*str != '$')
			write(1, str, 1);
		else
		{
			printf("%s", getenv(++str));
			break ;
		}
		str++;
	}
	
}

void	ft_echo(char **arr)
{
	int	i;
	
	i = 0;
	if (arr[1] && ft_strncmp(arr[1], "-n", 3) == 0)
		i++;
	while (arr[++i])
	{
		if (ft_strchr(arr[i], '$') != 0)
			ft_echo_variable(arr[i]);
		else
			printf("%s", arr[i]);
	}
	if (arr[1] && !ft_strncmp(arr[1], "-n", 3) )
		return ;
	printf("\n");
}
