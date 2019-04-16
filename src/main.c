/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Simple description
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "definition.h"

void help(const char *binary)
{
    printf("USAGE: %s port path\n", binary);
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory for the Anonymous user\n");
}

int error_management(int argc, char *argv[])
{
    int port = 0;

    if (argc == 2 && !strcmp(argv[1], "-help")) {
        help(argv[0]);
        return (0);
    } else if (argc != 3) {
        dprintf(2, "Error: see %s -help for help\n", argv[0]);
        return (-1);
    }
    if (!test_dir(argv[2])) {
        dprintf(2, "Error: '%s' not a directory", argv[2]);
        return (-1);
    } else if ((port = atoi(argv[1])) == 0) {
        dprintf(2, "Error: the port (%s) need to be numeric.", argv[1]);
        return (-1);
    }
    return (port);
}

int main(int argc, char *argv[])
{
    server_t server;
    int port = 0;

    port = error_management(argc, argv);
    if (port == -1)
        return (84);
    else if (port == 0)
        return (0);
    printf("Starting...\n");
    if ((server.listener = init(port, MAX_CLIENT)) == -1)
        return (84);
    server.maxfd = server.listener;
    boucle_main(&server, argv[2]);
    return (0);
}
