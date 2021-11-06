#include <linux/version.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <cassert>
#include <fstream>

#include <bcc/BPF.h>

using namespace std;

string load_bpf(string path){
    ifstream t(path);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 
    return path;
}

 
int main(){
    printf("BPF linked\n");
    ebpf::BPF bpf;
    ebpf::StatusTuple res(0);
    string ip_ripper = load_bpf("/bpf/src/ip_ripper.bpf.c"); // super-hacky, but works for these docker builds.
    res = bpf.init(ip_ripper);
    assert(res.code() == 0);
    int prog_fd;
    res = bpf.load_func("test", BPF_PROG_TYPE_CGROUP_SKB, prog_fd);
    assert(res.code() == 0);
    return 0;
}



