/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:05 by tcampbel          #+#    #+#             */
/*   Updated: 2024/06/04 18:37:22 by tcampbel         ###   ########.fr       */
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


char	*cpy_og_var(t_sh *msh, char *ptr)
{
	if (*ptr == '$' && *ptr)
		msh->buffer[msh->buf_len++] = *ptr++;
	ft_printf(2, RED":("END " $");
	while (*ptr && *ptr != '$' && ((ft_isalnum(*ptr) == 1) || *ptr == '_'))
	{
		ft_putchar_fd(*ptr, 2);
		msh->buffer[msh->buf_len++] = *ptr++;
	}
	ft_printf(2, ": ambiguous redirect\n");
	return (ptr);
}

char	*amb_redirect_check(t_sh *msh, char *ptr)
{
	char	*str;

	msh->flag = 0;
	while ((*ptr == '<' || *ptr == '>' || ft_isspace(*ptr)) && *ptr)
		msh->buffer[msh->buf_len++] = *ptr++;
	str = ptr;
	if (*ptr == '$' && ft_isspace(*(ptr + 1)) == 0 && *(ptr + 1) != '\0')
	{
		ptr = deref_var(msh, ptr + 1);
		if (msh->flag == 1)
			ptr = cpy_og_var(msh, str);
	}
	return (ptr);
}

void	handle_expansion(t_sh *msh, char *cmd)
{
	char	*ptr;

	ptr = cmd;
	while (*ptr)
	{
		if (*ptr == '\'')
			ptr = handle_squote(msh, ptr);
		else if (*ptr == '\"')
			ptr = handle_dquote(msh, ptr);
		else if (redirect_check(ptr))
			ptr = amb_redirect_check(msh, ptr);
		else if (*ptr == '$' && ft_isspace(*(ptr + 1)) == 0 \
					&& *(ptr + 1) != '\0' && *(ptr + 1) != '$')
		{
			ptr = deref_var(msh, ptr + 1);
			if (msh->var == NULL && *ptr == '\0')
				break ;
		}
		else
			msh->buffer[msh->buf_len++] = *ptr++;
	}
	msh->buffer[msh->buf_len] = '\0';
}
char	*env_var_type_check(char *ptr)
{
	if (*ptr == '?' || ft_isdigit(*ptr) == 1)
		ptr++;
	else
		while (*ptr && *ptr != '$' && ((ft_isalnum(*ptr) == 1) || *ptr == '_'))
			ptr++;
	return (ptr);
}

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

