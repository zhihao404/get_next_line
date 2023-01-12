/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhihao <zhihao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:07:44 by zhihao            #+#    #+#             */
/*   Updated: 2023/01/10 20:56:06 by zhihao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *save)
{
	int		read_byte;
	char	*buffer;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0 && strchr(save, '\n'))//文字列に'\n'がない場合whileに入る
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
		free(save);//saveはmallocしてるけどtmpはmallocしてないからここでfreeする
		save = tmp;
	}
	free(buffer);
	return (save);
}

char	*get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, save, i + 1);
	if (save[i] == '\n')
		line[i + 1] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_line2(char *save)
{
	char	*second_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
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
	return (second_line);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save)
	{
		save = malloc(sizeof(char) * 1);
		if (!save)
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
