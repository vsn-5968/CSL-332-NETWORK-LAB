#include<sys/types.h>
#include<sys/socket.h>

int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
