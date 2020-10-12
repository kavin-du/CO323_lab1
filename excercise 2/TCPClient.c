/* Sample TCP client */ 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

int main(int argc, char **argv){
    int sockfd, n;
    struct sockaddr_in servaddr;
    char consoleInput[20]; // take user input from console
    char buffer[1000];
    
    if (argc != 2)
    {
        printf("usage:  ./%s <IP address>\n", argv[0]);
        return -1;
    }   

    /* socket to connect */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    
    /* IP address information of the server to connect to */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(32000);
	
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	printf("Enter 'request' to receive the file: ");
	scanf("%s", consoleInput);    
    
	// sending console input
    sendto(sockfd, consoleInput, strlen(consoleInput), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    // receive the file size
    n = recvfrom(sockfd, buffer, 1000, 0, NULL, NULL);
	buffer[n] = 0;
	printf("file size: %s bytes\n", buffer); 
    
    int file_size = 0;
    sscanf(buffer, "%d", &file_size);
    
    // open destination file to write
    FILE* file = fopen("received_file.txt", "a+");
    if(file == NULL){
        printf("error writing file");
        exit(-1);
    }
	
	int temp = 0; // to track the file size
	
	while(temp <= file_size){
		n = recvfrom(sockfd, buffer, 1000, 0, NULL, NULL);
		buffer[n] = 0;
       		
		// write to the file
		fputs(buffer, file);	
		temp += 1000; // loop for next 1000 bytes
	}
    printf("writing to file is finished\n");
	fclose(file); // closing the file
    return 0;
}
