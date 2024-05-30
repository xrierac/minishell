/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:05 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/30 17:08:09 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*fetch_exit_code(t_sh *msh, char *ptr)
{
	char	*exit_code;

	msh->exit_code_flag = 1;
	exit_code = ft_itoa(msh->exit_code);
	if (!exit_code)
	{
		free(ptr);
		exit_error(msh, "malloc", 1);
	}
	return (exit_code);
}
