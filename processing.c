#include "processing.h"

void processIP(unsigned char* buffer, int* icmp, int* tcp, int* udp, int* other){

    struct in_addr src, dst;
	struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    src.s_addr = iph->saddr;
    dst.s_addr = iph->daddr;
    switch (iph->protocol){

        case IPPROTO_ICMP:
            printf("%-15s  =>  %-15s    ICMP\n", inet_ntoa(src), inet_ntoa(dst));
            (*icmp)++;
            break;

        case IPPROTO_TCP:
            printf("%-15s  =>  %-15s    TCP\n", inet_ntoa(src), inet_ntoa(dst));
            (*tcp)++;
            break;
         
        case IPPROTO_UDP:
            printf("%-15s  =>  %-15s    UDP\n", inet_ntoa(src), inet_ntoa(dst));
            (*udp)++;
            break;
         
        default:
            printf("%-15s  =>  %-15s    OTHER\n", inet_ntoa(src), inet_ntoa(dst));
            other++;
            break;
    }
    //inet_ntoa(*(struct in_addr*)&iph->saddr);
}