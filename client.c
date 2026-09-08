/*
Author: Davis Brooks
Base implementation author: Vighnesh Birodkar
Date: Fall 2026

Purpose: A client which sends text to and receives text from a server.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
 
int main(int argc, char **argv)
{
    int sockfd,n;
    char sendline[1000];
    char recvline[1000];
    struct sockaddr_in servaddr;

    //Ensure only one command line argument.
    if (argc != 2) {
        printf("Provide one command line argument!\n");
        return;
    }
 
    //Connect to the server.
    sockfd=socket(AF_INET, SOCK_STREAM,0);
    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(39876);
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
    connect(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr));

    //Sends text to the server.
    strcpy(sendline, argv[1]);
    write(sockfd,sendline,strlen(sendline)+1);

    //Receive text from the server.
    read(sockfd, recvline, 1000);
    printf("%s", recvline);
}