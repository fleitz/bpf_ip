#!/bin/bash
clang -O2 -emit-llvm -I/usr/include -c tcbpf-sample.bpf.c -o - | llc-10 -march=bpf -filetype=obj -o tcbpf.o
# remove old qdisc
# change eno1 to whatever adapter, eg. eth0
sudo tc qdisc del dev eno1 root handle 1

sudo tc qdisc add dev eno1 root handle 1: prio 
sudo tc filter add dev eno1 parent 1: bpf obj tcbpf.o
sleep 5
sudo tc qdisc del dev eno1 root handle 1
