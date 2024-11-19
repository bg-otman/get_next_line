/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:59:24 by obouizi           #+#    #+#             */
/*   Updated: 2024/11/10 20:59:46 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *allocate_and_free(char **buffer)
{
    char *line;
    char *temp;

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

char *get_last_line(char **buffer)
{
    char *line;

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

char *get_next_line(int fd)
{
    static char *buffer;
    char *ptr;
    char *temp;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!buffer)
    {
        bytes_read = read_data(fd, &buffer);
        if (bytes_read <= 0)
            return (NULL);
    }
    while (check_newline(buffer) == -1)
    {
        bytes_read = read_data(fd, &temp);
        if (bytes_read <= 0)
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

int main(void)
{
    int fd = open("tst.txt", O_RDONLY);
    char *line;

    if (fd == -1)
    {
        printf("Error opening file");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    printf("|%s|", get_next_line(fd));

    close(fd);
    return (0);
}