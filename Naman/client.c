#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    bzero(buffer,256);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //Use the arguments
    server = gethostbyname(argv[1]); //where server is running
    portno = atoi(argv[2]);// what port no.

    //create a socket over the internet
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
	printf("Error creating socket");

    //set up the socket details of server
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);//host can be same but port is diff

    //connect the socket to server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        printf("ERROR connecting");
    printf("Please enter the message: ");
    fgets(buffer,255,stdin);
    //write to the socket for sending
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         printf("Error writing to socket");
    close(sockfd);
    return 0;
}
