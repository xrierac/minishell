/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:32:22 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/06 14:16:07 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static unsigned long	convert_char(const char *str)
{
	unsigned long	num;

	num = 0;
	while (*str >= 48 && *str <= 57)
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	return (num);
}

unsigned long	ft_atoll(const char *str)
{
	int			neg;
	long long	num;

	neg = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	num = convert_char(str);
	return (num * neg);
}

static int	input_validity(char **cmd)
{
	int				i;
	unsigned long	n;

	i = 0;
	if (ft_strlen(cmd[1]) > 20)
	{
		ft_printf(2, "minishell: exit: %s: numeric argument required\n", cmd[1]);
		return (1);
	}
	if (cmd[1][i] == '-' || cmd[1][i] == '+')
		i++;
	n = ft_atoll(cmd[1]);
	while (cmd[1][i])
	{
		if (ft_isdigit(cmd[1][i]) == -1 || n > 9223372036854775807 &&
			ft_strncmp(cmd[1], "-9223372036854775808", 20) != 0)
		{
			ft_printf(2, "minishell: exit: %s: numeric argument required\n",
				cmd[1]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_exit_input(t_sh *msh, char **cmd)
{
	long long	n;

	if (cmd[2] != NULL)
	{
		ft_printf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (input_validity(cmd) == 1)
		return (2);
	n = ft_atoll(cmd[1]);
	free_all(msh);
	exit((unsigned char)n);
	return (0);
}

int	ft_exit(t_sh *msh, char **cmd)
{
	int	i;

	ft_printf(2, "exit\n");
	if (!cmd)
	{
		free_all(msh);
		exit(0);
	}
	else if (cmd[1])
	{
		i = check_exit_input(msh, cmd);
		if (i == 1)
			return (1);
		if (i == 2)
		{
			free_all(msh);
			exit(2);
		}
	}
	else
	{
		free_all(msh);
		exit(0);
	}
	return (0);
}
