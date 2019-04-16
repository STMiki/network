/*
** EPITECH PROJECT, 2019
** getnextline.c
** File description:
** Simple description
*/

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *getnextline(int fd)
{
    char *result = NULL;
    char character = 0;
    int length = 0;

    if (!(fcntl(fd, F_GETFD) != -1 || errno != EBADF))
        return (NULL);
    while (1) {
        read(fd, &character, 1);
        if (character == 0)
            return (result);
        else if (character == 10)
            return (result == NULL ? malloc(1) : result);
        result = realloc(result, (result == NULL ? 2 : length + 2));
        if (result == NULL)
            return (NULL);
        result[length] = character;
        result[length + 1] = 0;
        length += 1;
    }
}
