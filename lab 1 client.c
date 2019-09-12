#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


#define PORT 12000

int main (int argc, char const *argv[]){

	int sock = 0;
	long valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client! testmsg2";
	char buffer [1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	//Convert IPv4 and IPv6 addresses from text to binary form
	//Then store it in address provided
	//First parameter specifies IPv4 or IPv6
	//******QUESTION*******
	//how come 127.0.0.1 is server IP address even though used machine IP address as server IP address?
	//i'm aware that the python example set the server address to 127.0.0.1 
	if (inet_pton(AF_INET, "127.0.0.2", &serv_addr.sin_addr)<=0){
		printf("\nInvalid address/ Address not support \n");
		return -1;
	}

	//connects socket (first parameter) to address in serv_addr (second parameter)
	if (connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
		printf("\nConnection Failed. \n");
		return -1;
	}

	//only usable in connected state
	//same as write with no flags (last parameter) enabled. Flags specify certain network-related conditions
	//destination (first parameter), object to send (second parameter), length of object (third parameter), flags (fourth parameter)
	send(sock, hello, strlen(hello),0);
	printf("Hello message sent.\n");
	valread = read (sock,buffer,1024);
	printf("%s\n",buffer);

	return 0;
}
