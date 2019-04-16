/*
** EPITECH PROJECT, 2019
** retr.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "definition.h"

static char *get_data(const char *path)
{
    int fd = open(path, O_RDONLY);
    char *buffer = NULL;
    char *result = NULL;

    if (fd == -1)
        return (NULL);
    result = malloc(1);
    result[0] = 0;
    while ((buffer = getnextline(fd)) != NULL) {
        result = realloc(result, strlen(buffer) + strlen(result) + 1);
        strcat(result, buffer);
        free(buffer);
    }
    return (result);
}

static char *get_file(char *path)
{
    char *last = strtok(path, "/");
    char *temp = NULL;

    while ((temp = strtok(NULL, "/")) != NULL)
        last = temp;
    return (last);
}

static void send_file_data(client_t *client, char *path, char *data)
{
    dprintf(client->fd, "150 Opening ASCII mode data connection for ");
    dprintf(client->fd, "%s (%ld bytes).\r\n", get_file(path), strlen(data));
    write(client->data, data, strlen(data));
    dprintf(client->fd, "226 Transfer complete.\r\n");
}

void command_retr(server_t *server, client_t *client)
{
    char *path = NULL;
    char *data = NULL;

    if (detect_command_error(client, LOGGED | DATA_CONNECTED))
        return;
    path = get_path(client);
    if ((data = get_data(path)) == NULL) {
        dprintf(client->fd, "550 Failled to open file.\r\n");
        return;
    } else if (wait_until_data(client))
        return;
    send_file_data(client, path, data);
    clear_server(server, client);
}
