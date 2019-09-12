//tutorial used: https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>

#define PORT 12000
int main (int argc, char const *argv[]){

//****QUESTION*****
//when recompiling server code, sometimes get msg "Error in bind: Address already in use"
//but error goes away upon requesting immediate recompile. due to time delay in closing port or server?

	int server_fd, new_socket;
	long valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	char *hello = "Hello from server.";

	//Creating socket file descriptor
	//AF_INET refers to IPv4, the address family
	//SOCK_STREAM is the service needed by address family. IS "virtual circuit service" in this case
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){

		perror("In socket"); //prints "In socket" as error message (i think)
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET; //declares IPv4 usage
	address.sin_addr.s_addr = INADDR_ANY; //tells socket to use machine IP address
	printf("ip address: %d", address.sin_addr.s_addr);
	address.sin_port = htons (PORT); //"htons" converts bits from machine to host order.
									 // Related to big and little endian
	 								 // Also sets socket to certain port
	memset(address.sin_zero, '\0', sizeof address.sin_zero); //fills address.sin_zero with \0 or null char

	//error catchers
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){

		perror ("Error in bind");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 1)<0){ //server starts to listen for any connections to it
		perror("Error in listen");
		exit(EXIT_FAILURE);
	}

	while(1){
		printf("ip address check 2: %d", address.sin_addr.s_addr);
		printf("\n++++++++++++ Waiting for new connection ++++++++++++\n\n");
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){ //grabs first connection from listen() and creates new socket for connection between client and server
		//*****QUESTION*****
		//does accept() create a new socket? in example, it seems to redefine current socket. 			
			perror ("Error in accept");
			exit(EXIT_FAILURE);
		}

		char buffer[30000] = {0};
		valread = read (new_socket, buffer, 30000); //read is (where to read from, where to store what was read, how long of what i read)
		printf("%s\n", buffer);
		//STUDENT MODIFICATION
		//CAPITALIZATION
		int i = 0;
		while (buffer[i]){
			buffer[i] = toupper(buffer[i]);
			i++;	
		}
		printf("capitalized: %s",buffer);

		//write(new_socket, hello, strlen(hello));// write is (where to write to, where to write from, how long to write)
		write(new_socket, buffer, strlen(buffer));
		printf("\n++++++++++++ Hello message sent ++++++++++++\n");
		close(new_socket);
	}

	return 0;

}
