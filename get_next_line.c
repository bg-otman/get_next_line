/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:59:24 by obouizi           #+#    #+#             */
/*   Updated: 2024/11/19 15:43:33 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*allocate_line(char *buffer)
{
	int		len;
	int		i;
	char	*ptr;

	if (!buffer)
		return (NULL);
	len = check_newline(buffer);
	if (len == -1)
		len = ft_slen(buffer);
	i = 0;
	ptr = (char *) malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = buffer[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

ssize_t	read_data(int fd, char **buffer)
{
	ssize_t	bytes_read;

	*buffer = (char *) malloc(BUFFER_SIZE + 1);
	if (!*buffer)
		return (-1);
	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(*buffer);
		*buffer = NULL;
		return (bytes_read);
	}
	(*buffer)[bytes_read] = '\0';
	return (bytes_read);
}

char	*allocate_and_free(char **buffer)
{
	char	*line;
	char	*temp;

	if (!buffer || !*buffer)
		return (NULL);
	line = allocate_line(*buffer);
	if (!line)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	temp = ft_strdup(&(*buffer)[ft_slen(line)]);
	if (!temp)
	{
		free(line);
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*get_last_line(char **buffer)
{
	char	*line;

	if (*buffer && **buffer)
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (line);
	}
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*ptr;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		if (read_data(fd, &buffer) <= 0)
			return (NULL);
	}
	while (check_newline(buffer) == -1)
	{
		if (read_data(fd, &temp) <= 0)
			return (get_last_line(&buffer));
		ptr = ft_strjoin(buffer, temp);
		free(buffer);
		free(temp);
		if (!ptr)
			return (NULL);
		buffer = ptr;
	}
	return (allocate_and_free(&buffer));
}
