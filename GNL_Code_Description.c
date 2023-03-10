/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GNL_Code_Description.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhihao <zhihao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:07:44 by zhihao            #+#    #+#             */
/*   Updated: 2023/03/10 13:37:44 by zhihao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	line = NULL;//NULLはポインタ型の変数に代入するときに使う
	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)//FOPEN_MAXはファイルディスクリプタの最大値
		return (NULL);
	if (!save)//saveがNULLの場合にmallocする
	{
		save = malloc(sizeof(char) * 1);//1だけmallocしているのは、ft_strjoinのため
		if (!save)
			return (NULL);
		save[0] = '\0';//終端文字を入れているのは、ft_strjoinのため
	}
	save = read_and_save_file_data(fd, save);
	if (!save)//read_byteが-1の時にNULLが帰ってきているのをここで判定している
		return (NULL);
	line = extract_line_data(save);
	save = extract_second_line_data(save);
	return (line);
}

char	*read_and_save_file_data(int fd, char *save)//関数ポインターにしないと参照先の関数を呼び出すことができない。この場合だとmain関数でこの関数を呼び出したとしても、ft_strjoinをmain関数で呼び出すことができない
{
	ssize_t	read_byte;//ssize_t型はint型と同じサイズの符号付き整数型,int型にしていない理由は、read関数の返り値がssize_t型だから
	char	*buffer;//読み出したデータを格納するバッファの先頭アドレスを指すポインタ
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
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
		tmp = ft_strjoin(save, buffer);//直接saveにft_strjoin(save, buffer)の結果を代入すると、saveがft_strjoin()で動的に割り当てられたメモリ領域を参照しなくなり、メモリリークが発生する。そこで、一時変数tmpを用意し、ft_strjoin(save, buffer)の結果をtmpに代入してから、saveをtmpで上書きすることで、動的に割り当てられたメモリ領域を解放しながら、saveに新しいデータを連結している。要はメモリリークを回避している。
		
		// また、saveを直接変更すると、後でsaveの元の内容が必要になる場合に問題が発生する可能性がある。だから一時変数tmpを使って新しい文字列を作成し、最後にsaveに代入することで、元のsaveの内容が保持されるようになっている。
		free(save);//saveはmallocしてるけどtmpはmallocしてないからここでfreeする
		save = tmp;
	}
	free(buffer);
	return (save);
}

char	*extract_line_data(char *save)//関数ポインターにしないと参照先の関数を呼び出すことができない。この場合だとmain関数でこの関数を呼び出したとしても、ft_strlcpyをmain関数で呼び出すことができない
{
	char		*line;
	size_t		i;//int型ではなくsize_t型にしている理由は、iが負の値になることがないから→安全

	i = 0;
	if (!save || !*save)//*saveはsave[0]のこと	←超重要　//!*saveの条件がないと、saveがNULLの場合に、lineがNULLでない値を返してしまう
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));//'\0'と'\n'の分を確保
	if (!line)
		return (NULL);
	ft_strlcpy(line, save, i + 1);//'\0'を入れる //i+1は'\0'の分
	if (save[i] == '\n')//'\n'がある場合
		line[i++] = '\n';//'\n'を入れる
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
	if (!save[i])//'\n'がない場合
	{
		free(save);//ここでsaveをfreeしないと、次の行でsaveをmallocしても、freeされていないsaveのメモリ領域を参照してしまう
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


#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*prt;
	fd = open("test.txt", O_RDONLY);
	// prt = get_next_line(fd);
	// printf("\nFunc Return: %s\n", prt);
	// free(prt);
	// prt = get_next_line(fd);
	// printf("\nFunc Return: %s\n", prt);
	// free(prt);
	printf("\nFunc Return: %s\n", get_next_line(fd));
	printf("\nFunc Return: %s\n", get_next_line(fd));
	printf("\nFunc Return: %s\n", get_next_line(fd));
	close(fd);
}

