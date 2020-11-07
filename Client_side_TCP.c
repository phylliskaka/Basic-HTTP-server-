// Client side C program 
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

# define PORT 8080
int main(int argc, char const *argv[])
{   
    int sock = 0; long valread;
    struct sockaddr_in server_addr;
    char *hello = "Hello from client"; 
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        printf("\n Socket creation error");       
        return -1;
    }

    memset(&server_addr,  '0', sizeof server_addr);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 address from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read( sock, buffer, 1024);
    printf("%s\n", buffer);
    return 0;

}