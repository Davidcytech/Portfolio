#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
int main(void)
{
    // AF_INET specifies that we want to use IPv4
    // SOCK_STREAM specifies a connection-oriented byte stream
    // 0 lets the system choose the appropriate protocol
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) {
        printf("Failed to create socket\n");
        return 1;
    }

    printf("Socket created: %d\n", server_socket);

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET; //IPv4
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //Adress (loopback IPv4)
    server_address.sin_port = htons(8080); //Port number

    if (bind(server_socket, // Asks the kernel to associate the socket with the given IP address and port
         (struct sockaddr *)&server_address, //points to the server's address
         sizeof(server_address)) == -1) {
        printf("Failed to bind socket\n");
        return 1;
         }
    if (listen(server_socket, 5) == -1) { //Puts the socket into listening mode, 5 is the backlog(queue for pending connections)
        printf("Failed to listen\n");
        return 1;
    }
    int client_socket = accept(server_socket, NULL, NULL);//returns a new client communication socket
    if (client_socket == -1) {
        printf("Failed to accept connection");
        return 1;
    } //Up until now the server will only return a file decriptor

    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received == -1) {
        printf("Failed to receive data\n");
        return 1;
    }

    buffer[bytes_received] = '\0';

    printf("Received: %s\n", buffer);
    close(client_socket);//This socket is the one that takes care of the communication with the client, but not the client's socket itself
    close(server_socket);
    return 0;
}