#include "common.h"
#include "net.h"

int eth_pack(unsigned int len, unsigned short protol)
{
	eth_h *p = (void *)(send_buf);

	memcpy(p->dest, mac_destation, 6);
	memcpy(p->source, mac_source, 6);
	p->proto = htons(protol);

	return eth_send((void *)send_buf, len + sizeof(eth_h));
}

int ip_pack(unsigned int len, char protol)
{
	ip_h *p = (void *)(send_buf + sizeof(eth_h));

	p->ihl = sizeof(ip_h) >> 2; 	 	/*the lenth of ip_head*/
        p->version = IPv4;  			/*ipv4 or ipv6*/
        p->tos = 0;	        		/*type of service*/
        p->tot_len = htons(len + sizeof(ip_h)); /*the lenth of all data*/
        p->id = 0;		        	/*small package id*/
        p->frag_off = 0;   			/*small package offset*/
        p->ttl = 255;        			/*period of aliving*/
        p->protocol = protol;   		/*the type of protocol*/
        p->check = 0;      			/*the sum of check*/
        p->saddr = htonl(ip_source);      	/*the ipaddr of source*/
        p->daddr = htonl(ip_destation); 	/*the ipaddr of destation*/

	p->check = cal_check((void *)p, sizeof(ip_h));

	return eth_pack(sizeof(ip_h) + len, IP_P);
}

int udp_pack(unsigned int len)
{
	udp_h *p = (void *)(send_buf + sizeof(eth_h) + sizeof(ip_h));

	p->source = htons(port_source);         /*the port of source*/
        p->dest = htons(port_destation);        /*the port of destation*/
        p->len = htons(sizeof(udp_h) + len);    /*the len of all data*/
        p->check = 0;           	 	/*the sum of check*/
	
	return ip_pack(sizeof(udp_h) + len, UDP_P);
}

