#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/server.h"

int main(int argc, const char* argv) {

    Server_t* server = server_constructor(AF_INET, 8081, INADDR_ANY, 3, SOCK_STREAM, 0);
    accept_connection(server);
    return 0;
}
