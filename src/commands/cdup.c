/*
** EPITECH PROJECT, 2019
** cdup.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "definition.h"

void command_cdup(server_t *server, client_t *client)
{
    char *last = NULL;
    char *temp = NULL;

    (void)server;
    if (!client->logged) {
        dprintf(client->fd, "530 Please login with USER and PASS\r\n");
        return;
    }
    if (strcmp(client->pwd, "/")) {
        last = strtok(client->pwd, "/");
        while ((temp = strtok(NULL, "/")) != NULL)
            last = temp;
        if (client->pwd[strlen(client->pwd) - 1] == '/')
            client->pwd[strlen(client->pwd) - strlen(last) - 1] = 0;
        else
            client->pwd[strlen(client->pwd) - strlen(last)] = 0;
    }
    dprintf(client->fd, "250 Directory successfully changed\r\n");
}
