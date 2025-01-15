#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr; // Structures to hold server and client address information
    char server_message[2000], client_message[2000]; // Buffers for messages
    
    // Clean Buffers:
    memset(server_message, '\0', sizeof(server_message)); // Initialize server message buffer
    memset(client_message, '\0', sizeof(client_message)); // Initialize client message buffer
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    
    // Check if socket creation was successful
    if (socket_desc < 0)
    {
        printf("Error while creating socket\n");
        return -1; // Exit if socket creation failed
    }
    printf("Socket created successfully\n");
    
    // Set up the server address structure
    server_addr.sin_family = AF_INET; // Use IPv4
    server_addr.sin_port = htons(2000); // Set port number (2000) and convert to network byte order
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Set IP address to localhost
    
    // Bind the socket to the specified port and IP address
    if (bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) // Fixed parentheses
    {
        printf("Couldn't bind to the port\n");
        return -1; // Exit if binding failed
    }
    printf("Done with binding\n");
    
    // Listen for incoming client connections
    if (listen(socket_desc, 1) < 0) // Listen for a maximum of 1 client
    {
        printf("Error while listening\n"); // Fixed missing quote
        return -1; // Exit if listening failed
    }
    printf("Listening for incoming connections....\n"); // Fixed missing quote
    
    // Accept an incoming connection
    client_size = sizeof(client_addr); // Get the size of the client address structure
    client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size); // Accept the connection
    
    // Check if the connection was accepted successfully
    if (client_sock < 0)
    {
        printf("Can't accept\n");
        return -1; // Exit if accepting the connection failed
    }
    // Print the client's IP address and port number
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    // Receive a message from the client
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
    {
        printf("Couldn't receive\n");
        return -1; // Exit if receiving the message failed
    }
    // Print the received message from the client
    printf("Message from client: %s\n", client_message);
    
    // Prepare the server's response message
    strcpy(server_message, "This is the server's message.");
    
    // Send the server's message to the client
    if (send(client_sock, server_message, strlen(server_message), 0) < 0) // Fixed parentheses
    {
        printf("Can't send\n");
        return -1; // Exit if sending the message failed
    }
    
    // Close the client socket and the server socket
    close(client_sock); // Close the connection with the client
    close(socket_desc); // Close the server socket
    
    return 0; // Exit the program successfully
}
