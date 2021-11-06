#include <linux/bpf.h>
#include <linux/types.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/tcp.h>
#include <linux/if_ether.h>
#include "bpf_helpers.h"
#include "bpf_endian.h"
#define INLINE __always_inline
#define skb_shorter(skb, len) ((void *)(long)(skb)->data + (len) > (void *)(long)skb->data_end)

#define ETH_IPV4_SIZE (14 + sizeof(struct iphdr))
#define ETH_IPV6_SIZE (14 + sizeof(struct ipv6hdr))

static INLINE struct ipv6hdr *get_ipv6hdr(struct __sk_buff *skb)
{
	struct ipv6hdr *ip = NULL;
	struct ethhdr *eth;

	if (skb_shorter(skb, ETH_IPV6_SIZE))
		goto out;
        if(skb->protocol != 56710) // technically this means its a tcpv6 header, but we have TCP traffic so it works.
                goto out;

	eth = (void *)(long)skb->data;
	ip = (void *)(eth + 1);

out:
	return ip;
}


static INLINE struct iphdr *get_iphdr(struct __sk_buff *skb)
{
	struct iphdr *ip = NULL;
	struct ethhdr *eth;

	if (skb_shorter(skb, ETH_IPV4_SIZE))
		goto out;
        // Filter ipv6
        if(skb->protocol != 8) 
                goto out;

	eth = (void *)(long)skb->data;
	ip = (void *)(eth + 1);
        // There's nothing more important than family, unfortunately family is a forbidden field so we'll use protocol instead.
        // bpf_printk("Family: %d", skb->protocol);
out:
	return ip;
}

           SEC("classifier") 
           int cls_main(struct __sk_buff *skb)
           {
                // skb->local_ip4 is forbidden by bpf_skb_is_valid_access so we go digging in the packet data.
                struct iphdr* iphdr = get_iphdr(skb);
                bpf_printk("Interface: %d", skb->ifindex);
                if(iphdr != NULL){
                        __u32 ip = iphdr->saddr;
                        bpf_printk("IP IS: %pI4 (0x%x)\n", &ip, ip);
                        return -1;
                }
                struct ipv6hdr* ipv6hdr = get_ipv6hdr(skb);
                if(ipv6hdr != NULL){
                        bpf_printk("IP IS: %pI6", &ipv6hdr->saddr);
                        return -1;
                }
                return -1;
           }

           

           char __license[] SEC("license") = "GPL";