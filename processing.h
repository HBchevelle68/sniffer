#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h> 
#include <linux/if_ether.h>


void processIP(unsigned char* buffer, int* icmp, int* tcp, int* udp, int* other);


//TO DO





#endif