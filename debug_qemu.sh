#! /bin/bash
qemu-system-i386 -no-kvm -D qemu.log -s -kernel src/kernel &
gdb -x gdb.settings src/kernel
#ddd ddd --eval-command="" src/kernel &