/*
** EPITECH PROJECT, 2019
** commands_lib.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include "definition.h"

static int test_logged(client_t *client)
{
    if (!client->logged) {
        dprintf(client->fd, "530 Please login with USER and PASS\r\n");
        return (1);
    }
    return (0);
}

static int test_data_connected(client_t *client)
{
    if (client->active == 0 && !client->data_server) {
        dprintf(client->fd, "425 Use PORT or PASV first.\r\n");
        return (1);
    } else if (client->active == 1 && !client->data) {
        dprintf(client->fd, "425 Use PORT or PASV first.\r\n");
        return (1);
    }
    return (0);
}

int detect_command_error(client_t *client, int flags)
{
    int error = 0;

    if (flags & LOGGED)
        error += test_logged(client);
    else if (flags & DATA_CONNECTED)
        error += test_data_connected(client);
    return (error == 0 ? 0 : 1);
}
