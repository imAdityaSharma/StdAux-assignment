/*

Start -

step 1 -->	Create a TCP socket
step 2 -->	Bind the socket to the port 8080
step 3 -->	Listen for incoming connections
step 4 -->	Accept an incoming connection
step 5 -->	Read the HTTP request from the client
step 6 -->	Parse the HTTP request to determine the method and path
step 7 -->	If the method is not GET
	    ----->	Send a 405 Method Not Allowed response and close the connection
        -->	Else
	    ----->	Get the parameters passed with the GET request
step 8 -->	Generate the HTTP response
step 9 -->	Send the HTTP response to the client
step 10 -->	Close the connection

End

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0); //creating TCP socket
  if (socket_fd < 0) {
    perror("socket");
    exit(EXIT_FAILURE);  }

/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
  // Binding socket to the port
  struct sockaddr_in ServerAddress;
  ServerAddress.sin_family = AF_INET;
  ServerAddress.sin_addr.s_addr = INADDR_ANY;
  ServerAddress.sin_port = htons(PORT);
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */

  int bind_result = bind(socket_fd, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress));
  if (bind_result < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

int listen_result = listen(socket_fd, 10);   // Listening for incoming connections
  if (listen_result < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  int ClientSocket = accept(socket_fd, NULL, NULL); // Accepting an incoming connection
  if (ClientSocket < 0) {
    perror("accept");
    exit(EXIT_FAILURE);  }

  char request_buffer[1024];
  int bytes_received = recv(ClientSocket, request_buffer, sizeof(request_buffer), 0); // get HTTP request
  if (bytes_received < 0) {
    perror("recv");
    exit(EXIT_FAILURE);
  }

  // Parseing the HTTP request
  char *method = strtok(request_buffer, " ");
  char *path = strtok(NULL, " ");
  
  if (strcmp(method, "GET") != 0)// Checking if request is a GET request
   {  send(ClientSocket, "HTTP/1.1 405 Method Not Allowed\r\n\r\n", 32, 0);
      close(ClientSocket);
      exit(EXIT_SUCCESS);  }

  char *parameters = strtok(NULL, "\r\n"); // Getting parameters passed with the GET request
  char response_buffer[1024];
  sprintf(response_buffer, "HTTP/1.1 200 OK\r\nContent-Encoding: utf-8\r\nContent-Type: text/html\r\n\r\n<h1>Hello, world!</h1>\n<p>Parameters: %s</p>\n", parameters);// creating HTTP response
  int bytes_sent = send(ClientSocket, response_buffer, sizeof(response_buffer), 0);  // Sending HTTP response
  if (bytes_sent < 0) {
    perror("send");
    exit(EXIT_FAILURE);  }

  close(ClientSocket);
  close(socket_fd);
  return EXIT_SUCCESS;
}
