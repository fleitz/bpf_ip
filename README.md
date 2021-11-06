# bpf_ip

# Remember clock was off by ~3 hours, 7:26 PM was 4:53 PM don't trust the git commit logs
# Subtract an 15 for WSL, cannot use WSL as the kernel doesnt support modules, would need to compile custom kernel, use WD server instead.
# Sub 15 for Agent forwarding
# Sub 60 for hung NFS mount, ugh. Why is EVERYTHING broken today? Open ticket with OVH. Why does grub need to scan every mount anyway?
# 10:06 PM Headers FINALLY installed.
# 10:09 Why is python on this machine python2?
# 10:23 PM lets call it a night, deal with server tomorrow.
# 12:15 AM resume work
# 12:29 AM bcc does not build with clang-6 and clang-10 installed. It's going to be key for dev with bcc to make sure we have repeatable builds. Probably want to dockerize the build process.
#           also does not build with llvm-12 installed which is required for openjre.
# 12:42 AM building in docker, bcc has so many compiler warnings. Code smell? Look into exactly how hard it is to use libbpf directly from the kernel sources. Why isn't ebpf just an ARCH target for clang / llvm? Have a feeling there may be huge benefit from rethinking BCC from first principles. Modified C lang....? This reeks of "Any sufficiently complicated C or Fortran program contains an ad hoc, informally-specified, bug-ridden, slow implementation of half of Common Lisp."
# A spike on seeing what happens just using llvm-bpf might be worth it in the future.
# 1:05 AM building on docker, no kernel headers. Can't compile ip_ripper.bpf.c
# 1:36 AM blank ip_ripper.bpf.c now successfully fails to compile, instead of failing to compile because it can't find the kernel headers.





