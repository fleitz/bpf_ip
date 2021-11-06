# bpf_ip
# eBPF Filter
https://github.com/fleitz/bpf_ip/blob/main/src/tcbpf-sample.bpf.c

# Notes
* Remember clock was off by ~3 hours, 7:26 PM was 4:53 PM don't trust the git commit logs
* Subtract an 15 for WSL, cannot use WSL as the kernel doesnt support modules, would need to compile custom kernel, use WD server instead.
* Sub 15 for Agent forwarding
* Sub 60 for hung NFS mount, ugh. Why is EVERYTHING broken today? Open ticket with OVH. Why does grub need to scan every mount anyway?
* 10:06 PM Headers FINALLY installed.
* 10:09 Why is python on this machine python2?
* 10:23 PM lets call it a night, deal with server tomorrow.

* 12:15 AM resume work

* 12:29 AM bcc does not build with clang-6 and clang-10 installed. It's going to be key for dev with bcc to make sure we have repeatable builds. Probably want to dockerize the build process.
*           also does not build with llvm-12 installed which is required for openjre.
* 12:42 AM building in docker, bcc has so many compiler warnings. Code smell? Look into exactly how hard it is to use libbpf directly from the kernel sources. Why isn't ebpf just an ARCH target for clang / llvm? Have a feeling there may be huge benefit from rethinking BCC from first principles. 
* 1:05 AM building on docker, no kernel headers. Can't compile ip_ripper.bpf.c
* 1:36 AM blank ip_ripper.bpf.c now successfully fails to compile, instead of failing to compile because it can't find the kernel headers.
* 1:36 AM stop working
* 1:55 AM resume work
* 2:22 AM there seems to be lots of complicated ways of calculating the offsets, lets just assume the packet starts at 0 and is an IP header.
* 2:45 AM looking through the iproute2 sources it looks like BCC is massively overcomplicating things. Lets write raw BPF and compile with clang. Starting print_ip.bpf.c
* 3:45 AM bcc is not designed to attach to 'tc', lets use the example program from tc and strace it to find out how it attaches to the kernel traffic controller. Also, XDP seems cool, it sounds like ebpf runs right on the network card / driver in some cases...
* 4:15 AM tc sets up the ebpf fd via sendmsg/recvmsg, dive deeper into this later, abandon all hope of using BCC.
* 4:49 AM copy a bunch of defines out of iproutes / bcc to get tcbpf-sample.bpf.c compiling, now it gets rejected by the verifier, checking if bpf_trace_printk is not allowed in classifiers? or maybe I'm using the wrong fmt.
* 5:47 AM not allowed to use skb->local_ip4. Why have it and then reject it? kernel tests point to another method. apparently we are deep enough in the network stack that the ip headers are just part of the skb 'data'.
* 6:03 AM didn't compile because I didn't check if the iphdr code returns null. errno seems so luxurious now.
* 6:59 AM code is not outputting the expected hex, the kernel test code says it works and iphdr->daddr is almost always 0x0 which is likely sockets listening on 0.0.0.0. Could be IPv6 packets?
* 7:10 AM finish notes, ideas for making this go quicker, copy all the packet data into a ringbuf and feed it into libpcap / wireshark somehow. voila, universal network packet inspector... with a GUI even... does the same thing as tcpdump / old school bpf. maybe borrow the tcpdump code for writing pcap / pcap-ng format files?
* 7:10 AM stop work
* 1:20 PM Do what I should have done at the start, run the latest and greatest kernel on the latest and greatest OS. Use %pI4 / %pI6 to print IPs in a human readable format. 
* 1:45 PM We are done.


