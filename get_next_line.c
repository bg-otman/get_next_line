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

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*ptr_dst;
	const unsigned char		*ptr_src;
	size_t					i;

	ptr_dst = dst;
	ptr_src = src;
	i = 0;
	if (ptr_dst == ptr_src || n == 0)
		return (dst);
	while (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	return (dst);
}

static size_t	ft_slen(char const *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;
    
	s1_len = ft_slen(s1);
    s2_len = ft_slen(s2);
	ptr = (char *) malloc((s1_len + s2_len) + 1);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, s1_len);
	ft_memcpy(ptr + s1_len, s2, s2_len);
	ptr[s1_len + s2_len] = '\0';
	return (ptr);
}

/// ////////////////
int get_len(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (++i);
        i++;
    }
    return (i);
}
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

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;
    size_t s_len;

	i = 0;
    s_len = strlen(s1);
	ptr = (char *) malloc(s_len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < s_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[s_len] = '\0';
	return (ptr);
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
    static char buffer[BUFFER_SIZE + 1];
    static ssize_t bytes_read;
    static ssize_t i;
    int is_newline;
    char *ptr;
    char *temp;
    int j;

    if (i >= bytes_read)
    {
        bytes_read = read_data(fd, buffer);
        // i = 0;
        if (bytes_read <= 0)
            return (NULL);
        buffer[BUFFER_SIZE] = '\0';
    }
    ptr = buffer;
    while (check_newline(ptr) == -1)
    {
        temp = ft_strdup(ptr);
        if (!temp)
            return (NULL);
        if (read_data(fd, buffer) > 0)
        {
            ptr = buffer;
            ptr = ft_strjoin(temp, ptr);
            if (!ptr)
                return (NULL);
        }
        else
            return (NULL);
        free(temp);
    }

    return (ptr);
}



int main()
{
    int fd = open("tst.txt", O_RDONLY);
    
    printf("[%s]\n", get_next_line(fd));
    // printf("[%s]\n", get_next_line(fd));
    // printf("[%s]\n", get_next_line(fd));
    // printf("[%s]", get_next_line(fd));

    // printf("%s", read_data(fd));
    
    close(fd);
    return 0;
}