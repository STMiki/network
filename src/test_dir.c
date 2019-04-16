/*
** EPITECH PROJECT, 2019
** test_dir.c
** File description:
** Simple description
*/

#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int test_dir(const char *path)
{
    DIR *directory = NULL;

    if (path == NULL)
        return (0);
    if ((directory = opendir(path))) {
        closedir(directory);
        return (1);
    } else if (ENOENT == errno)
        return (0);
    else {
        perror("opendir");
        return (0);
    }
}
