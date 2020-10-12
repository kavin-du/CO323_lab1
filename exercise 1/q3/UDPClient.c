/* Sample UDP client */ 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 

int main(int argc, char **argv){

    int sockfd, n;
    struct sockaddr_in servaddr;
    char sendline[1000] = "";
    char recvline[1000];

    if (argc != 2)
    {
        printf("usage:  ./%s <IP address>\n", argv[0]);
        return -1;
    }
    
    int num_of_sentences;
    printf("Enter number of sentences: ");
    scanf("%d", &num_of_sentences);
    sprintf(sendline, "%d", num_of_sentences);
    sendline[1000] = 0;
    
    // -------------------------------------------------------
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(32000);
    // ---------------------------------------------------------

    // send the number of sentences
    sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    // receive ack
    n = recvfrom(sockfd, recvline, 10000, 0, NULL, NULL);
    recvline[n] = 0;
    printf("Acknowledement is: %s\n", recvline);

    // taking user input
    for(int i=0; i<num_of_sentences; i++){
        scanf("\n");
        scanf("%[^\n]%*c", sendline);
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));       
    }

    // printing server output
    for(int i=0; i<num_of_sentences; i++){
        n = recvfrom(sockfd, recvline, 10000, 0, NULL, NULL);
        recvline[n] = 0;
        printf("Received: %s\n", recvline);
    }
    
    return 0;
}
