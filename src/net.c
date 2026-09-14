/*
 * Contains the code for creating the server and client sockets and allowing
 * the server to listen for client connections. Essentially, this creates the
 * server.
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "net.h"

#define PORT "3000"
#define BACKLOG (10)

/*
 * This function creates the server socket with the loopback address and makes
 * the server listen to incoming connections.
 */

int get_server_socket() {
    struct addrinfo hints;  /* limits potential addresses to connect to */
    struct addrinfo *res;   /* tracks potential address to connect to */
    int status;             /* tracks return values for errors */
    int sockfd;

    memset(&hints, 0, sizeof(hints));

    hints.ai_flags = AI_PASSIVE;        /* use loopback address */
    hints.ai_family = AF_UNSPEC;        /* use IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(NULL, PORT, &hints, &res);

    if (status != 0) {
        fprintf(stderr, "[ERROR] %s\n", gai_strerror(status));
        exit(1);
    }

    struct addrinfo *tmp_addr = NULL;

    for (tmp_addr = res; tmp_addr != NULL; tmp_addr = tmp_addr->ai_next) {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        if (sockfd == -1) {
            fprintf(stderr, "[WARNING] unable to create server socket\n");
            continue;
        }

        int on = 1;
        status = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

        if (status == -1) {
            fprintf(stderr, "[WARNING] unable to set server socket options\n");
            close(sockfd);
            continue;
        }

        status = bind(sockfd, res->ai_addr, res->ai_addrlen);

        if (status == -1) {
            fprintf(stderr, "[WARNING] unable to bind server socket\n");
            close(sockfd);
            continue;
        }

        break;
    }

    freeaddrinfo(res);

    /* indicates no address found */

    if (tmp_addr == NULL) {
        fprintf(stderr, "[ERROR] unable to find connectable address\n");

        /* prints end of serving starting header in server.c */

        printf("\n\n");
        printf("************************************************************"
               "****");
        exit(1);
    }

    status = listen(sockfd, BACKLOG);

    if (status == -1) {
        fprintf(stderr, "[ERROR] unable to listen with server socket\n");
        close(sockfd);
        printf("\n\n");
        printf("************************************************************"
               "****");
        exit(1);
    }

    char ip[INET6_ADDRSTRLEN] = { '\0' };
    get_ip(tmp_addr->ai_addr, ip, sizeof(ip));
    ip[sizeof(ip) - 1] = '\0';
    printf("> Server started with IP %s\n", ip);

    return sockfd;
} /* get_server_socket() */

/*
 * This function creates a socket for communicating with the client.
 */

int get_client_socket(int server_socket) {
    struct sockaddr_storage client_sockaddr;  /* stores client address info */
    socklen_t client_addrlen = sizeof(client_sockaddr);
    int sockfd;
    
    sockfd = accept(server_socket, (struct sockaddr *)&client_sockaddr,
                    &client_addrlen);

    if (sockfd == -1) {
        fprintf(stderr, "[ERROR] unable to create client socket\n");
        exit(1);
    }
    
    char ip[INET6_ADDRSTRLEN] = { '\0' };
    get_ip((struct sockaddr *)&client_sockaddr, ip, sizeof(ip));
    ip[sizeof(ip) - 1] = '\0';
    printf("cli ip: %s\n");
    
    return sockfd;
} /* get_client_socket() */

/*
 * This function gets the IP given by the addr, and puts it into the buf.
 */

void get_ip(struct sockaddr *addr, char *buf, int buf_size) {
    char ip[INET6_ADDRSTRLEN] = { '\0' };

    if (addr->sa_family == AF_INET) {
        inet_ntop(AF_INET, &(((struct sockaddr_in *)addr)->sin_addr), ip,
                  sizeof(ip));
    } else {
        inet_ntop(AF_INET6,
                  &(((struct sockaddr_in6 *)addr)->sin6_addr), ip,
                  sizeof(ip));
    }

    strncpy(buf, ip, buf_size);
} /* print_ip() */
