/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:04:25 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/12 14:36:36 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static int	ft_stop(char *base)
{
	int	j;
	int	k;

	j = 0;
	if (base[0] == '\0' || base [1] == '\0')
		return (1);
	while (base[j])
	{
		k = j + 1;
		if (base[j] == '+' || base[j] == '-')
			return (1);
		while (base[k])
		{
			if (base[k] == base[j])
				return (1);
			k++;
		}
		j++;
	}
	return (0);
}

void	ft_putnbr_base(int nbr, char *base)
{
	char	coded;
	long	i;
	long	j;

	i = 0;
	j = nbr;
	if (ft_stop(base) == 1)
		return ;
	while (base[i])
	{
		i++;
	}
	coded = base[j % i];
	if (j < 0)
	{
		ft_putchar('-');
		j = -j;
	}
	if (j >= i)
	{
		ft_putnbr_base(j / i, base);
		ft_putchar(coded);
	}
	else if (j < i)
		ft_putchar(coded);
}
