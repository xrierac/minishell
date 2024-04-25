/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:05:00 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/21 11:44:27 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_str(const char *s, char c, char q)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == q && s[i])
		{
			count++;
			i++;
			while (s[i] != q && s[i])
				i++;
			i++;
		}
		else if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static char	**free_str(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

void	skip_char(const char *s, char q, t_split *split)
{
	split->start++;
	while (s[split->end] == q && s[split->end])
		split->end++;
	while (s[split->end] != q && s[split->end])
		split->end++;
	split->len = split->end - split->start;
}

char	**malloc_strings(char const *s, char c, char q, t_split *split)
{
	while (s[split->start])
	{
		while (s[split->start] == c && s[split->start])
			split->start++;
		if (s[split->start] == '\0')
			return (split->str);
		split->end = split->start;
		if (s[split->start] == q)
		{
			skip_char(s, q, split);
			split->str[split->i] = ft_substr(s, split->start, split->len);
			split->end++;
		}
		else
		{
			while (s[split->end] && s[split->end] != c)
				split->end++;
			split->len = split->end - split->start;
			split->str[split->i] = ft_substr(s, split->start, split->len);
		}
		split->start = split->end;
		if (split->str[split->i++] == '\0')
			return (free_str(split->str));
	}
	return (split->str);
}

char	**ft_skip_split(char const *s, char c, char q)
{
	t_split	split;

	split.start = 0;
	split.end = 0;
	split.len = 0;
	split.i = 0;
	split.str = ft_calloc((count_str(s, c, q) + 1), sizeof(char *));
	if (!split.str || !s)
		return (NULL);
	split.str = malloc_strings(s, c, q, &split);
	return (split.str);
}
