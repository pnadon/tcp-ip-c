#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void chat(int sockfd)
{
  char buff[MAX];
  int n;

  while(1)
  {
    memset(buff, 0, MAX);

    read(sockfd, buff, sizeof(buff));

    printf("From client: %s\t To client: ", buff);
    memset(buff, 0, MAX);
    n = 0;
    
    while ((buff[n++] = getchar()) != '\n') ;

    write(sockfd, buff, sizeof(buff));

    if (!strncmp("exit", buff, 4))
    {
      printf("Server exit...\n");
      return;
    } 
  }
}

int main()
{
  struct sockaddr_in servaddr, cli;
  int sockfd, connfd;
  socklen_t len = sizeof(servaddr);
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }
  else
    printf("Socket created...\n");

  memset(&servaddr, 0, len);

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  if (bind(sockfd, (SA*)&servaddr, len) != 0)
  {
    perror("listen failed...");
    exit(EXIT_FAILURE);
  }
  else
    printf("Server listening...\n");
  
  if (listen(sockfd, 3) < 0) 
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  connfd = accept(sockfd, (SA*)&cli, &len);
  if (connfd < 0)
  {
    perror("Server accept failed...");
    exit(EXIT_FAILURE);
  }
  else
    printf("Server accepted the client...\n");

  chat(connfd);

  close(sockfd);
}
