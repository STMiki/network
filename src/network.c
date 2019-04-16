/*
** EPITECH PROJECT, 2019
** network.c
** File description:
** Simple description
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <netinet/tcp.h>
#include "definition.h"

int init(int port, int nb_client)
{
    struct sockaddr_in server;
    int sd = 0;
    int optval = 1;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        return (-1);
    }
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(sd, IPPROTO_TCP, TCP_NODELAY, (char *) &optval, sizeof(int));
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);
    if (bind(sd, (struct sockaddr*) &server, sizeof(struct sockaddr)) == -1) {
        perror("bind error");
    } else if (listen(sd, nb_client) == -1) {
        perror("listen error");
    } else
        return (sd);
    return (-1);
}

char *get_ip(void)
{
    char temp[INET_ADDRSTRLEN] = {0};
    int pid = 0;
    int fd[2];

    pipe(fd);
    if ((pid = fork()) == 0) {
        dup2(fd[1], 1);
        dup2(open("/dev/null", O_APPEND), 2);
        execvp("curl", (char *[]) {"curl", "https://ifconfig.me/ip", NULL});
        perror("execvp");
        exit(84);
    } else if (pid == -1)
        return (NULL);
    read(fd[0], temp, INET_ADDRSTRLEN);
    for (int i = 0; temp[i]; i += 1) {
        if ((temp[i + 1] >= '0' && temp[i + 1] <= '9') || temp[i + 1] == '.')
            continue;
        temp[i + 1] = 0;
    }
    return (strdup(temp));
}

void handle(server_t *server, client_t *client)
{
    char *raw = getnextline(client->fd);

    if (raw == NULL) {
        printf("Connection ended for %s\n", client->ip);
        clean_client(server, client);
        return;
    }
    parse_command(server, client, raw);
    free(raw);
}

void check_select_data(server_t *server, client_t *client)
{
    if (FD_ISSET(client->fd, &server->list))
        handle(server, client);
    if (client->data && FD_ISSET(client->data, &server->list))
        handle_data_connection(client);
    if (client->data_server && FD_ISSET(client->data_server, &server->list))
        handle_data_connection(client);
}

void handle_boucle(server_t *server, const char *home)
{
    struct sockaddr_in from;
    socklen_t length = sizeof(from);
    int client = 0;

    if (FD_ISSET(server->listener, &server->list)) {
        client = accept(server->listener, (struct sockaddr*) &from, &length);
        if (client >= 0) {
            FD_SET(client, &server->main);
            server->maxfd = server->maxfd > client ? server->maxfd : client;
            add_client(client, server->client, home, from);
            dprintf(client, "220 (myFTP server 1.0)\n");
        } else
            perror("client error");
    }

    for (int i = 0; server->client[i].connected == 1; i += 1)
        check_select_data(server, &server->client[i]);
}

void boucle_main(server_t *server, const char *home)
{
    for (int i = 0; i < MAX_CLIENT; i += 1)
        server->client[i].connected = 0;
    FD_ZERO(&server->main);
    FD_ZERO(&server->list);
    FD_SET(server->listener, &server->main);
    server->ip = get_ip();
    for (int i = 0; server->ip[i]; i += 1)
        server->ip[i] = server->ip[i] == '.' ? ',' : server->ip[i];
    printf("Server started !\n");
    while (fcntl(server->listener, F_GETFD) != -1 || errno != EBADF) {
        server->list = server->main;
        if (select(server->maxfd + 1, &server->list, NULL, NULL, NULL) == -1) {
            perror("Select error");
            continue;
        }
        handle_boucle(server, home);
    }
    for (int i = 0; i < MAX_CLIENT; i += 1)
        clean_client(server, &server->client[i]);
}
