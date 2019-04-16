/*
** EPITECH PROJECT, 2019
** user.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "definition.h"

void command_user(server_t *server, client_t *client)
{
    char *user = NULL;

    (void)server;
    if (client->logged) {
        dprintf(client->fd, "530 can't change from guest user\r\n");
        return;
    } else if ((user = strtok(NULL, DELIMITER)) == NULL) {
        dprintf(client->fd, "530 Permission denied.\r\n");
        return;
    }
    if (client->user)
        free(client->user);
    client->user = strdup(user);
    dprintf(client->fd, "331 Please specify the password.\r\n");
}
