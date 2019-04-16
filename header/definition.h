/*
** EPITECH PROJECT, 2019
** definition.h
** File description:
** Simple description
*/

#pragma once

#include <netinet/in.h>

#define DELIMITER " "
#define MAX_CLIENT 5

#define LOGGED         1
#define DATA_CONNECTED 2

typedef struct client_s client_t;
typedef struct server_s server_t;

struct client_s {
    int connected;
    int fd;
    int data;
    int data_server;
    int active;
    int port;
    int logged;
    char *user;
    char *home;
    char *pwd;
    char *ip;
};

struct server_s {
    fd_set main;
    fd_set list;
    int listener;
    int maxfd;
    char *ip;
    client_t client[MAX_CLIENT];
};

int my_random(int min, int max);
char *getnextline(int fd);
int test_dir(const char *path);
int init(int port, int nb_client);
void add_client(int client, client_t list[], const char *home,
                struct sockaddr_in from);
void handle(server_t *server, client_t *client);
void handle_data_connection(client_t *client);
void handle_boucle(server_t *server, const char *home);
void boucle_main(server_t *server, const char *home);
void parse_command(server_t *server, client_t *client, char *raw);
void clean_client(server_t *server, client_t *client);
int create_data_connection(server_t *server, client_t *client);
void clear_server(server_t *server, client_t *client);
char *get_path(client_t *client);
int wait_until_data(client_t *client);
int detect_command_error(client_t *client, int flags);
