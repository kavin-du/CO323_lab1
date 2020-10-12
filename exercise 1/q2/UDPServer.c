/* Sample UDP server */ 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <strings.h> 
#include <string.h>
#include <stdio.h> 

int main(int argc, char**argv) { 
	int sockfd,n; 
	struct sockaddr_in servaddr, cliaddr; 
	socklen_t len; 
	char mesg[1000];
	
	//char* banner = ""; 
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);  // return socket descripter
	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY); 
	servaddr.sin_port=htons(32000); 
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); 
	
	len = sizeof(cliaddr); 
	while(1){
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);		 
		mesg[n] = 0; 
		printf("Received: %s\n",mesg); 
		
		// sending same message to the client
		sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)); 
		
	}
	
	return 0; 
	
}
