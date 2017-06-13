#ifndef PROCESSING_H
#define PROCESSING_H

#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h> 
#include <linux/if_ether.h>


void processpacket(unsigned char* buffer, int* icmp, int* tcp, int* udp, int* other);



#endif