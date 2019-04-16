/*
** EPITECH PROJECT, 2019
** cwd.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "definition.h"

static char *create_path(const char *dir, client_t *client)
{
    char *path = NULL;

    path = malloc(sizeof(char) * (strlen(client->pwd) + strlen(dir) + 2));
    strcpy(path, client->pwd);
    if (client->pwd[strlen(client->pwd) - 1] != '/')
        strcat(path, "/");
    strcat(path, dir);
    return (path);
}

void command_cwd(server_t *server, client_t *client)
{
    char *dir = strtok(NULL, DELIMITER);
    char *path = NULL;

    (void)server;
    if (!client->logged) {
        dprintf(client->fd, "530 Please login with USER and PASS\r\n");
        return;
    } else if (dir == NULL) {
        dprintf(client->fd, "550 failed to change directory\r\n");
        return;
    }
    path = create_path(dir, client);
    if (!test_dir(path)) {
        dprintf(client->fd, "550 failed to change directory\r\n");
        return;
    }
    free(client->pwd);
    client->pwd = path;
    dprintf(client->fd, "250 Directory successfully changed\r\n");
}
