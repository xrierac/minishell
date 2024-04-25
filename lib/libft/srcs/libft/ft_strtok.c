/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:54:41 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/16 17:09:32 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	find_delim(const char *s, char *delim, int i)
{
	int	j;

	while (s[i])
	{
		j = 0;
		while (delim[j])
		{
			if (s[i] == delim[j])
				return (delim[j]);
			j++;
		}
		i++;
	}
	return (0);
}


void	count_str(const char *s, char c, char q, t_tok *tok)
{
	size_t	i;

	tok->count = 0;
	i = 0;
	while (s[i])
	{
		q = find_delim(s, tok->delim, i);
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			tok->count++;
			while (s[i] != c && s[i])
			{
				if (s[i] == q && s[i])
				{
					i++;
					while (s[i] != q && s[i])
						i++;
				}
				i++;
			}
		}
	}
}

void	skip_char(const char *s, char q, t_tok *tok)
{
	tok->end++;
	while (s[tok->end] != q && s[tok->end])
		tok->end++;
	tok->end++;
}

char	**malloc_strings(char const *s, char c, char q, t_tok *tok)
{
	while (s[tok->start])
	{
		while (s[tok->start] == c && s[tok->start])
			tok->start++;
		if (s[tok->start] == '\0')
			return (tok->str);
		tok->end = tok->start;
		while (s[tok->end] && s[tok->end] != c)
		{
			if (s[tok->end] == q)
				skip_char(s, q, tok);
			tok->end++;
		}
		tok->len = tok->end - tok->start;
		tok->str[tok->i] = ft_substr(s, tok->start, tok->len);
		tok->start = tok->end;
		q = find_delim(s, tok->delim, tok->end);
		if (tok->str[tok->i++] == '\0')
			return (return_free_array(tok->str));
	}
	return (tok->str);
}

char	**ft_strtok(char const *s, char c, char *skip)
{
	t_tok	tok;
	char	q;

	tok.start = 0;
	tok.end = 0;
	tok.len = 0;
	tok.i = 0;
	tok.delim = skip;
	q = find_delim(s, tok.delim, tok.end);
	count_str(s, c, q, &tok);
	tok.str = ft_calloc(tok.count + 1, sizeof(char *));
	if (!tok.str || !s)
		return (NULL);
	tok.str = malloc_strings(s, c, q, &tok);
	return (tok.str);
}
