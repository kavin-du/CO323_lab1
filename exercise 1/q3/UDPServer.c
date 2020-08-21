/* Sample UDP server */ 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <strings.h> 
#include <string.h>
#include <stdio.h> 
#include <ctype.h>

int main(int argc, char**argv) { 
	int sockfd,n; 
	struct sockaddr_in servaddr, cliaddr; 
	socklen_t len; 
	char mesg[1000];

	//char* banner = ""; 
	int num_of_sentences = 0; // taken from the client
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);  // return socket descripter
	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY); 
	servaddr.sin_port=htons(32000); 
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); 
	
	len = sizeof(cliaddr); 
	
	// recieve num of sentences
	n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);		 
	mesg[n] = 0; 
	sscanf(mesg, "%d", &num_of_sentences);

	// sending acknowledgement if > 0
	sendto(sockfd,"ack",3,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)); 
	
	for(int i=0; i<num_of_sentences; i++){
		// receive message
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);		 
		mesg[n] = 0;
		
		// capitalize
		char capitalized[1000];
		int j=0;
		while(mesg[j]){
			capitalized[j] = toupper(mesg[j]);
			j++;
		}
		capitalized[n] = 0;

		// send to client
		sendto(sockfd,capitalized,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)); 

	}
	//sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)); 
	
	//printf("Received: %s\n",mesg); 	
	
	return 0; 
	
}
