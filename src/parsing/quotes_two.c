/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:02:56 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/22 16:03:37 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_quote_ptr(char *str, char q)
{
	str++;
	while (*str != q && *str)
		str++;
	return (str + 1);
}

int	skip_quotes(char *str, int i)
{
	if (str[i] == '\'' || str[i] == '\"')
		i = find_quote(str, str[i], i + 1);
	return (i);
}