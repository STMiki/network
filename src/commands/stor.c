/*
** EPITECH PROJECT, 2019
** stor.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "definition.h"

void receive_data(client_t *client, int file)
{
    char *buffer = NULL;

    while ((buffer = getnextline(client->data)) != NULL) {
        write(file, buffer, strlen(buffer));
        free(buffer);
    }
}

void command_stor(server_t *server, client_t *client)
{
    char *path = NULL;
    int file = 0;

    if (detect_command_error(client, LOGGED | DATA_CONNECTED))
        return;
    path = get_path(client);
    if ((file = open(path, O_CREAT | O_TRUNC | O_WRONLY)) == -1) {
        dprintf(client->data, "550 Permission denied.\r\n");
        return;
    } else if (wait_until_data(client))
        return;
    receive_data(client, file);
    dprintf(client->fd, "226 Download complete.\r\n");
    clear_server(server, client);
}
