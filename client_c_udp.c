// client_c_udp.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
   int sock;
   unsigned int length;
   struct sockaddr_in server, from;
   struct hostent *hp;
   char buffer[256];
   
   sock = socket(AF_INET, SOCK_DGRAM, 0);
   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);
   printf("Enter string: ");
   bzero(buffer,256);
   fgets(buffer,256,stdin);
   
   sendto(sock,buffer,strlen(buffer),0,(const struct sockaddr *)&server,length);
   recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);
   printf("%s",buffer);
   close(sock);
   return 0;
}
