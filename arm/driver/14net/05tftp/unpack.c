#include "common.h"
#include "net.h"

void eth_unpack(void)
{
	eth_h *eth = (void *)recv_buf;

#ifdef DEBUG
	printf("eth_unpack..., %02x:%02x:%02x:%02x:%02x:%02x\n",
			eth->dest[0],
			eth->dest[1],
			eth->dest[2],
			eth->dest[3],
			eth->dest[4],
			eth->dest[5]
			);
#endif

	if(memcmp(eth->dest, eeth, 6) != 0)
		return;

	switch(htons(eth->proto)){
		case 0x0800:
			ip_unpack();
//		csae ARP
//			arp_flag = 0;
//			memcpy(heth, xxx->yyy, 6);
			break;
	}
}

void ip_unpack(void)
{
	ip_h *ip = (void *)(recv_buf + sizeof(eth_h));

#ifdef DEBUG
	printf("ip_unpack...\n");
#endif

	if(htonl(ip->daddr) != eip)
		return;

	unsigned short ck_sum = ip->check;
	ip->check = 0;

	if(ck_sum != cal_sum((void *)ip, sizeof(ip_h)));
		/*do some thing*/
	
	switch(ip->protocol){
		case 17:
			udp_unpack();
//		case TCP:
			break;
	}
}

void udp_unpack(void)
{
	udp_h *udp = (void *)(recv_buf + sizeof(eth_h) + sizeof(ip_h));
	
#ifdef DEBUG
	printf("udp_unpack...\n");
#endif

	if((udp->dest) != eport)
		return;

			//--->tftp	//tftp
	tftp_unpack((void *)(udp + 1), htons(udp->len) - sizeof(udp_h), udp->source);//source = 69
}


