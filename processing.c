#include "processing.h"

void processpacket(unsigned char* buffer, int* icmp, int* tcp, int* udp, int* other){

	struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    switch (iph->protocol){

        case IPPROTO_ICMP:
            (*icmp)++;
            break;

        case IPPROTO_TCP:
            (*tcp)++;
            break;
         
        case IPPROTO_UDP:
            (*udp)++;
            break;
         
        default:
            other++;
            break;
    }
}