#ifndef LZY_NET_H
#define LZY_NET_H

#define IP_P	0x0800
#define UDP_P	17
#define IPv4	4

struct eth_head{
	unsigned char   dest[6];        /* destination eth addr */
        unsigned char   source[6];      /* source ether addr    */
        unsigned short  proto;          /* packet type ID field */
}__attribute__((packed));

typedef struct eth_head eth_h;

struct ip_head{
	unsigned int        ihl:4;	/*the lenth of ip_head*/
	unsigned int        version:4;	/*ipv4 or ipv6*/
	unsigned char       tos;	/*type of service*/
	unsigned short      tot_len;	/*the lenth of all data*/
	unsigned short      id;		/*small package id*/
	unsigned short      frag_off;	/*small package offset*/
	unsigned char       ttl;	/*period of aliving*/
	unsigned char       protocol;	/*the type of protocol*/
	unsigned short      check;	/*the sum of check of head*/
	unsigned int        saddr;	/*the ipaddr of source*/
	unsigned int        daddr;	/*the ipaddr of destation*/
}__attribute__((packed));

typedef struct ip_head ip_h;

struct udp_head{
	unsigned short source;		/*the port of source*/	
	unsigned short dest;		/*the port of destation*/
	unsigned short len;		/*the len of all data*/
	unsigned short check;		/*the sum of check*/
}__attribute__((packed));

typedef struct udp_head udp_h;

/*in dm9000.c*/
extern void eth_init(void);
extern int eth_recv(char *buf);
extern int eth_send(char *buf, unsigned short len);

/*in net.c*/
extern unsigned int htonl(unsigned int host);
extern unsigned short htons(unsigned short host);

/*in main*/
extern char recv_buf[2048];
extern char send_buf[2048];
extern char mac_source[6];
extern char mac_destation[6]; 
extern unsigned int ip_source;
extern unsigned int ip_destation;
extern unsigned short port_source;
extern unsigned short port_destation;

/*in string.c*/
void * memcpy(void * dest,const void *src,int count);
int strlen(const char * s);

#endif
