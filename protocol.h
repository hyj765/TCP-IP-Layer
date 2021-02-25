typedef struct ether_header
{
	u_int8_t dhost[6];
	u_int8_t shost[6];
	u_int16_t ether_type;
}Eth_header;



typedef struct ip_header
{
	uint8_t ip_hl:4;
	uint8_t ip_v:4;
	uint8_t ip_tos;
	uint16_t ip_len;
	uint16_t ip_id;
	uint16_t ip_off;
#define IP_RF 0x8000
#define IP_DF 0x4000
#define IP_MF 0x2000
#define IP_OFFMASK 0x1fff
	uint8_t ip_ttl;
	uint8_t ip_p;
	uint16_t ip_sum;
	struct in_addr ip_src,ip_dsc;
}ip;

typedef struct tcp_header
{
	uint16_t sport;
	uint16_t dport;
	uint32_t seq;
	uint32_t ack;
	uint8_t th_x2:4;
	uint8_t th_off:4;
	uint8_t th_flags;
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
	uint16_t th_win;
	uint16_t th_sum;
	uint16_t th_urp;
}TCP;
