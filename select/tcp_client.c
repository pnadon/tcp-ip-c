#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define MAXLINE 1024
#define INET_ADDR "127.0.0.1"

int main()
{
  int sockfd;
  char buffer[MAXLINE];
  char* message = "Hello Server";
  struct sockaddr_in servaddr;
  int ret_status;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = inet_addr(INET_ADDR);

  if ((ret_status = connect(sockfd, (struct sockaddr *)&servaddr,
        sizeof(servaddr))) < 0)
  {
    printf("\n Error: Connect failed: %d\n", ret_status);
  }

  memset(buffer, 0, sizeof(buffer));
  strcpy(buffer, "Hello Server");
  write(sockfd, buffer, sizeof(buffer));
  printf("Message from server: ");
  read(sockfd, buffer, sizeof(buffer));
  puts(buffer);
  close(sockfd);
}
