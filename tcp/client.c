#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define MAX 80
#define SA struct sockaddr

void chat(int sockfd)
{
  char buff[MAX];
  int n;
  while (1)
  {
    memset(buff, 0, sizeof(buff));
    printf("Enter the string: ");
    n = 0;

    while ((buff[n++] = getchar()) != '\n') ;

    write(sockfd, buff, sizeof(buff));
    memset(buff, 0, sizeof(buff));
    read(sockfd, buff, sizeof(buff));

    printf("From server: %s", buff);
    if ((strncmp(buff, "exit", 4)) == 0)
    {
      printf("Client exiting...\n");
      return;
    }
  }
}

int main(int argc, char* argv[])
{
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  int port_addr;
  char* inet_addr_str;
  if (argc < 3)
  {
     port_addr = 9734;
     inet_addr_str = "127.0.0.1";
  } else
  {
    inet_addr_str = argv[1];
    port_addr = atoi(argv[2]);
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("Socket creation failed...\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Socket successfully created...\n");

  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(inet_addr_str);
  servaddr.sin_port = htons(port_addr);

  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
  {
    perror("Connection with server failed...\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Connected to the server...\n");

  chat(sockfd);

  close(sockfd);
}
