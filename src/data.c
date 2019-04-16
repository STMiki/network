/*
** EPITECH PROJECT, 2019
** data.c
** File description:
** Simple description
*/

#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include "definition.h"

void clear_server(server_t *server, client_t *client)
{
    if (client->data) {
        close(client->data);
        FD_CLR(client->data, &server->main);
        client->data = 0;
    }
    if (client->data_server) {
        close(client->data_server);
        FD_CLR(client->data_server, &server->main);
        client->data_server = 0;
    }
}

void init_server(server_t *server, client_t *client)
{
    int port1 = 0;
    int port2 = 0;
    int port = 0;
    int server_fd = 0;

    do {
        while (port >= 10000 || port <= 0) {
            port1 = my_random(0, 257);
            port2 = my_random(0, 257);
            port = port1 * 256 + port2;
        }
    } while ((server_fd = init(port, 1)) < 0);
    client->port = port;
    client->data_server = server_fd;
    FD_SET(server_fd, &server->main);
    server->maxfd = server->maxfd > server_fd ? server->maxfd : server_fd;
}

int init_client(const char *ip, int port)
{
    int client = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;

    if (client == -1) {
        perror("socket client error");
        return (-1);
    }
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (connect(client, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Connection failled to data socket");
        return (-1);
    }
    return (client);
}

int create_data_connection(server_t *server, client_t *client)
{
    clear_server(server, client);
    if (client->active) {
        if (!client->port) {
            dprintf(client->fd, "425 Connection set active but no port\r\n");
            return (1);
        }
        if ((client->data = init_client(client->ip, client->port)) == -1) {
            dprintf(client->fd, "425 Can't connect to client\r\n");
            return (1);
        }
    } else
        init_server(server, client);
    return (0);
}

void handle_data_connection(client_t *client)
{
    int data = 0;
    struct sockaddr_in from;
    char address[INET_ADDRSTRLEN];
    socklen_t length = sizeof(from);

    data = accept(client->data_server, (struct sockaddr*) &from, &length);
    if (data > 0) {
        inet_ntop(AF_INET, &from.sin_addr.s_addr, address, INET_ADDRSTRLEN);
        if (strcmp(address, client->ip)) {
            dprintf(client->fd, "425 Security: bad ip connecting\r\n");
            close(data);
            return;
        }
        client->data = data;
    } else
        perror("accept data error");
}
