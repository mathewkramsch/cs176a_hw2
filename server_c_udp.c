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

int charlen(char b[]){
    //get length of buff characters
int s = 0;
for(int i = 0;i < 128;i++){
    if(b[i]=='\0'){
        return s;
    }
    s++;
}
return s;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{


int newlen;
struct sockaddr_in from;
struct sockaddr_in server;
socklen_t fromlen;
char buff[128];


if (argc < 2) {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(0);
}

//create socket
int sock = socket(AF_INET,SOCK_DGRAM,0);
server.sin_family = AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(atoi(argv[1]));
//bind socket to adress and port
if (bind(sock,(struct sockaddr *)&server,sizeof(server))<0) 
       error("binding");

//length of sockaddr struct pointed to
fromlen = sizeof(struct sockaddr_in);
//get string from client, n now holds number of bytes in message
int n = recvfrom(sock,buff,128,0,(struct sockaddr *)&from,&fromlen);
if (n < 0) error("recvfrom");
//check if string has all numbers
//printf("nhello");

for(int i = 0; i < n-1; i++){
    if(!isdigit(buff[i])){
         n = sendto(sock,"Sorry,cannot compute!\n",23,0,(struct sockaddr *)&from, fromlen);
        return 0;
    }
}

int len = charlen(buff);
newlen=len;


printf("newlen,%i",newlen);
while(newlen>2){
char ar[128] = {'0'};
int sum = 0;


for(int i = 0; i < newlen - 1  ; i++){
     //add up all numbers
    sum = sum + buff[i]-'0';
    //printf("sum,%i",sum);
 }

// somehow put final sum result back into buffer
//printf("buff %i",buff[0]-'0');
sprintf(ar, "%d", sum);
for(int i =0;i<128;i++){
    buff[i]=ar[i];
}
//printf("buff %i",buff[0]-'0');
//send sum to client
n = sendto(sock,buff,128,0,(struct sockaddr *)&from,fromlen);
newlen = strlen(buff);
printf("newlen,%i",newlen);
}


//when theres only one digit left send it to socket and close connection
    if(newlen == 2){
        n = sendto(sock,buff,128,0,(struct sockaddr *)&from, fromlen);
        printf("newlen2:");
        return 0;
    }





return 0;
}