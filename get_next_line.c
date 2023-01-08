/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhihao <zhihao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:07:44 by zhihao            #+#    #+#             */
/*   Updated: 2022/12/22 19:45:48 by zhihao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *save)
{
	int		read_byte;
	char	*buffer
	char	*tmp;
	
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0 && strchr(save, '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			free(save);
			return(NULL);
		}
		buffer[read_byte] = '\0';
		tmp = ft_strjoin(save, buffer);
		free(save);
		save = tmp;
	} 
	free(buffer);
	return (save);
}

char *get_next_line(int fd)
{
	static char	*save;
	char		*line;
	
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save)
	{
		if (!(save = malloc(sizeof(char))))
			return (NULL);
		save[0] = '\0';
	}
	save = read_file(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = get_line2(save);
	return (line);
}