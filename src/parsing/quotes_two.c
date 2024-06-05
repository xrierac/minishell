/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:02:56 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/04 17:41:34 by tcampbel         ###   ########.fr       */
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

char	*handle_squote(t_sh *msh, char *ptr)
{
	if (*ptr == '\'')
		msh->buffer[msh->buf_len++] = *ptr++;
	while (*ptr != '\'' && *ptr)
		msh->buffer[msh->buf_len++] = *ptr++;
	if (*ptr == '\'')
		msh->buffer[msh->buf_len++] = *ptr++;
	return (ptr);
}

char	*handle_dquote(t_sh *msh, char *ptr)
{
	if (*ptr == '\"' && *ptr)
		msh->buffer[msh->buf_len++] = *ptr++;
	while (*ptr != '\"' && *ptr)
	{
		if (*ptr == '$' && ft_isspace(*(ptr + 1)) == 0 && *(ptr + 1) != '\0' \
			&& *(ptr + 1) != '\"')
		{
			ptr = deref_var(msh, ptr + 1);
			if (msh->var == NULL && *ptr == '\0')
				break ;
		}
		else
			msh->buffer[msh->buf_len++] = *ptr++;
	}
	if (*ptr == '\"' && *ptr)
		msh->buffer[msh->buf_len++] = *ptr++;
	msh->buffer[msh->buf_len] = '\0';
	return (ptr);
}
