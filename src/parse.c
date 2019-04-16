/*
** EPITECH PROJECT, 2019
** parse.c
** File description:
** Simple description
*/

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include "definition.h"
#include "commands.h"

static const char *COMMANDS[] = {
    "USER",
    "PASS",
    "CWD",
    "CDUP",
    "QUIT",
    "DELE",
    "PWD",
    "PASV",
    "PORT",
    "HELP",
    "NOOP",
    "RETR",
    "STOR",
    "LIST"
};
static void (*ACTIONS[])(server_t *, client_t *) = {
    command_user,
    command_pass,
    command_cwd,
    command_cdup,
    command_quit,
    command_dele,
    command_pwd,
    command_pasv,
    command_port,
    command_help,
    command_noop,
    command_retr,
    command_stor,
    command_list
};
static const int COMMANDS_SIZE = sizeof(COMMANDS) / sizeof(COMMANDS[0]);

void parse_command(server_t *server, client_t *client, char *raw)
{
    char *command = NULL;
    int found = 0;

    if (raw == NULL)
        return;
    for (int i = 0; raw[i]; i+= 1)
        raw[i] = raw[i] == '\r' ? 0 : raw[i];
    command = strtok(raw, DELIMITER);
    for (int i = 0; i < COMMANDS_SIZE; i += 1) {
        if (strcmp(command, COMMANDS[i]) == 0) {
            found = 1;
            ACTIONS[i](server, client);
        }
    }
    if (found)
        return;
    dprintf(client->fd, "502 Command not found.\r\n");
}
