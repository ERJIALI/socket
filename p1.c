#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

void error(char *message);

void error(char *message){
    printf("%s\n", message);
    exit(1);
}


int main(int argc, char *argv[]){
    
    
    if(argc != 3){
        printf("usage %s file", argv[0]);
        exit(0);
    }
    char *address = argv[1]; //server IP address
    char *port = argv[2]; //server port
    
    // create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0){
        error("create socket failed");
    }
    //contruct the server address structure
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr)); // set struct be 0
    servAddr.sin_family = AF_INET;
    int servIP = inet_pton(AF_INET, address, &servAddr.sin_addr.s_addr); //convers the string representat of the server's Internet address in dotted-quad notation into a 32-bit binary representation
    int servPort = atoi(port);
    servAddr.sin_port = htons(servPort); //converts the string port to binary earlier, ensure that the binary value is formatted as required by the API
    
    // establish the connection to server
    int connection = connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr));
    if(connection < 0){
        error("connect failed");
    }
    
    if(stdin = NULL){
        error("Error opening file");
        exit(1);
    }
    //send the str in socket to the server
    //receive the socket
    size_t bufsize = 1024;
    char buffer[bufsize];
    ssize_t numBytes;
    while(fgets(buffer, bufsize , stdin) != NULL){
	numBytes = send(sockfd, buffer, bufsize, 0);
	if(numBytes < 0){
		error("send failed");
	}
    }
    
	unsigned int totalBytes = 0;
    while(totalBytes < bufsize){
	char buffer[bufsize];
	numBytes = recv(sockfd,  buffer, bufsize-1, 0);
	if(numBytes < 0){
		error("received failed");
	}
	totalBytes +=numBytes;
	buffer[numBytes] = '\0';
	fputs(buffer, stdout);
}
	
	
    fputc('\n', stdout);
    close(sockfd);
    exit(0);

}