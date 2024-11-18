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

    bytes_read = read(fd, buffer, BUFFER_SIZE);
    return (bytes_read);
}

char *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE + 1];
    int is_newline;
    char *line;
    static char *left_buffer;
    char *temp;
    int bytes_read;
    
    bytes_read = read_data(fd, buffer);
    if (bytes_read < 0 || (bytes_read == 0 && left_buffer == NULL))
            return (NULL);
    
    if (left_buffer && bytes_read == 0 && check_newline(left_buffer) == -1)
    {
        line = ft_strdup(left_buffer);
        if (!line)
            return (NULL);
        free(left_buffer);
        return (line);
    }

    if (buffer[0])
        left_buffer = ft_strjoin(left_buffer, buffer);
    // printf("%s\n", left_buffer);
    if (check_newline(left_buffer) != -1)
    {
        // printf("hi\n");
        line = allocate_line(left_buffer);
        if (!line)
            return (NULL);
        temp = ft_strdup(&left_buffer[ft_slen(line)]);
        if (!temp)
            return (NULL);
        free(left_buffer);
        left_buffer = temp;
    }
    while (check_newline(left_buffer) == -1)
    {
        bytes_read = read_data(fd, buffer);
        if (bytes_read > 0)
        {
            left_buffer = ft_strjoin(left_buffer, buffer);
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
        } else
            return (NULL);
    }
    // printf("*   \n");

    return (line);
}



int main()
{
    int fd = open("tst.txt", O_RDONLY);
    
    char *ptr1 = get_next_line(fd);
    char *ptr2 = get_next_line(fd);
    char *ptr3 = get_next_line(fd);
    char *ptr4 = get_next_line(fd);

    printf("[%s]\n", ptr1);
    printf("[%s]\n", ptr2);
    printf("[%s]\n", ptr3);
    printf("[%s]\n", ptr4);

    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    
    close(fd);
    return 0;
}