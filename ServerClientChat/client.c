#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 80
#define PORT 43454
#define SA struct sockaddr

void func(int sockfd)
{
  char buff[MAX];
  int n;
  for(;;)
{
  bzero(buff,sizeof(buff));
  printf("Enter The String : ");
  n=0

  while((buff[n++]=getchar())!='\n');
  write(sockfd,buff,sizrof(buff));
  bzero(buff,sizeof(buff));
  read(sockfd,buff,sizeof(buff));
  printf("From server : %s",buff);

if((strncmp(buff,"exit",4))=0)
{
  printf("Client Exit...\n");
  break;
}}}

int main ()
{
  int sockfd,connfd;
  struct sockaddr_in servaddr,cli;
  sockfd=socket(AF_INET,SOCK_STREAM,0);

if(sockfd==-1)
{
  printf("Socket Creation failed...\n");
  exit(0);
}
 else
    printf("socket Successfully created...n\");

bzero(&servaddr,sizeof(servaddr));

  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s=inet_addr("192.168.65.129");
  servaadr.sin_port=htons(PORT);

if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr))!=0)
{
  printf("Connection With the Server failed...\n");
  exit(0);
}

  else
      printf("Connected To The Server...\n")

func(sockfd);
close(sockfd);

}