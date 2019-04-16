/*
** EPITECH PROJECT, 2019
** pass.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "definition.h"

void command_pass(server_t *server, client_t *client)
{
    (void)server;
    if (client->logged) {
        dprintf(client->fd, "230 Already logged in.\r\n");
        return;
    } else if (client->user == NULL) {
        dprintf(client->fd, "503 Login with USER first.\r\n");
        return;
    }
    if (strcmp(client->user, "Anonymous") == 0) {
        client->logged = 1;
        dprintf(client->fd, "230 Login successful.\r\n");
    } else {
        dprintf(client->fd, "530 Login incorrect.\r\n");
    }
}
