#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/poll.h>
#include <arpa/inet.h>

#define NETMAP_WITH_LIBS 

#include <net/netmap_user.h>


#define PROTO_IP		0x0800
#define PROTO_ARP		0x0806


#define PROTO_UDP		17


//代表一个字节对齐
#pragma pack(1)

#define ETH_MAC_LENGTH		6
//以太网协议头 14字节
struct ethhdr {

	unsigned char h_dest[ETH_MAC_LENGTH];
	unsigned char h_source[ETH_MAC_LENGTH];
	unsigned short h_proto;

};
//每一层都加校验，可定位哪一层出现问题
//ip协议头
struct iphdr {
#if 0
unsigned char version:4
              length:4;
#endif
	unsigned char version;//ip协议版本4bit  4位首部长度  最大为15 15*4
	//表示ip协议头最大有60个字节
	unsigned char tos; // 8位服务类型
	unsigned short length;//16位总长度(字节数)  --  ip数据包的长度
	unsigned short id;  //16位标识  每个包都带有一个id号
	unsigned short flag_off; //
	unsigned char ttl;//生存时间  当包达到目的为0时直接丢弃
	unsigned char proto;//8位协议  tcp/ip
	unsigned short check;//2字节=16位首部校验和

	unsigned int saddr;//32位源地址
	unsigned int daddr;//32位目的地址

	//unsigned char opt[0];

};

//udp头
struct udphdr {

	unsigned short sport; //源端口
	unsigned short dport;  //目的端口
	unsigned short len; //长度  数据包的总长度
	unsigned short check;//校验 
};

struct udppkt {

	struct ethhdr eh; //以太网头
	struct iphdr ip; //ip头
	struct udphdr udp;//udp头

	unsigned char body[0];//柔性数组 可扩展
    //用户数据 可扩展
};

struct tcb{

    unsigned int saddr;
    unsigned int daddr;
    unsigned short sport;
    unsigned short dport;

    unsigned char status;//tcp的11个状态
};

struct arphdr {

	unsigned short h_type;
	unsigned short h_proto;
	unsigned char h_addrlen;
	unsigned char protolen;
	unsigned short oper;
	unsigned char smac[ETH_MAC_LENGTH];
	unsigned int sip;
	unsigned char dmac[ETH_MAC_LENGTH];
	unsigned int dip;

};

struct arppkt {

	struct ethhdr eh;
	struct arphdr arp;

};

int str2mac(char *mac, char *str) {

	char *p = str;
	unsigned char value = 0x0;
	int i = 0;

	while (p != '\0') {
		
		if (*p == ':') {
			mac[i++] = value;
			value = 0x0;
		} else {
			
			unsigned char temp = *p;
			if (temp <= '9' && temp >= '0') {
				temp -= '0';
			} else if (temp <= 'f' && temp >= 'a') {
				temp -= 'a';
				temp += 10;
			} else if (temp <= 'F' && temp >= 'A') {
				temp -= 'A';
				temp += 10;
			} else {	
				break;
			}
			value <<= 4;
			value |= temp;
		}
		p ++;
	}

	mac[i] = value;

	return 0;
}

void echo_arp_pkt(struct arppkt *arp, struct arppkt *arp_rt, char *hmac) {

	memcpy(arp_rt, arp, sizeof(struct arppkt));

	memcpy(arp_rt->eh.h_dest, arp->eh.h_source, ETH_MAC_LENGTH);
	str2mac(arp_rt->eh.h_source, hmac);
	arp_rt->eh.h_proto = arp->eh.h_proto;

	arp_rt->arp.h_addrlen = 6;
	arp_rt->arp.protolen = 4;
	arp_rt->arp.oper = htons(2);
	
	str2mac(arp_rt->arp.smac, hmac);
	arp_rt->arp.sip = arp->arp.dip;
	
	memcpy(arp_rt->arp.dmac, arp->arp.smac, ETH_MAC_LENGTH);
	arp_rt->arp.dip = arp->arp.sip;

}



int main() {
	struct nm_desc *nmr = nm_open("netmap:eth1", NULL, 0, NULL);
	if (nmr == NULL) {
		return -1;
	}
	struct pollfd pfd = {0};
	pfd.fd = nmr->fd;
	pfd.events = POLLIN;
	unsigned char *stream = NULL;
	struct nm_pkthdr h;
	while (1) {
		int ret = poll(&pfd, 1, -1);
		if (ret < 0) continue;
		if (pfd.revents & POLLIN) { // 当可读事件来的时候，就代表有数据来了
			stream = nm_nextpkt(nmr, &h);
			// 取出内存中的数据，内部没有分配空间，已经提前分配好了，将其取出转换成ethhdr以太网包
			struct ethhdr *eh = (struct ethhdr*)stream;
			printf("zjx proto: %x\n", ntohs(eh->h_proto));
			if (ntohs(eh->h_proto) == PROTO_IP) {  // 如果是IP协议，那么对应的处理
				struct udppkt *udp = (struct udppkt *)stream;
				printf("zjx1 udp->ip.proto: %d\n", udp->ip.proto);
				if (udp->ip.proto == PROTO_UDP) {
					int udp_length = ntohs(udp->udp.len);
                    //udp减去8个字节首部长度，拿到udp的数据，末尾加结束标志符
					udp->body[udp_length-8] = '\0'; //udp的数据包进行打印处理
					printf("zjx 3udp-> %s\n", udp->body);			
				}
			} else if (ntohs(eh->h_proto) == PROTO_ARP) {
				struct arppkt *arp = (struct arppkt*)stream;// 当协议是arp，那么进行arp处理
				struct arppkt arp_rt;
				if (arp->arp.dip == inet_addr("192.168.0.120")) {
					echo_arp_pkt(arp, &arp_rt, "00:0c:29:4a:f6:6c");
					nm_inject(nmr, &arp_rt, sizeof(struct arppkt));				
				}
				

			}
			
		}

	}

}



