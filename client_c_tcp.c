// client_tcp.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

	void error(const char *msg) {
		perror(msg);
		exit(0);
	}
	
	// MAKE VARIABLES
	int sockfd, portno;  // socket file descriptor & port number
	struct sockaddr_in serv_addr;
	struct hostent *server;  // pointer to server's host
	char buffer[256];

	// NEED HOSTNAME & PORT TO CONNECT TO SERVER (AS ARGS)
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

	// CREATE CLIENT SOCKET TO CONNECT TO SERVER
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  // create socket w/ socket() system call
		// sockfd: stores return file descriptor of socket
    if (sockfd < 0) error("ERROR opening socket");  // check if socket() succeeded

	// convert IP address passed by user to valid server address
    server = gethostbyname(argv[1]);
    if (server == NULL) {  // check that server address obtained
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

	// POPULATE serv_addr STRUCT W/ RELEVANT PARAMS
    bzero((char *) &serv_addr, sizeof(serv_addr));  // clears serv_addr
    serv_addr.sin_family = AF_INET;  // server addr family = IPv4
    bcopy((char *)server->h_addr,  // writes server's address into serv_addr
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);  // get port number specified by client

	// USE SERV_ADDR TO CONNECT TO SERVER
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)  // connect() system call
        error("ERROR connecting");  // if returns -1, then error
		// socket file descriptor, pointer to serv_addr, size of serv_addr
		// if success: connection is established btwn client & server

	// CONNECTION SET UP: CLIENT CAN USE SOCKET TO WRITE/READ
	// WRITE TO SOCKET
    printf("Enter string: ");
    bzero(buffer,256);  // clears buffer
    fgets(buffer,255,stdin);  // stores user input into buffer
    write(sockfd,buffer,strlen(buffer));

	// READ FROM SOCKET
	bzero(buffer,256);
	while (read(sockfd,buffer,255) > 0) {
		printf("From server: %s\n",buffer);  // print what server wrote
		write(sockfd,buffer,strlen(buffer));
		bzero(buffer,256);
	}

	// CLOSE SOCKET
    close(sockfd);


	return 0;
}
