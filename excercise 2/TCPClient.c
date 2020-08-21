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
	
	printf("Enter Argument: ");
	scanf("%s", consoleInput);    
    
	// sending console input
    sendto(sockfd, consoleInput, strlen(consoleInput), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    // ------ this is not the file name, same as server file name
    FILE* file = fopen("recieved_file.txt", "a+");
    if(file == NULL){
        printf("error writing file");
        exit(-1);
    }

	while(1){
		n = recvfrom(sockfd, buffer, 1000, 0, NULL, NULL);
		buffer[n] = 0;
		// printf("%s",buffer);
		
        if(strcmp(buffer, "finished") == 0) {
            break;
        }
		
		fputs(buffer, file);
		// fprintf(file, "%s", buffer);		
		
	}
    printf("writing to file is finished");
	fclose(file);
    return 0;
}