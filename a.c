#include "get_next_line.h"
#include <stdio.h>

char    *read_file(int fd, char **save)
{
    int     read_byte;
    char    *buffer;
    char    *tmp;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    read_byte = 1;//read_byteが0になるまでwhileに入る
    while (read_byte > 0 && !ft_strchr(*save, '\n'))//strchrは文字列に'\n'がない場合NULLを返す
    {
        read_byte = read(fd, buffer, BUFFER_SIZE);//read_byteが0になるとwhileから抜ける //read関数は読み込んだバイト数を返す
        if (read_byte == -1)
        {
            free(buffer);
            free(*save);
            return (NULL);
        }
        buffer[read_byte] = '\0';//bufferの最後に'\0'を入れる
        tmp = ft_strjoin(*save, buffer);
        free(*save);//saveはmallocしてるけどtmpはmallocしてないからここでfreeする
        *save = tmp;
    }
    free(buffer);
    return (*save);
}

char    *get_line(char **save)
{
    char    *line;
    int     i;

    i = 0;
    if (!*save)
        return (NULL);
    while ((*save)[i] && (*save)[i] != '\n')
        i++;
    // printf("%d",i);
    line = malloc(sizeof(char) * (i + 2));//'\0'と'\n'の分を確保
    if (!line)
        return (NULL);
    ft_strlcpy(line, *save, i + 1);//'\0'を入れる //i+1は'\0'の分
    if ((*save)[i] == '\n')//'\n'がある場合
        line[i++] = '\n';//'\n'を入れる //i++ではなくi+1だと'\0'の分を入れてしまう
    line[i] = '\0';
    return (line);
}

char    *get_line2(char **save)
{
    char    *second_line;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while ((*save)[i] && (*save)[i] != '\n')
        i++;
    if (!(*save)[i])
    {
        free(*save);
        return (NULL);
    }
    second_line = malloc(sizeof(char) * (ft_strlen(*save) - i + 1));//'\0'の分を確保 //ft_strlenは'\0'を含まない
    if (!second_line)
        return (NULL);
    i++; //i += 2;でもいい
    while ((*save)[i])
        second_line[j++] = (*save)[i++];
    second_line[j] = '\0';
    free(*save);
    *save = second_line;
    return (*save);
}

char    *get_next_line(int fd)
{
    static char *save;
    char        *line;

    line = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!save)//saveがNULLの場合にmallocする
}