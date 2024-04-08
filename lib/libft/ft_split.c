/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:10:16 by xriera-c          #+#    #+#             */
/*   Updated: 2023/11/06 08:35:30 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number_words(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0)
		{
			i++;
			j++;
		}
		if (*s == c && j != 0)
			j = 0;
		s++;
	}
	return (i);
}

static char	**free_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

static char	*get_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (ft_substr(s, 0, i));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		j;

	if (!s)
		return (0);
	arr = malloc(sizeof(char *) * (get_number_words(s, c) + 1));
	if (!arr)
		return (0);
	j = -1;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			arr[++j] = get_word(s, c);
			if (arr[j] == 0)
				return (free_memory(arr));
			s = s + ft_strlen(arr[j]);
		}
	}
	arr[++j] = 0;
	return (arr);
}
