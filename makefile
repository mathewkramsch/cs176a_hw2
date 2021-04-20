# makefile

CC = gcc
ARGS = -Wall

all: server_udp client_udp server_tcp client_tcp

server_udp: server_udp.c
	$(CC) $(ARGS) -o $^ $@

client_udp: client_udp.c
	$(CC) $(ARGS) -o $^ $@

server_tcp: server_tcp.c
	$(CC) $(ARGS) -o $^ $@

client_tcp: client_tcp.c
	$(CC) $(ARGS) -o $^ $@

clean:
	rm -f *.o server_udp *~
	rm -f *.o client_udp *~
	rm -f *.o server_tcp *~
	rm -f *.o client_tcp *~
