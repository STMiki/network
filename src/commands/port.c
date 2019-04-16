/*
** EPITECH PROJECT, 2019
** port.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "definition.h"

static int get_port(char *ip)
{
    int port1 = 0;
    int port2 = 0;
    char *temp = strtok(ip, ".");

    for (int i = 0; i < 3; i += 1)
        strtok(NULL, ".");
    if ((temp = strtok(NULL, ".")) == NULL)
        return (0);
    else if ((port1 = atoi(temp)) <= 0)
        return (0);
    if ((temp = strtok(NULL, ".")) == NULL)
        return (0);
    else if ((port2 = atoi(temp)) <= 0)
        return (0);
    return (port1 * 256 + port2);
}

static int check_ip(client_t *client)
{
    char *temp = strtok(NULL, DELIMITER);

    for (int i = 0; temp[i]; i += 1)
        temp[i] = temp[i] == ',' ? '.' : temp[i];
    if (strstr(temp, client->ip) == temp) {
        client->port = get_port(temp);
        return (0);
    }
    dprintf(client->fd, "530 Security: bad ip.\r\n");
    return (1);
}

void command_port(server_t *server, client_t *client)
{
    if (!client->logged) {
        dprintf(client->fd, "530 Please login with USER and PASS\r\n");
        return;
    }
    client->active = 1;
    if (check_ip(client))
        return;
    else if (create_data_connection(server, client))
        return;
    dprintf(client->fd, "200 Server connected successfully.\r\n");
}
