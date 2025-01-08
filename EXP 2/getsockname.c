#include<sys/types.h>
#include<sys/socket.h>

int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
