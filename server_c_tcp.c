// server_tcp.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

bool isNumber(const char *buffer) {
// PRECONDITION: buffer is a character array
// POSTCONDITION: returns true if all elements in buffer are integers, false otherwise
	for (int i=0; i<strlen(buffer)-1; i++)
		if (!isdigit(buffer[i])) return false;
	return true;
}

char* toArray(int num) {
// PRECONDITION: n is positive
// POSTCONDITION: converts integer n into a character array
	int n = log10(num) + 1;
	char *numberArray = calloc(n, sizeof(char));
	for (int i=n-1; i>=0; --i, num/=10) {
		numberArray[i] = (num % 10) + '0';
	}
	return numberArray;
}

char* getSum(char *buffer) {
// PRECONDITION: buffer is non-empty and is all integers
// POSTCONDITON: returns a char array of the sum of buffer's digits
	int sum = 0;
	//printf("length of buffer: %lu\n",strlen(buffer));
	for (int i=0; i<strlen(buffer); i++) {
		if (isdigit(buffer[i]))  // since last element might be null terminator
			sum += buffer[i]-'0';
		//printf("buffer[%i]: ",i);
		//printf("%c\n",buffer[i]);
	}
	//printf("sum: %i\n",sum);
	int n = log10(sum) + 1;
	char *numberArray = calloc(n+1, sizeof(char));
	for (int i=n-1; i>=0; --i, sum/=10) {
		numberArray[i] = (sum%10) + '0';
	}
	numberArray[n] = '\0';
	return numberArray;
}

int main(int argc, char *argv[]) {

	// MAKE VARIABLES	
	int sockfd, newsockfd, portno;  
	socklen_t clilen;  // socket length variable
	char buffer[256];  // 256 bytes
	struct sockaddr_in serv_addr, cli_addr;  // address structures

	if (argc < 2) {  // check # of arguments
		fprintf(stderr,"ERROR, no port provided (delete this)\n");
		exit(1);
	}

	// CREATE NEW SOCKET
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// POPULATE serv_addr STRUCTURE
	bzero((char *) &serv_addr, sizeof(serv_addr));  // clears serv_addr struct
	portno = atoi(argv[1]);  // get port number 
	serv_addr.sin_family = AF_INET;  // for IPv4
	serv_addr.sin_addr.s_addr = INADDR_ANY;  // where to accept connections from (all interfaces)
	serv_addr.sin_port = htons(portno);  // what port to bind to

	// BIND SOCKET TO THE ADDRESS
	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

	// LISTEN ON SOCKET FOR NEW CONNECTIONS
	listen(sockfd,5); 

	// ACCEPT CONNECTION FROM CLIENT
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	bzero(buffer,256);  // clear buffer
	while (read(newsockfd,buffer,255) > 0) {
		if (!isNumber(buffer)) {
			write(newsockfd,"Sorry, cannot compute!",22);
			break;
		}
		else if (strlen(buffer)<2) break;
		else {
			memcpy(buffer, getSum(buffer), strlen(buffer));  // overwrites buffer with its sum
			write(newsockfd,buffer,strlen(buffer));
			bzero(buffer,256);
		}
	}

	// CLOSES CLIENT'S SOCKET AND SERVER'S LISTENING SOCKET
	close(newsockfd);
	close(sockfd);

	return 0;
}

/* TO COMPILE:
 * gcc server.c -o server */

/* USAGE:
 * ./server <PORT>
 * ie. ./server 8000 
 * creates new socket bound to port 8000 w/ address 0.0.0.0 (listens to all interfaces) */


/*
 *
			 printf("buffer: %s\n", buffer);
			 printf("buffer length: %lu\n", strlen(buffer));
			 */
