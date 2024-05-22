/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:19 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/14 16:34:37 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	size_t size;
	char *ptr;
	char *buf;

	size = 2000;
	buf = (char *)malloc(size);
	if (!buf)
		return (generic_error("", "pwd"));
	ptr = getcwd(buf, size);
	if (!ptr)
		return (generic_error("", "pwd"));
	printf("%s\n", ptr);
	free(ptr);
	return (0);
}
