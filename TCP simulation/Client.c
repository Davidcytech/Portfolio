#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
int main(void)
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {
        printf("Failed to create socket\n");
        return 1;
    }

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_address.sin_port = htons(8080);

    connect(client_socket,
            (struct sockaddr *)&server_address,
            sizeof(server_address));

    char message[] = "Hello Server!";
    send(client_socket, message, sizeof(message), 0);
    close(client_socket);
    return 0;
}