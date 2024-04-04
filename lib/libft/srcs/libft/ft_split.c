/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:05:00 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/15 18:13:03 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_str(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
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

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	start = 0;
	result = ft_calloc((count_str(s, c) + 1), sizeof(char *));
	if (!result || !s)
		return (NULL);
	while (s[start])
	{
		while (s[start] == c && s[start])
			start++;
		if (s[start] == '\0')
			return (result);
		end = start;
		while (s[end] != c && s[end])
			end++;
		result[i] = ft_substr(s, start, end - start);
		start = end;
		if (result[i++] == '\0')
			return (free_str(result));
	}
	return (result);
}
