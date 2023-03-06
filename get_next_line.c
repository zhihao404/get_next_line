/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhihao <zhihao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:07:44 by zhihao            #+#    #+#             */
/*   Updated: 2023/03/06 22:44:55 by zhihao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save)//saveがNULLの場合にmallocする
	{
		save = malloc(sizeof(char) * 1);
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	save = read_file(fd, save);
	if (!save)//read_byteが-1の時にNULLが帰ってきているのをここで判定している
		return (NULL);
	line = get_line(save);
	save = get_line2(save);
	return (line);
}

char	*read_file(int fd, char *save)
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

char	*get_line(char *save)
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

char	*get_line2(char *save)
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


// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*prt;
// 	fd = open("test.txt", O_RDONLY);
// 	// prt = get_next_line(fd);
// 	// printf("\nFunc Return: %s\n", prt);
// 	// free(prt);
// 	// prt = get_next_line(fd);
// 	// printf("\nFunc Return: %s\n", prt);
// 	// free(prt);
// 	printf("\nFunc Return: %s\n", get_next_line(fd));
// 	printf("\nFunc Return: %s\n", get_next_line(fd));
// 	printf("\nFunc Return: %s\n", get_next_line(fd));
// 	close(fd);
// }

