/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:47:46 by tcampbel          #+#    #+#             */
/*   Updated: 2024/01/11 10:45:17 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

char	*find_line(char *storage)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] != '\n' && storage[i])
		i++;
	if (storage[i] == '\n')
		i++;
	new_line = ft_substr(storage, 0, i);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*find_end(char *storage)
{
	int		i;
	char	*end_line;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	end_line = ft_substr(storage, i, (ft_strlen(storage) - i));
	if (!end_line)
		return (ft_free(&storage));
	ft_free(&storage);
	return (end_line);
}

char	*read_line(int fd, char *storage)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(&storage));
		buffer[bytes_read] = '\0';
		if (!storage)
			storage = ft_strdup(buffer);
		else
			storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (ft_free(&storage));
		if (ft_strchr(storage, '\n'))
			break ;
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_strchr(storage, '\n'))
		storage = read_line(fd, storage);
	if (!storage)
		return (NULL);
	line = find_line(storage);
	if (!line)
		return (ft_free(&storage));
	storage = find_end(storage);
	return (line);
}
