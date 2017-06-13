#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h> 

#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h> 
#include <linux/if_ether.h>

#include "processing.h"

#define MAXBUFF 65536


int main(int argc, char* argv[]){

	int rsfd;//raw socket file descriptor
	struct sockaddr saddr;
	//struct ifreq ifr;
	unsigned char* buffer = malloc(MAXBUFF);
	memset(buffer, 0, MAXBUFF);
	int icmp = 0;
	int tcp = 0;
	int udp = 0;
	int other = 0;

    if ((rsfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
        perror("socket() raw socket creation failed ");
        exit(EXIT_FAILURE);
    }

	
	printf("here\n");
	unsigned int ssaddr = sizeof(saddr);
	for(int i =0; i<10000; i++){
	    if(recvfrom(rsfd, buffer, MAXBUFF, 0, &saddr, (socklen_t *)&ssaddr) < 0){
	        printf("Recvfrom error , failed to get packets\n");
	        return EXIT_FAILURE;
	    }
	    processpacket(buffer, &icmp, &tcp, &udp, &other);
	    printf("\rTCP : %d   UDP : %d   ICMP : %d   Others : %d\n",tcp,udp,icmp,other);
	}
	printf("%s",buffer);
    free(buffer);
	return 0;
}