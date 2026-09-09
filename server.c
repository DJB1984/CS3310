/*
Author: Davis Brooks
Base implementation author: Vighnesh Birodkar
Date: Fall 2026

Purpose: A server that takes input text input from a client, converts it to Cow 
Code then returns it to the client.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Converts given text to Cow Code
void convertToCowCode(char *str, char *strInCowCode) {

    //Map the letters of the alphebet to their correspoding Cow Code values.
    struct CowCode {
        char letter;
        char *code;
    };

    struct CowCode cowCodeDict[] = {
        {'A', "OM"}, {'a', "om"},
        {'B', "MOOO"}, {'b', "mooo"},
        {'C', "MOMO"}, {'c', "momo"},
        {'D', "MOO"}, {'d', "moo"},
        {'E', "O"}, {'e', "o"},
        {'F', "OOMO"}, {'f', "oomo"},
        {'G', "MMO"}, {'g', "mmo"},
        {'H', "OOOO"}, {'h', "oooo"},
        {'I', "OO"}, {'i', "oo"},
        {'J', "OMMM"}, {'j', "ommm"},
        {'K', "MOM"}, {'k', "mom"},
        {'L', "OMOO"}, {'l', "omoo"},
        {'M', "MM"}, {'m', "mm"},
        {'N', "MO"}, {'n', "mo"},
        {'O', "MMM"}, {'o', "mmm"},
        {'P', "OMMO"}, {'p', "ommo"},
        {'Q', "MMOM"}, {'q', "mmom"},
        {'R', "OMO"}, {'r', "omo"},
        {'S', "OOO"}, {'s', "ooo"},
        {'T', "M"}, {'t', "m"},
        {'U', "OOM"}, {'u', "oom"},
        {'V', "OOOM"}, {'v', "ooom"},
        {'W', "OMM"}, {'w', "omm"},
        {'X', "MOOM"}, {'x', "moom"},
        {'Y', "MOMM"}, {'y', "momm"},
        {'Z', "MMOO"}, {'z', "mmoo"},
    };

    //Replace every letter with it's Cow Code corresponding values.
    for (int i = 0; str[i] != '\0'; i++) {

        bool isReplaced = false;

        //Loop through the Cow Code dictionary and replace.
        for (int j = 0; j <= 52; j++) {

            if (str[i] == cowCodeDict[j].letter){

                strcat(strInCowCode, cowCodeDict[j].code);
                isReplaced = true;
            }
        }

        //If the current character isn't a letter it isn't replaced.
        if(!isReplaced){

            int len = strlen(strInCowCode);
            strInCowCode[len] = str[i];
            strInCowCode[len + 1] = '\0';
        }
    }

    strcat(strInCowCode, "\n");
}
 
int main() {
    char str[1000];
    char strInCowCode[1000];
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;
 
    //Open the socket. Bind and listen on the port.
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(39876);
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listen_fd, 10);

    printf("The server is running...\n");
    printf("Text sent to this server will be encrypted it into Cow Code.\n");
 
    //Accepts data from the client, converts the received data to cow code, closes connection, and repeats.
    while(1) {
 
        comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
 
        bzero(str, 1000);
        bzero(strInCowCode, 1000);
 
        read(comm_fd, str, 1000);
 
        printf("Converting: '%s' to Cow Code.\n", str);

        convertToCowCode(str, strInCowCode);
 
        write(comm_fd, strInCowCode, strlen(strInCowCode)+1);

        close(comm_fd);
    }
}