#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     bzero((char *) &serv_addr, sizeof(serv_addr));
     bzero(buffer,256);
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;//any random ip
     serv_addr.sin_port = htons(portno);
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if(sockfd<0)
	printf("Socket error");

     //bind socket to the port and host(ip)
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              printf("Error encountered");
     //wait for conenctions, max 5 connections allowed
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
//this socket descriptor will be used for r/w
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          printf("Error creating the new socket");

/////////////BELOW SERVER CLIENT COMM. FOLLOWS///////////
     n = read(newsockfd,buffer,255);
     if(n<0)
     printf("Read error");
     else
     printf("Received: %s",buffer);

     close(newsockfd);
     close(sockfd);
     return 0; 
}
