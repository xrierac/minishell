/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:52:19 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/09 15:59:19 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(void)
{
	size_t size;
	char *ptr;
	char *buf;

	size = 2000;
	buf = (char *)malloc(size);
	if (!buf)
		return ;
	ptr = getcwd(buf, size);
	printf("%s\n", ptr);
	free(ptr);
}
