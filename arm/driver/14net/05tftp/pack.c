#include "common.h"
#include "net.h"

int eth_pack(unsigned int length, unsigned short type)
{
	eth_h *eth = (void *)send_buf;

	memcpy(eth->dest, heth, 6);
	memcpy(eth->source, eeth, 6);
	eth->proto = htons(type);

	return eth_send((void *)send_buf, length + sizeof(eth_h));
}

int ip_pack(unsigned int length, unsigned char type)
{
	ip_h *ip = (void *)(send_buf + sizeof(eth_h));

	ip->ihl = sizeof(ip_h) >> 2;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = htons(sizeof(ip_h) + length);
	ip->id = 0;
	ip->frag_off = 0;
	ip->ttl = 255;
	ip->protocol = type;
	ip->check = 0;
	ip->saddr = htonl(eip);
	ip->daddr = htonl(hip);
	
	ip->check = cal_sum((void *)ip, sizeof(ip_h));

	return eth_pack(sizeof(ip_h) + length, 0x0800);
}

int udp_pack(unsigned int length, unsigned short port)
{
	udp_h *udp = (void *)(send_buf + sizeof(eth_h) + sizeof(ip_h));

	udp->source = (eport);
	udp->dest = (port);
	udp->len = htons(sizeof(udp_h) + length);
	udp->check = 0;

	return ip_pack(sizeof(udp_h) + length, 17);
}


