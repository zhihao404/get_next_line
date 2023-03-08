/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhihao <zhihao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:59:48 by zhihao            #+#    #+#             */
/*   Updated: 2023/03/08 14:38:20 by zhihao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*save[FOPEN_MAX];
	char		*line;

	line = NULL;
	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save[fd])
	{
		save[fd] = malloc(sizeof(char) * 1);
		if (!save[fd])
			return (NULL);
		save[fd][0] = '\0';
	}
	save[fd] = read_and_save_file_data(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = extract_line_data(save[fd]);
	save[fd] = extract_second_line_data(save[fd]);
	return (line);
}

char	*read_and_save_file_data(int fd, char *save)
{
	ssize_t	read_byte;
	char	*buffer;
	char	*tmp;

	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0 && !ft_strchr(save, '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			free(save);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		tmp = ft_strjoin(save, buffer);
		free(save);
		save = tmp;
	}
	free(buffer);
	return (save);
}

char	*extract_line_data(char *save)
{
	char		*line;
	size_t		i;

	i = 0;
	if (!save || !*save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, save, i + 1);
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*extract_second_line_data(char *save)
{
	char		*second_line;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	second_line = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!second_line)
		return (NULL);
	i += 1;
	while (save[i])
		second_line[j++] = save[i++];
	second_line[j] = '\0';
	free(save);
	return (second_line);
}
