#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include "include/server.h"

/*
 *  Desc: Instantiate server object
 *  Func: server_constructr()
 *  Param: proto_family
 *  Param: port
 *  Param: address
 *  Param: backlog
 *  Return: Server_t*
 */

Server_t* server_constructor(int ip_family, int port, long address, int backlog, int sock_type, int protocol){
   
    Server_t* server = (Server_t*)calloc(1, sizeof(Server_t));
    if (server == NULL) {
        perror("ERROR: Could not alloc for server");
        exit(EXIT_FAILURE);
    }

    server->address =  (struct sockaddr_in*)calloc(1, sizeof(struct sockaddr_in));

    if (server->address == NULL) {
        
        perror("ERROR: Sock Address not alloc'd");
        exit(EXIT_FAILURE);
    
    }

    server->address->sin_family = ip_family;
    server->address->sin_port = htons(port);
    server->address->sin_addr.s_addr = htonl(address);
    server->backlog = backlog;

    server->server_socket = socket(ip_family, sock_type, protocol);

    if (server->server_socket < 0) {
        perror("ERROR: Could not create socket");
        exit(EXIT_FAILURE);
    }
    
    int bind_type = bind(server->server_socket, (struct sockaddr*)server->address, sizeof(struct sockaddr));

    if (bind_type < 0) {
        perror("ERROR: Could not bind socket to address");
        exit(EXIT_FAILURE);
    }

    int listen_type = listen(server->server_socket, server->backlog);

    if (listen_type < 0) {
        perror("ERROR: Could not listen to connections");
        exit(EXIT_FAILURE);
    }

    return server;
}

/*
 *  Desc: Listen to connections from clients
 *  Func: listen_connection()
 *  Param: server
 *  Return: void
 */

void accept_connection(Server_t* server){

    if (server == NULL) {
        perror("ERROR: Server is not instantiated");
        exit(EXIT_FAILURE);
    }

    while(1) {
        int server_addr_len = sizeof(server->address);
        int client_socket = accept(server->server_socket, (struct sockaddr*)&server->address, (socklen_t*)&server_addr_len);

        if (client_socket < 0) {
            perror("ERROR: client could not connect");
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        const char* hello = "HTTP/1.1 200 OK\nDate: Mon, 27 Feb 2022 12:28:53 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Feb 2022 19:15:56 GMT\nContent-Length: 300\nContent-Type: text/html\nConnection: Closed\n\n<!DOCTYPE html><html lang='en'><head><meta charset=UTF-8><title>Web Server In C</title></head><body><h1>Web Server written in C</h1><h3>By Philane Msibi</h3></body></html>";
        read(client_socket, buffer, 1024); 
        write(client_socket, hello, strlen(hello));
        close(client_socket);
    }
}

