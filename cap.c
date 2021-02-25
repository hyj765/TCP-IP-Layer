#include<pcap.h>
#include<stdio.h>
#include"protocol.h"
#include<string.h>

typedef struct Iplenths
{
        uint8_t hl;
        uint16_t tl;
}iplen;


void EtherheaderPrint(const u_char *packet);
iplen IPheaderPrint(const u_char *packet);
int TCPheaderPrint(const u_char*packet);

int main(int argc, char* argv[])
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t * pcap;
	pcap = pcap_open_live(argv[1],BUFSIZ,1,1000,errbuf);
	if(pcap == NULL)
	{
		fprintf(stderr,"pcap_open_live(%s) error_nullptr",errbuf);
		return -1;
	}
	while(1)
	{
		struct pcap_pkthdr* header;
		const u_char* packet;
		int res = pcap_next_ex(pcap,&header,&packet);
		if(res == 0) continue;
		if(res == -1 || res == -2){
			printf("pcap_next_error : %s\n",pcap_geterr(pcap));
			break;
		}
		EtherheaderPrint(packet);
		packet += 14;
		iplen IPHL=IPheaderPrint(packet);	
		packet += IPHL.hl <<2; 
		int tlen=TCPheaderPrint(packet);
		packet += tlen;
		int Datalenth = IPHL.tl - IPHL.hl - tlen;
		printf("%u bytes capture\n",header->caplen);
	}
	pcap_close(pcap);

}

void EtherheaderPrint(const u_char *packet)
{
	Eth_header *eh;
	eh = (Eth_header*)packet;
	printf("=======ethernet=======\n");
	printf("Dst MAC %02x:%02x:%02x:%02x:%02x:%02x",eh->dhost[0],eh->dhost[1],eh->dhost[2],eh->dhost[3],eh->dhost[4],eh->dhost[5]);
	printf("Dst MAC %02x:%02x:%02x:%02x:%02x:%02x\n",eh->shost[0],eh->shost[1],eh->shost[2],eh->shost[3],eh->shost[4],eh->shost[5]);
}
iplen IPheaderPrint(const u_char *packet){
	ip*ipheader;
	ipheader = (ip*)packet;
	iplen rlen;
	char src_ip[1024];
	char dst_ip[1024];
	strcpy(src_ip,inet_ntoa(ipheader->ip_src));
	strcpy(dst_ip,inet_ntoa(ipheader->ip_dsc));
	rlen.hl = ipheader->ip_hl;
	rlen.tl = ipheader->ip_len;
	printf(" =================== IP HEADER =============\n");
	printf("SrcIP: %s\n",src_ip);
	printf("DstIP: %s\n",dst_ip);
	printf("IPheader: %d\n",ipheader->ip_hl);
	printf("IPHEADER TOTAL length : %d\n",htons(ipheader->ip_len));
	return rlen;
}
int TCPheaderPrint(const u_char* packet)
{
	TCP* tcpH;
	tcpH = (TCP*)packet;
	int TCPlen = tcpH->th_off << 2;
	printf("================== TCP HEADER ============\n");
	printf("Source Port: %d\n",ntohs(tcpH->sport));
	printf("Detination Port: %d\n",ntohs(tcpH->dport));
	return TCPlen;
}
