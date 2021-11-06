int test(struct __sk_buff *skb) {
    __u32 src_ip;
    __u32 dst_ip;
    bpf_skb_load_bytes(skb,12, &src_ip, 4);
    bpf_skb_load_bytes(skb,16, &dst_ip, 4);
    bpf_trace_printk("src: %d dst: %d", src_ip, dst_ip);
    return -1;
}