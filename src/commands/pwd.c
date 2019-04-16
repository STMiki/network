/*
** EPITECH PROJECT, 2019
** pwd.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include "definition.h"

void command_pwd(server_t *server, client_t *client)
{
    (void)server;
    if (!client->logged) {
        dprintf(client->fd, "530 Please login with USER and PASS\r\n");
        return;
    }
    dprintf(client->fd, "257 \"%s\"\r\n", client->pwd);
}
