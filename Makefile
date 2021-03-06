# Makefile

CC = gcc
ARGS = -Wall

all: server_c_udp client_c_udp server_c_tcp client_c_tcp

server_c_udp: server_c_udp.c
	$(CC) $(ARGS) $^ -lm -o $@

client_c_udp: client_c_udp.c
	$(CC) $(ARGS) $^ -o $@

server_c_tcp: server_c_tcp.c
	$(CC) $(ARGS) $^ -lm -o $@

client_c_tcp: client_c_tcp.c
	$(CC) $(ARGS) $^ -o $@

clean:
	rm -f *.o server_c_udp *~
	rm -f *.o client_c_udp *~
	rm -f *.o server_c_tcp *~
	rm -f *.o client_c_tcp *~
