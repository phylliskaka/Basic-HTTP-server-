// Server side C program 
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

# define PORT 8080
int main(int argc, char const *argv[])
{   
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    //creating socket file descriptor 

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))<0){
        perror("cannot create socket");
        return 0;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("\n++++++++++ Waiting for new connection ++++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0 )
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        char buffer[30000] = {0};

        int valread = read( new_socket, buffer, 30000);
        printf("%s\n", buffer);
        if(valread < 0){
            printf("No bytes are there to read");
        }

        char *hellow = "Hello from the server"; 
        write(new_socket, hello, strlen(hello));
        printf("----------------------------Hello message sent--------------------------\n");

        close(new_socket);

    }

    return 0;

}