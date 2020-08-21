
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
	
	if(strcmp(buffer, "request") == 0){
		FILE* file = fopen("serverfile.txt", "r");  // read only
		if(!file){
			printf("file not found");
			exit(-1);
		}
		
		while(fgets(banner, 1000, file) != NULL ){
			sendto(connfd, banner, strlen(banner), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		}
		sendto(connfd, "finished", strlen(banner), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		fclose(file);
	}
	
    
    
    //printf("Received:%s\n", buffer);
   
    return 0;
}