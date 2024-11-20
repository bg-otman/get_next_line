/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:25:49 by obouizi           #+#    #+#             */
/*   Updated: 2024/11/20 15:25:57 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_slen(char const *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*get_last_line(char **buffer, ssize_t bytes_read);
char	*allocate_line(char *buffer);
int		check_newline(char *buffer);
ssize_t	read_data(int fd, char **buffer);
char	*allocate_and_free(char **buffer);

#endif
