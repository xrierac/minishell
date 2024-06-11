/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:40:55 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/07 13:21:23 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	ft_echo(char **arr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arr[++j] && ft_strncmp(arr[j], "-n", 2) == 0 && check_flag(arr[j]))
		i++;
	while (arr[++i])
	{
		ft_putstr_fd(arr[i], 1);
		if (arr[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (arr[1] && check_flag(arr[1]) == 1)
		return (0);
	printf("\n");
	return (0);
}
