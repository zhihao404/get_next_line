/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhihao <zhihao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:03:30 by zhihao            #+#    #+#             */
/*   Updated: 2023/03/07 16:04:28 by zhihao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#include <unistd.h> //read
#include <stdlib.h> //malloc
#include <stdio.h>  //FOPEN_MAX

char	*get_next_line(int fd);
char	*read_and_save_file_data(int fd, char *save);
char	*extract_line_data(char *save);
char	*extract_second_line_data(char *save);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

#endif