// server_c_udp.c

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<strings.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h> 
#include <math.h>

bool isNumber(const char *buffer) {
// PRECONDITION: buffer is a character array
// POSTCONDITION: returns true if all elements in buffer are integers, false otherwise
	for (int i=0; buffer[i]!='\0' && buffer[i]!='\n'; i++) {
		if (!isdigit(buffer[i])) return false;
	}
	return true;
}

char* getSum(const char *buffer) {
// PRECONDITION: buffer is non-empty and is all integers
// POSTCONDITON: returns a char array of the sum of buffer's digits
	int sum = 0;
	for (int i=0; i<strlen(buffer); i++) {
		if (isdigit(buffer[i]))  // since last element might be null terminator
			sum += buffer[i]-'0';
	}
	int n = log10(sum) + 1;
	char *numberArray = calloc(n+1, sizeof(char));
	for (int i=n-1; i>=0; --i, sum/=10) {
		numberArray[i] = (sum%10) + '0';
	}
	numberArray[n] = '\0';
	return numberArray;
}

char* getMessage(const char *buffer) {
// PRECONDITION: buffer is non-empty and is all integers
// POSTCONDITION: returns a char array representing each iterative sum of buffer's digits
	char *mssg = calloc(256, sizeof(char));
	char *tmpBuffer = calloc(256, sizeof(char));
	memcpy(tmpBuffer, buffer, strlen(buffer));
	while (strlen(tmpBuffer)>1) {
		strcat(mssg, "From server: ");
		strcat(mssg, getSum(tmpBuffer));
		strcat(mssg, "\n");
		memcpy(tmpBuffer, getSum(tmpBuffer), strlen(tmpBuffer));  // overwrites buffer with its sum
	}
	return mssg;
}

int main(int argc, char *argv[]) {
	struct sockaddr_in from;
	struct sockaddr_in server;
	socklen_t fromlen;
	char buff[256];

	//create socket
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi(argv[1]));
	bind(sock,(struct sockaddr *)&server,sizeof(server));  //bind socket to adress and port

	//length of sockaddr struct pointed to
	fromlen = sizeof(struct sockaddr_in);
	//get string from client, n now holds number of bytes in message
	
	while (true) {
		recvfrom(sock,buff,256,0,(struct sockaddr *)&from,&fromlen);
		if (!isNumber(buff)) {
			sendto(sock,"From server: Sorry, cannot compute!\n",256,0,(struct sockaddr *)&from,fromlen);
		} else {
			char *newBuffer = calloc(256, sizeof(char));
			newBuffer = getMessage(buff);
			bzero(buff,256);
			memcpy(buff, newBuffer, strlen(newBuffer));  // overwrites buffer with the message
			sendto(sock,buff,256,0,(struct sockaddr *)&from,fromlen);
		}
		bzero(buff,256);
	}

	close(sock);
	return 0;
}
