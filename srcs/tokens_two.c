/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:44:06 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/12 15:05:22 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*redirect_in(t_sh *msh, char *input)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_substr(input, i, 1);
	return (temp);
}
