/*

Start
-->	Create a TCP socket
-->	Bind the socket to the port 8080
-->	Listen for incoming connections
-->	Accept an incoming connection
-->	Read the HTTP request from the client
-->	Parse the HTTP request to determine the method and path
-->	If the method is not GET
	----->	Send a 405 Method Not Allowed response and close the connection
-->	Else
	----->	Get the parameters passed with the GET request
-->	Generate the HTTP response
-->	Send the HTTP response to the client
-->	Close the connection
End

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
  // Create a TCP socket
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // Bind the socket to the port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  int bind_result = bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_result < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  int listen_result = listen(socket_fd, 10);
  if (listen_result < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // Accept an incoming connection
  int client_socket_fd = accept(socket_fd, NULL, NULL);
  if (client_socket_fd < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  // Read the HTTP request
  char request_buffer[1024];
  int bytes_received = recv(client_socket_fd, request_buffer, sizeof(request_buffer), 0);
  if (bytes_received < 0) {
    perror("recv");
    exit(EXIT_FAILURE);
  }

  // Parse the HTTP request
  char *method = strtok(request_buffer, " ");
  char *path = strtok(NULL, " ");

  // Check if the request is a GET request
  if (strcmp(method, "GET") != 0) {
    // Not a GET request
    send(client_socket_fd, "HTTP/1.1 405 Method Not Allowed\r\n\r\n", 32, 0);
    close(client_socket_fd);
    exit(EXIT_SUCCESS);
  }

  // Get the parameters passed with the GET request
  char *parameters = strtok(NULL, "\r\n");

  // Generate the HTTP response
  char response_buffer[1024];
  sprintf(response_buffer, "HTTP/1.1 200 OK\r\nContent-Encoding: utf-8\r\nContent-Type: text/html\r\n\r\n<h1>Hello, world!</h1>\n<p>Parameters: %s</p>\n", parameters);

  // Send the HTTP response
  int bytes_sent = send(client_socket_fd, response_buffer, sizeof(response_buffer), 0);
  if (bytes_sent < 0) {
    perror("send");
    exit(EXIT_FAILURE);
  }

  // Close the sockets
  close(client_socket_fd);
  close(socket_fd);

  return EXIT_SUCCESS;
}
