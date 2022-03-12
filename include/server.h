#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

/*
 *  Desc: Contains server prototypes
 *  Author: Philane Msibi
 *  Model: Server
 */

typedef struct SERVER_STRUCT {

    struct sockaddr_in* address;
    int server_socket;
    int backlog;

} Server_t;


/*
 *  Desc: Instantiate server object
 *  Func: server_constructr()
 *  Param: proto_family
 *  Param: port
 *  Param: address
 *  Param: backlog
 *  Return: Server_t*
 */

Server_t* server_constructor(int ip_family, int port, long address, int backlog, int sock_type, int protocol);

/*
 *  Desc: Listen to connections from clients
 *  Func: listen_connection()
 *  Param: server
 *  Return: void
 */

void accept_connection(Server_t* server);

