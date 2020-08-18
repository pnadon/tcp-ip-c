#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define MAX 80
#define PORT 8080
#define INET_ADDR "127.0.0.1"
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

int main()
{
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

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
  servaddr.sin_addr.s_addr = inet_addr(INET_ADDR);
  servaddr.sin_port = htons(PORT);

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
