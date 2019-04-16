/*
** EPITECH PROJECT, 2019
** noop.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include "definition.h"

void command_noop(server_t *server, client_t *client)
{
    (void)server;
    if (!client->logged) {
        dprintf(client->fd, "530 Please login with USER and PASS\r\n");
        return;
    }
    dprintf(client->fd, "200 NOOP ok\r\n");
}
