/*
Flow of program
START --> Initialize Winsock (socket library for windows) 
-->Create Server Socket --> Bind Server Socket --> Listen for incoming Connections
-->Accept Client Connection --> Serve Request to Client --> Send "Hello, World!" 
-->Make HTTP Request to External Server --> Receive and Print HTTP Response from External Server
-->Close Client Socket --> Repeat for New Connections 
--> END

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h> //windows socket library
#include <windows.h>

#define ServerPort 8080
#define TargetIp "127.0.0.1"
#define TargetSPort 80

void Serverreq(SOCKET client_soc) {
    char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
    send(client_soc, response, sizeof(response), 0);
}

void http_req() {
    WSADATA wsa;
    SOCKET client_soc;
    struct sockaddr_in ServerAddress;
    int ServerAddress_len = sizeof(ServerAddress);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        perror("WSAStartup failed");
        return;
    }
    client_soc = socket(AF_INET, SOCK_STREAM, 0);
    if (client_soc == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        return;
    }
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(TargetSPort);
    ServerAddress.sin_addr.s_addr = inet_addr(TargetIp);
    if (connect(client_soc, (struct sockaddr*)&ServerAddress, ServerAddress_len) == SOCKET_ERROR) {
        perror("Connection failed");
        closesocket(client_soc);
        WSACleanup();
        return;
    }

    char req[] = "GET / HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
    send(client_soc, req, sizeof(req), 0);

    char response[4096];
    recv(client_soc, response, sizeof(response), 0);
    printf("Received response:\n%s\n", response);
    closesocket(client_soc);
    WSACleanup();
}

int main() {
    WSADATA wsa;
    SOCKET server_soc, client_soc;
    struct sockaddr_in ServerAddress, client_addr;
    int client_addr_len = sizeof(client_addr);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        perror("WSAStartup failed");
        return 1;
    }

    server_soc = socket(AF_INET, SOCK_STREAM, 0);
    if (server_soc == INVALID_SOCKET) {
        perror("Socket creation failed");
        WSACleanup();
        return 1;
    }

    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
    ServerAddress.sin_port = htons(ServerPort);

    if (bind(server_soc, (struct sockaddr*)&ServerAddress, sizeof(ServerAddress)) == SOCKET_ERROR) {
        perror("Bind failed");
        closesocket(server_soc);
        WSACleanup();
        return 1;
    }
    if (listen(server_soc, 5) == SOCKET_ERROR) {
        perror("Listen failed");
        closesocket(server_soc);
        WSACleanup();
        return 1;
    }
    printf("Server is listening on port %d...\n", ServerPort);
    while (1) {
        client_soc = accept(server_soc, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_soc == INVALID_SOCKET) {
            perror("Accept failed");
            break;
        }
        Serverreq(client_soc);
        http_req();
        closesocket(client_soc);
    }
    closesocket(server_soc);
    WSACleanup();
    return 0;
}
