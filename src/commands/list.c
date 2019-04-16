/*
** EPITECH PROJECT, 2019
** list.c
** File description:
** Simple description
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <dirent.h>
#include <unistd.h>
#include "definition.h"

char *get_path(client_t *client)
{
    char *path = strtok(NULL, DELIMITER);
    char *temp = NULL;

    if (path == NULL || strlen(path) == 0)
        return (strdup(client->pwd));
    else if (path[strlen(path) - 1] == '\r')
        path[strlen(path) - 1] = 0;
    if (path[0] == '/')
        return (strdup(path));
    temp = malloc(sizeof(char) * (strlen(path) + strlen(client->pwd) + 2));
    bzero(temp, sizeof(char) * (strlen(path) + strlen(client->pwd) + 2));
    strcpy(temp, client->pwd);
    if (client->pwd[strlen(client->pwd) - 1] != '/') {
        temp[strlen(temp) + 1] = 0;
        temp[strlen(temp)] = '/';
    }
    strcat(temp, path);
    return (temp);
}

static int execute_ls(client_t *client)
{
    int pid = 0;
    char *path = get_path(client);
    int status = 0;

    if ((pid = fork()) == 0) {
        dup2(client->data, 1);
        execvp("ls", (char *[]) {"ls", "-l", path, NULL});
        exit(84);
    } else if (pid == -1)
        return (1);
    do {
        waitpid(pid, &status, WEXITED | WCONTINUED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return (status == 0 ? 0 : 1);
}

int wait_until_data(client_t *client)
{
    fd_set list;
    struct timeval timeout;
    int nb_client = 0;

    if (client->data)
        return (0);
    FD_ZERO(&list);
    FD_SET(client->data_server, &list);
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
    nb_client = select(client->data_server + 1, &list, NULL, NULL, &timeout);
    if (nb_client == -1) {
        perror("Select");
        return (1);
    } else if (nb_client == 0) {
        dprintf(client->fd, "226 Timeout\r\n");
        return (1);
    }
    handle_data_connection(client);
    return (0);
}

void command_list(server_t *server, client_t *client)
{
    if (!client->logged) {
        dprintf(client->fd, "530 Please login with USER and PASS\r\n");
        return;
    }
    if (client->active == 0 && !client->data_server) {
        dprintf(client->fd, "425 Use PORT or PASV first.\r\n");
        return;
    } else if (client->active == 1 && !client->data) {
        dprintf(client->fd, "425 Use PORT or PASV first.\r\n");
        return;
    }
    if (wait_until_data(client))
        return;
    dprintf(client->fd, "150 Here come the directory listing\r\n");
    if (execute_ls(client)) {
        dprintf(client->fd, "226 Transfert done ");
        dprintf(client->fd, "(but failled to open directory).\r\n");
    }
    dprintf(client->fd, "226 Transfert done.\r\n");
    clear_server(server, client);
}
