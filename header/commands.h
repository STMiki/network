/*
** EPITECH PROJECT, 2019
** commands.h
** File description:
** Simple description
*/

#pragma once

#include "definition.h"

void command_user(server_t *server, client_t *client);
void command_pass(server_t *server, client_t *client);
void command_cdup(server_t *server, client_t *client);
void command_quit(server_t *server, client_t *client);
void command_dele(server_t *server, client_t *client);
void command_pasv(server_t *server, client_t *client);
void command_port(server_t *server, client_t *client);
void command_help(server_t *server, client_t *client);
void command_noop(server_t *server, client_t *client);
void command_retr(server_t *server, client_t *client);
void command_stor(server_t *server, client_t *client);
void command_list(server_t *server, client_t *client);
void command_cwd(server_t *server, client_t *client);
void command_pwd(server_t *server, client_t *client);
