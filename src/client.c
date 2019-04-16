/*
** EPITECH PROJECT, 2019
** client.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "definition.h"

void add_client(int client, client_t list[], const char *home,
                struct sockaddr_in from)
{
    char address[INET_ADDRSTRLEN];

    for (int i = 0; i < MAX_CLIENT; i += 1) {
        if (list[i].connected == 0) {
            inet_ntop(AF_INET, &from.sin_addr.s_addr, address, INET_ADDRSTRLEN);
            list[i].connected = 1;
            list[i].logged = 0;
            list[i].data = 0;
            list[i].data_server = 0;
            list[i].active = 0;
            list[i].port = 0;
            list[i].fd = client;
            list[i].user = NULL;
            list[i].home = strdup(home);
            list[i].pwd = strdup(home);
            list[i].ip = strdup(address);
            printf("New connection from %s\n", address);
            return;
        }
    }
}

void clean_client(server_t *server, client_t *client)
{
    if (client->connected == 0)
        return;
    close(client->fd);
    FD_CLR(client->fd, &server->main);
    if (client->data) {
        close(client->data);
        FD_CLR(client->data, &server->main);
    }
    if (client->data_server) {
        close(client->data_server);
        FD_CLR(client->data_server, &server->main);
    }
    free(client->home);
    free(client->user);
    free(client->pwd);
    free(client->ip);
    bzero(client, sizeof(client_t));
}
