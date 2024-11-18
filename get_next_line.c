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

int check_newline(char *buffer)
{
    int i;

    i = 0;
    while (buffer[i])
    {
        if (buffer[i] == '\n')
            return (++i);
        i++;
    }
    return (-1);
}

char *allocate_line(char *buffer)
{
    int is_newline;
    int i;
    char *ptr;

    is_newline = check_newline(buffer);
    i = 0;
    if (is_newline != -1)
    {
        ptr = (char *) malloc(is_newline + 1);
        while (i < is_newline)
        {
            ptr[i] = buffer[i];
            i++;
        }
        ptr[i] = '\0';
        return (ptr);
    }
    return (NULL);
}

ssize_t read_data(int fd, char *buffer)
{
    ssize_t bytes_read;

    memset(buffer, 0, BUFFER_SIZE + 1);
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    return (bytes_read);
}

char *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE + 1];
    char *line;
    static char *left_buffer;
    char *temp;
    ssize_t bytes_read;

    bytes_read = read_data(fd, buffer);
    if (bytes_read < 0 || (bytes_read == 0 && !left_buffer))
            return (NULL);
    
    if (left_buffer && bytes_read == 0 && check_newline(left_buffer) == -1)
    {
        line = ft_strdup(left_buffer);
        if (!line)
            return (NULL);
        free(left_buffer);
        left_buffer = NULL;
        return (line);
    }

    if (bytes_read > 0)
    {
        temp = left_buffer;
        left_buffer = ft_strjoin(left_buffer, buffer);
        free(temp);
        temp = NULL;
    }

    if (check_newline(left_buffer) != -1)
    {
        
        line = allocate_line(left_buffer);
        if (!line)
            return (NULL);
        temp = ft_strdup(&left_buffer[ft_slen(line)]);
        if (!temp)
            return (NULL);
        free(left_buffer);
        left_buffer = temp;
        return (line);
    }
    while (check_newline(left_buffer) == -1)
    {
        bytes_read = read_data(fd, buffer);
        if (bytes_read > 0)
        {
            ///
            temp = left_buffer;
            left_buffer = ft_strjoin(left_buffer, buffer);
            free(temp);
            temp = NULL;
            ///
            if (check_newline(left_buffer) != -1)
            {
                line = allocate_line(left_buffer);
                if (!line)
                    return (NULL);
                temp = ft_strdup(&left_buffer[ft_slen(line)]);
                if (!temp)
                    return (NULL);
                free(left_buffer);
                left_buffer = temp;
                return (line);
            }
        }
        if (left_buffer && bytes_read == 0)
        {
            line = ft_strdup(left_buffer);
            if (!line)
                return (NULL);    
            free(left_buffer);
            left_buffer = NULL;
            return (line);
        }
    }

    return (line);
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

    close(fd);
    return (0);
}