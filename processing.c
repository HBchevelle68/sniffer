#include "processing.h"

void processIP(unsigned char* buffer, int* icmp, int* tcp, int* udp, int* other){

    unsigned char MAC[6] = {0xA4, 0xB8, 0x05, 0xD3, 0x73, 0xBC};
    struct in_addr src, dst;
    struct ethhdr* eth = (struct ethhdr*)buffer; 
	struct iphdr* iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));

    if(strncmp(eth->h_source, MAC, ETH_ALEN) != 0 ){
        int i = 0;
        for(;i < ETH_ALEN-1; i++)
            printf("%x:", eth->h_source[i]);
        printf("%x\n", eth->h_source[i]);
    }

    src.s_addr = iph->saddr;
    dst.s_addr = iph->daddr;
    switch (iph->protocol){

        case IPPROTO_ICMP:
            //printf("%-15s  =>  %-15s    ICMP\n", inet_ntoa(src), inet_ntoa(dst));
            (*icmp)++;
            break;

        case IPPROTO_TCP:
            //printf("%-15s  =>  %-15s    TCP\n", inet_ntoa(src), inet_ntoa(dst));
            (*tcp)++;
            break;
         
        case IPPROTO_UDP:
            //printf("%-15s  =>  %-15s    UDP\n", inet_ntoa(src), inet_ntoa(dst));
            (*udp)++;
            break;
         
        default:
            //printf("%-15s  =>  %-15s    OTHER\n", inet_ntoa(src), inet_ntoa(dst));
            (*other)++;
            break;
    }
    //inet_ntoa(*(struct in_addr*)&iph->saddr);
}