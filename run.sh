#!/bin/bash
export KERNEL_VERSION=`uname -r`
docker-compose build
docker-compose run bpf /bpf/src/build.sh