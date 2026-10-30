#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "http.h"

#define PORT 8080

int main(void)
{
    int server_fd;
    int client_fd;

    struct sockaddr_in server_addr;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1)
    {
        perror("socket");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(PORT);

    // Bind socket to address and port
    if (bind(server_fd,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(server_fd);
        return 1;
    }

    // Start listening
    if (listen(server_fd, 10) == -1)
    {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("HTTP server listening on http://127.0.0.1:%d\n", PORT);

    while (1)
    {
        // Wait for a client
        client_fd = accept(server_fd, NULL, NULL);

        if (client_fd == -1)
        {
            perror("accept");
            continue;
        }

        printf("Client connected!\n");

        char buffer[4096];

        ssize_t bytes_received = recv(
            client_fd,
            buffer,
            sizeof(buffer) - 1,
            0
        );

        printf("recv returned: %zd\n", bytes_received);

        if (bytes_received > 0)
        {
            buffer[bytes_received] = '\0';

            printf("Request:\n%s\n", buffer);

            struct HttpRequest request;

            if (parse_request(buffer, &request) == -1)
            {
                printf("Invalid request\n");
                close(client_fd);
                continue;
            }
            printf("Method: %s\n", request.method);
            printf("Path: %s\n", request.path);
            printf("Version: %s\n", request.version);

        }

        close(client_fd);
    }

    close(server_fd);

    return 0;
}
