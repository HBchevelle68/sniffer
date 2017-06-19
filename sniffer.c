#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
//special for monitor mode
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

#include "processing.h"

#define MAXBUFF 65536


int main(int argc, char* argv[]){

	int rsfd;//raw socket file descriptor
	//struct sockaddr saddr;
	struct sockaddr_ll if_addr;
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

    //grab interface index
	struct ifreq interface;
	memset(&interface, 0, sizeof(struct ifreq));
	strncpy((char*)interface.ifr_name, argv[1], IF_NAMESIZE);
	if(ioctl(rsfd, SIOCGIFINDEX, &interface) < 0){
		perror("IF index ioctl error: ");
		exit(EXIT_FAILURE);
	}

	//bind the raw socket to the interface
	if_addr.sll_ifindex = interface.ifr_ifindex;
	if_addr.sll_family = AF_PACKET;
	if(bind(rsfd, (struct sockaddr*)&if_addr, sizeof(if_addr)) < 0){
		perror("Erro binding socket: ");
		exit(EXIT_FAILURE);
	}

	struct packet_mreq if_mreq;
	memset(&if_mreq, 0, sizeof(struct packet_mreq));
	if_mreq.mr_ifindex = interface.ifr_ifindex;
	if_mreq.mr_type = PACKET_MR_PROMISC;
	if_mreq.mr_alen = 6;
	if(setsockopt(rsfd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, (void*)&if_mreq, (socklen_t)sizeof(if_mreq)) < 0){
		perror("Error setting IF to promiscuous: ");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_ll addr;
	socklen_t addr_len = sizeof(addr);
	while(1){
	    if(recvfrom(rsfd, buffer, MAXBUFF, 0, (struct sockaddr*)&addr, (socklen_t *)&addr_len) < 0){
	        perror("Recvfrom error: ");
	        exit(EXIT_FAILURE);
	    }
	    processIP(buffer, &icmp, &tcp, &udp, &other);
	}
	
    free(buffer);
	return 0;
}