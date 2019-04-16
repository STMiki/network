/*
** EPITECH PROJECT, 2019
** dele.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "definition.h"

void command_dele(server_t *server, client_t *client)
{
    char *path = NULL;

    (void)server;
    if (detect_command_error(client, LOGGED))
        return;
    path = get_path(client);
    if (strcmp(client->pwd, path) == 0) {
        dprintf(client->fd, "501 Not enough arguments.\r\n");
        return;
    }
    if (unlink(path) == -1) {
        dprintf(client->fd, "550 The file does't exist or is a directory.\r\n");
        return;
    }
    dprintf(client->fd, "250 File deleted successfully.\r\n");
}
