SOURCES=kernel.o main.o common.o monitor.o
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -g
LDFLAGS=-m elf_i386 -Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<