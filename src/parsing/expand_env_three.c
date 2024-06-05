/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:28:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/05 11:29:03 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redirect_check(char *ptr)
{
	char	*str;

	str = ptr;
	if ((*str == '>' && *(str + 1) == '>')
		|| (*str == '<' && *(str + 1) == '<'))
		return (1);
	else if ((*str == '>' && *(str + 1) != '>')
		|| (*str == '<' && *(str + 1) != '<'))
		return (1);
	return (0);
}


char	*cpy_og_var(t_sh *msh, char *ptr, int hd_flag)
{
	if (*ptr == '$' && *ptr)
		msh->buffer[msh->buf_len++] = *ptr++;
	if (hd_flag == 0)
		ft_printf(2, RED":("END " $");
	while (*ptr && *ptr != '$' && ((ft_isalnum(*ptr) == 1) || *ptr == '_'))
	{
		if (hd_flag == 0)
			ft_putchar_fd(*ptr, 2);
		msh->buffer[msh->buf_len++] = *ptr++;
	}
	if (hd_flag == 0)
		ft_printf(2, ": ambiguous redirect\n");
	return (ptr);
}

char	*amb_redirect_check(t_sh *msh, char *ptr)
{
	char	*str;
	int		hd_flag;

	msh->flag = 0;
	hd_flag = 0;
	if (*ptr == '<' && *(ptr + 1) == '<')
		hd_flag = 1;
	while ((*ptr == '<' || *ptr == '>' || ft_isspace(*ptr)) && *ptr)
		msh->buffer[msh->buf_len++] = *ptr++;
	str = ptr;
	if (*ptr == '$' && ft_isspace(*(ptr + 1)) == 0 && *(ptr + 1) != '\0')
	{
		ptr = deref_var(msh, ptr + 1);
		if (msh->flag == 1)
			ptr = cpy_og_var(msh, str, hd_flag);
	}
	return (ptr);
}