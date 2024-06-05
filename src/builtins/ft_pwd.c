/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:19 by xriera-c          #+#    #+#             */
/*   Updated: 2024/06/05 15:11:00 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	*ptr;
	char	*buf;

	buf = (char *)malloc(MAX_ARGS);
	if (!buf)
		return (generic_error("", "pwd"));
	ptr = getcwd(buf, MAX_ARGS);
	if (!ptr)
		return (generic_error("", "pwd"));
	printf("%s\n", ptr);
	free(ptr);
	return (0);
}
