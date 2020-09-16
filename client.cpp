#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

using namespace std;

int main(int argc, char const *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	const char *hello = "Hello Nishit, I got you";
	char buffer[1024] = {0};

	struct Certificate
	{
		char name[38];
		unsigned int hash;
	};

	Certificate c2;

	//Create socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	read(sock, &c2, sizeof(c2));
	cout << "name: " << c2.name << endl;
	cout << "hash: " << c2.hash << endl;
	send(sock, hello, strlen(hello), 0);
	printf("Hello message sent\n");
	read(sock, buffer, 1024);
	printf("Received: %s\n", buffer);
	return 0;
}
