#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[2000], client_message[2000];
	
	memset(server_message, '\0', sizeof(server_message));
	memset(client_message, '\0', sizeof(client_message));
	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc < 0)
	{
		perror("Unable to create socket");
		return -1;
	}
	printf("Socket created successfully\n");
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Unable to connect");
		close(socket_desc);
		return -1;
		
	}
	printf("Connected with server successfully\n");
	
	printf("Enter message: ");
	if(fgets(client_message, sizeof(client_message), stdin) == NULL)
	{
		perror("Error reading input");
		close(socket_desc);
		return -1;
	}
	
	if(send(socket_desc, client_message, strlen(client_message), 0) < 0)
	{
		perror("Unable to send message");
		close(socket_desc);
		return -1;
	}
	
	if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0)
	{
		perror("Error while receiving server's message");
		close(socket_desc);
		return -1;
	}
	
	printf("Server's response: %s\n", server_message);
	
	close(socket_desc);
	
	return 0;
}
