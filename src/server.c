#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "cache.h"
#include "http.h"
#include "net.h"

int main() {
    printf("****************************************************************");
    printf("\n\n");

    printf("> Starting server...\n");

    int server_socket = get_server_socket(); /* prints IP */

    /* capacity of ten and expire entries after two minutes */

    cache_t *cache = create_cache(10, 120);

    if (cache != NULL) {
        printf("> Created server cache...\n");
    } else {
        printf("> Unable to created server cache...\n");
    }

    printf("> Server listening for incoming connections...\n");

    printf("\n");
    printf("****************************************************************");
    printf("\n\n");

    while (1) {
        int client_socket = get_client_socket(server_socket);

        handle_http_request(client_socket, cache);

        close(client_socket);
        
        printf("\n");
        printf("--------------------------------------------------------------"
               "--");
        printf("\n\n");
    }

    close(server_socket);
}
