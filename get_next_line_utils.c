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

size_t	ft_slen(char const *s)
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
    int len;
    int i;
    char *ptr;

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

ssize_t read_data(int fd, char **buffer)
{
    ssize_t bytes_read;
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