#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 6
#endif

#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd);
size_t getline_len(int fd);

# endif