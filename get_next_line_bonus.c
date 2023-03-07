/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhihao <zhihao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:59:48 by zhihao            #+#    #+#             */
/*   Updated: 2023/03/07 16:03:35 by zhihao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*save[FOPEN_MAX];//OPEN_MAXでなくFOPEN_MAXを使うべき、対応していない環境linuxがあるから
	char		*line;

	line = NULL;
	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)//fd > FOPEN_MAX
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

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));//1をsize_t型にキャストしているのは、BUFFER_SIZEがunsigned int型だから
	if (!buffer)
	return (NULL);
	read_byte = 1;//read_byteが0になるまでwhileに入る
	while (read_byte > 0 && !ft_strchr(save, '\n'))//strchrは文字列に'\n'がない場合NULLを返す
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);//read_byteが0になるとwhileから抜ける //read関数は読み込んだバイト数を返す
		if (read_byte == -1)
		{
			free(buffer);
			free(save);
			return (NULL);
		}
		buffer[read_byte] = '\0';//bufferの最後に'\0'を入れる
		tmp = ft_strjoin(save, buffer);
		free(save);//saveはmallocしてるけどtmpはmallocしてないからここでfreeする
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
	if (!save || !*save)//*saveはsave[0]のこと	←超重要
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	// printf("%d",i);
	line = malloc(sizeof(char) * (i + 2));//'\0'と'\n'の分を確保
	if (!line)
		return (NULL);
	ft_strlcpy(line, save, i + 1);//'\0'を入れる //i+1は'\0'の分
	if (save[i] == '\n')//'\n'がある場合
		line[i++] = '\n';//'\n'を入れる //i++ではなくi+1だと'\0'の分を入れてしまう
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
	second_line = malloc(sizeof(char) * (ft_strlen(save) - i + 1));//'\0'の分を確保 //ft_strlenは'\0'を含まない
	if (!second_line)
		return (NULL);
	i += 1;//'\n'の次の文字からコピーする
	while (save[i])
		second_line[j++] = save[i++];
	second_line[j] = '\0';
	free(save);
	return (second_line);
}