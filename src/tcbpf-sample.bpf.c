#include <linux/bpf.h>
#include <linux/types.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/if_ether.h>
#include "bpf_helpers.h"
#include "bpf_endian.h"
#define INLINE __always_inline
#define skb_shorter(skb, len) ((void *)(long)(skb)->data + (len) > (void *)(long)skb->data_end)

#define ETH_IPV4_SIZE (14 + sizeof(struct iphdr))

static INLINE struct iphdr *get_iphdr(struct __sk_buff *skb)
{
	struct iphdr *ip = NULL;
	struct ethhdr *eth;

	if (skb_shorter(skb, ETH_IPV4_SIZE))
		goto out;

	eth = (void *)(long)skb->data;
	ip = (void *)(eth + 1);

out:
	return ip;
}

           SEC("classifier") 
           int cls_main(struct __sk_buff *skb)
           {
                // skb->local_ip4 is forbidden by bpf_skb_is_valid_access so we go digging in the packet data.
                struct iphdr* iphdr = get_iphdr(skb);
                if(iphdr == NULL){
                        return -1;
                }
                __u32 ip = 0;
                ip = bpf_ntohl(iphdr->saddr);
                char fmt[] = "IP IS: 0x%x\n";
                bpf_trace_printk(fmt, sizeof(fmt), ip);
                // bpf_printk("IP IS: %d\n", ip);
                return -1;
           }

           

           char __license[] SEC("license") = "GPL";