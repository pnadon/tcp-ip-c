#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 5000
#define MAXLINE 1024
#define INET_ADDR "127.0.0.1"

int main()
{
  int sockfd;
  char buffer[MAXLINE];
  char* message = "Hello server";
  struct sockaddr_in servaddr;

  int n;

  socklen_t len = sizeof(servaddr);

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    printf("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, len);

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = inet_addr(INET_ADDR);

  sendto(sockfd, (const char*)message, strlen(message),
      0, (const struct sockaddr*)&servaddr, len);

  printf("Message from server: ");
  n = recvfrom(sockfd, (char *)buffer, MAXLINE,
      0, (struct sockaddr*)&servaddr, &len);
  
  puts(buffer);
  close(sockfd);
  return EXIT_SUCCESS;
}
