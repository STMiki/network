/*
** EPITECH PROJECT, 2019
** help.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include "definition.h"

void command_help(server_t *server, client_t *client)
{
    (void)server;
    if (!client->logged) {
        dprintf(client->fd, "530 Please login with USER and PASS\r\n");
        return;
    }
    dprintf(client->fd, "214-The following commands are recognized.\r\n");
    dprintf(client->fd, " CDUP CWD  DELE HELP LIST");
    dprintf(client->fd, " NOOP PASS PASV PORT PWD  QUIT RETR");
    dprintf(client->fd, " STOR USER\r\n");
    dprintf(client->fd, "214 Help OK.\r\n");
}
