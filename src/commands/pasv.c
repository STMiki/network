/*
** EPITECH PROJECT, 2019
** pasv.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include "definition.h"

void command_pasv(server_t *server, client_t *client)
{
    if (!client->logged) {
        dprintf(client->fd, "530 Please login with USER and PASS\r\n");
        return;
    }
    client->active = 0;
    if (create_data_connection(server, client))
        return;
    dprintf(client->fd, "227 Entering Passive Mode ");
    dprintf(client->fd, "(%s,%d,", server->ip, client->port / 256);
    dprintf(client->fd, "%d).\r\n", client->port % 256);
}
