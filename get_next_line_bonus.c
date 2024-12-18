/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:21:31 by obouizi           #+#    #+#             */
/*   Updated: 2024/11/21 17:36:16 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (bytes_read <= 0)
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

char	*get_last_line(char **buffer, ssize_t bytes_read)
{
	char	*line;

	if (bytes_read == -1)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
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
	static char	*buffer[OPEN_MAX];
	char		*ptr;
	char		*temp;
	ssize_t		byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (!buffer[fd])
	{
		if (read_data(fd, &buffer[fd]) <= 0)
			return (NULL);
	}
	while (check_newline(buffer[fd]) == -1)
	{
		byte_read = read_data(fd, &temp);
		if (byte_read <= 0)
			return (get_last_line(&buffer[fd], byte_read));
		ptr = ft_strjoin(buffer[fd], temp);
		free(buffer[fd]);
		free(temp);
		if (!ptr)
			return (NULL);
		buffer[fd] = ptr;
	}
	return (allocate_and_free(&buffer[fd]));
}
