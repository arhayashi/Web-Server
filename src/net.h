#ifndef NET_H

#define NET_H

int get_server_socket();
int get_client_socket(int);
void get_ip(struct sockaddr *, char *, int);

#endif
