/* Sample UDP server */ 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <strings.h> 
#include <string.h> 
#include <stdio.h> 
#include <time.h>
#include <unistd.h>

int main(int argc, char**argv) { 
	
	int sockfd, n; 
	struct sockaddr_in servaddr, cliaddr; 
	socklen_t len; 
	char mesg[1000];
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);  // return socket descripter
	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY); 
	servaddr.sin_port=htons(32000); 
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); 
	
	len = sizeof(cliaddr); 
	n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len); 
	mesg[n] = 0; 
	printf("%s\n", mesg); // message from the client
	
	while(1){
		time_t t;
		time(&t);
		char day[10], month[10], date[10], time[10], year[10];
		
		/* 
			note: 
			ctime() returns time in this format ->  Www Mmm dd hh:mm:ss yyyy
			we need only the hh:mm:ss part
			sscanf used to extract only the time part from the string		
		*/
		
		sscanf(ctime(&t), "%s %s %s %s %s", day, month, date, time, year);
		
		sleep(1); // delay for one second
		// sending the time part from the string
		sendto(sockfd,time,10,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)); 
		
	}

	return 0; 
	
}
