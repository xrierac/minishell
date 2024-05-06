/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:19 by xriera-c          #+#    #+#             */
/*   Updated: 2024/05/06 12:11:20 by xriera-c         ###   ########.fr       */
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
		return (0);
	ptr = getcwd(buf, size);
	printf("%s\n", ptr);
	free(ptr);
	return (0);
}
