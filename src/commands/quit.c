/*
** EPITECH PROJECT, 2019
** quit.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include "definition.h"

void command_quit(server_t *server, client_t *client)
{
    printf("Connection ended for %s\n", client->ip);
    dprintf(client->fd, "221 Goodbye.\r\n");
    clean_client(server, client);
}
