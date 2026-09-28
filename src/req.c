/*
 * This file contains 
 */

#include "req.h"

/*
 * This function finds the boundary string used for form data in POST requests
 * from the request argument and then copies it to the boundary argument.
 */

int get_boundary(char *request, char *boundary) {
    char *boundary_start = strstr(request, "boundary=");

    if (boundary_start == NULL) {
        fprintf(stderr, "[ERROR] error while parsing request\n");
        return SERVER_ERR;
    }

    /* STR(BOUND_MAX_LEN) turns the max boundary length into a string */

    if (sscanf(boundary_start, "boundary=%" STR(BOUND_MAX_LEN) "[^\r\n]",
               boundary) != 1) {
        fprintf(stderr, "[ERROR] error while parsing request\n");
        return SERVER_ERR;
    }

    return SERVER_SUCC;
} /* get_boundary() */

/*
 * This function ...
 */

void handle_post_response(char *response, char *request, int req_len) {
    char boundary[BOUND_BUF_LEN] = { '\0' };
    char *header_end;
    char *body_start;
    size_t boundary_div_len; // boundary between data
    size_t boundary_end_len; // indicates end of data
    char *pos;               // current position in the data

    if (get_boundary(request, boundary) == SERVER_ERR) {
        return;
    }

    header_end = strstr(request, "\r\n\r\n");
    body_start = header_end + strlen("\r\n\r\n");

    boundary_div_len = strlen("--") + strlen(boundary);
    boundary_end_len = boundary_div_len + strlen("--");


    while (1) {
        break;
    }

    printf("boundary = %s\n", boundary);
} /* handle_post_response() */
