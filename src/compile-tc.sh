#!/bin/bash
IFACE=${1:-enp0s3}
clang -O2 -emit-llvm -I/usr/include -c tcbpf-sample.bpf.c -o - | llc-13 -march=bpf -filetype=obj -o tcbpf.o
# remove old qdisc
# change eno1 to whatever adapter, eg. eth0
sudo tc qdisc del dev $IFACE root handle 1

sudo tc qdisc add dev $IFACE root handle 1: prio 
sudo tc filter add dev $IFACE parent 1: bpf obj tcbpf.o
sleep 5
sudo tc qdisc del dev $IFACE root handle 1
