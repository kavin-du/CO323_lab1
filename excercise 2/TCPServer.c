
/* Sample TCP server */ 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

int main(int argc, char **argv){
    int listenfd, connfd, n;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
    char banner[1000];
    char buffer[1000];        

    /* one socket is dedicated to listening */    
    listenfd = socket(AF_INET, SOCK_STREAM, 0); 
    
    /* initialize a sockaddr_in struct with our own address for binding the socket */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(32000); 
    
    /* binding */
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 0);
    clilen = sizeof(cliaddr);                                                   
    
    /* accept the client with a different socket.  */
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);            // the uninitialized cliaddr variable is filled in with the
    
    n = recvfrom(connfd, buffer, 1000, 0, (struct sockaddr *)&cliaddr, &clilen); // information of the client by recvfrom function
    buffer[n] = 0;
            
    
    // sending the file size to the client
    char file_size[] = "1239";
	sendto(connfd, file_size, strlen(file_size), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
	
	if(strcmp(buffer, "request") == 0){
		FILE* file = fopen("serverfile.txt", "r");  // read only
		if(!file){
			printf("file not found");
			exit(-1);
		}
		
		// reading 1000 bytes at a time and sending to client
		int count = 0;
		int total_count = 0; // to track the total size of the file
		int character = getc(file); // using getc() method to read file
		
		while(character != EOF){
			// read 1000 bytes at a time and send to client
			while(count < 1000 && total_count < atoi(file_size)){
				banner[count++] = (char)character;
				character = getc(file);
				total_count++;
			}
			sendto(connfd, banner, 1000, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
			count = 0;	
			memset(banner, 0, 1000); // resetting char array each time		
		}	
		fclose(file); // close the file
	}
   
    return 0;
}
