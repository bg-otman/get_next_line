#include "get_next_line.h"
#include <stdio.h>

size_t getline_len(int fd)
{
    size_t len;
    char c;
    // static int i;

    len = 0;
    while (read(fd, &c, 1) > 0)
    {
        len++;
        if (c == '\n')
            break ;
    }
    return (len);
}