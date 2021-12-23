#include <stdio.h>
#include <unistd.h>
#include <netinet/ether.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <string.h>
#include <sys/socket.h>


#define BUFFER_SIZE 65536 //max ip size
#define IP_LEN 16

void print_icmp_packet(unsigned char* , int);

int main( int argc, char* argv[]){

ssize_t data_size;
uint8_t packet_buffer[BUFFER_SIZE];


// create raw socket
int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

if (sock == -1){
    perror("sock create error");
    return -1;
}

//Turn on the promiscouse mode
struct packet_mreq mr;
mr.mr_type = PACKET_MR_PROMISC;
setsockopt(sock, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr));


char buff[IP_MAXPACKET];    // contains the packet inside
while (1){
    // this while loop performs as a listener for incoming packets of all sorts
    // of packets
    // and we are printing only the packets with type ICMP
    // in the function 'prin_icmp_packet'
    bzero(buff, IP_MAXPACKET);  //initiallizating of the buffer
    int data_size = recvfrom(sock, buff,ETH_FRAME_LEN, 0, NULL,NULL);
    print_icmp_packet(buff, data_size);

    }
    close(sock);    // closing the socket
    return 0;
}

void print_icmp_packet(unsigned char* buffer, int size){
    struct iphdr *iph = (struct iphdr*)(buffer + ETH_HLEN);
    // this is a critical condition to check wether a packet is
    // ICMP type and if so --> print the required details
    if(iph->protocol == IPPROTO_ICMP){
	unsigned short iphdrlen = iph->ihl * 4;
	struct icmphdr *icmph = (struct icmphdr *)(buffer +ETH_HLEN+ iphdrlen);

    unsigned int type = (unsigned int)(icmph->type);
    if (type>=0 && type <11){
        struct sockaddr_in source, dest;
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = iph->saddr;
        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = iph->daddr;
        
        // since we are sending and recieving IPv4 packets
        // and considering the structer of such packets
        // we found the exact location of the source and destination IP
        // inside the buffer
        // [26..29] --> SOURCE
        // [30..33] --> DESTINATION
        
        // Source addr
        printf("\n Source -->%d.%d.%d.%d",  (unsigned char)(buffer[26]),
                                            (unsigned char)(buffer[27]),
                                            (unsigned char)(buffer[28]),
                                            (unsigned char)(buffer[29]));
        // Destination addr
        printf("\n Destination -->%d.%d.%d.%d", (unsigned char)(buffer[30]),
                                                (unsigned char)(buffer[31]),
                                                (unsigned char)(buffer[32]),
                                                (unsigned char)(buffer[33]));
        
        printf("\n ICMP Type: %d  \n ICMP Code: %d \n" ,(unsigned int)(icmph->type), (unsigned int)(icmph->code));
        
    }

    }
}