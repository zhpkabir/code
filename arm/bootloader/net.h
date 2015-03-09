#ifndef LZY_NET_H
#define LZY_NET_H

struct ethhdr{
	unsigned char	dest[6];	/* destination eth addr	*/
	unsigned char	source[6];	/* source ether addr	*/
	unsigned short	proto;		/* packet type ID field	*/
} __attribute__((packed));

typedef struct ethhdr eth_h;

struct iphdr{
    unsigned int 	ihl:4;
    unsigned int 	version:4;
    unsigned char 	tos;
    unsigned short 	tot_len;
    unsigned short 	id;
    unsigned short 	frag_off;
    unsigned char 	ttl;
    unsigned char 	protocol;
    unsigned short 	check;
    unsigned int 	saddr;
    unsigned int 	daddr;
} __attribute__((packed));

typedef struct iphdr ip_h;

struct udphdr{
  unsigned short source;
  unsigned short dest;
  unsigned short len;
  unsigned short check;
} __attribute__((packed));

typedef struct udphdr udp_h;

//dm9000.c
extern void eth_init(void);
extern int eth_send(const char *buf, unsigned int length);
extern int eth_recv(char *buf);

/* net.c */
extern unsigned int swapl(unsigned int d);
extern unsigned short swaps(unsigned short d);
extern unsigned short cal_sum(unsigned short *buf, int len);

//pack.c
extern int eth_pack(unsigned int, unsigned short);
extern int ip_pack(unsigned int, unsigned char);
extern int udp_pack(unsigned int, unsigned short);
extern int icmp_pack(int seq);

//unpack.c
extern void eth_unpack(void);
extern void ip_unpack(void);
extern void udp_unpack(void);
extern void icmp_unpack(void);

//lib.c
extern void delay(int n);
extern unsigned int exp16(unsigned int n);
extern char * strcpy(char * dest,const char *src);
extern int strcmp(const char * cs,const char * ct);
extern int strlen(const char * s);
extern void * memset(void * s,int c,int count);
extern void * memcpy(void * dest,const void *src,int count);

//main.c
extern unsigned char heth[6];
extern unsigned char eeth[6];
extern unsigned int hip;
extern unsigned int eip;
extern unsigned short hport;
extern unsigned short eport;
extern unsigned char send_buf[2048];
extern unsigned char recv_buf[2048];

//tftp.c
extern void tftp_unpack(char *pkt, unsigned int length, unsigned short port);
extern void tftp_down(char *addr, char *filename);

#endif

