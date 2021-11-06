FROM ubuntu:20.04

RUN apt update
ARG DEBIAN_FRONTEND="noninteractive"
ENV TZ=America/Vancouver
RUN apt install -y bison build-essential cmake flex git libedit-dev libllvm7 llvm-7-dev libclang-7-dev python zlib1g-dev libelf-dev libfl-dev python3-distutils kmod
RUN git clone https://github.com/iovisor/bcc.git
RUN mkdir bcc/build
WORKDIR bcc/build
RUN cmake ..
RUN make
RUN make install
RUN cmake -DPYTHON_CMD=python3 .. # build python3 binding
WORKDIR src/python/
RUN make
RUN make install
WORKDIR /bpf
