# CS 176A: Homework 2
## Socket Programming in C

This program is used for communication between a client and server with one program using UDP and one using TCP. The client sends a string of numbers to the server and the server adds up the numbers and then sends them back to the client until there is only one digit left.


## Usage:
### Client Input/Output:
**Input:**  <br>
```
./client IP PORT 
```

Example: <br>
```
csil-machine2> ./client_c_udp 128.111.49.44 32000
Enter string: 123456789101234567891012345678910
```

**Output:**  <br>
```
From server: 138
From server: 12
From server: 3
csil-machine2>
```

### Server Input:
```
./server_c_udp PORT 
```

Example: <br>
```
csil-machine1> ./server_c_udp 32000 
```


