/*
 *  common.c Some wonderful functions for everybody!
 *  (You get a function, and YOU get a function!)
 */

#include "common.h"

// write a byte out to the port
void outb(u16int port, u8int value) {
    asm volatile ("outb %1, %0 " : : "dN" (port), "a" (value));
}

u8int inb(u16int port) {
    u8int ret;
    asm volatile ("inb %1, %0 " : "=a" (ret) : "dN" (port));
    return ret;
}

u16int inw(u16int port) {
    u16int ret;
    asm volatile ("inw %1, %0 " : "=a" (ret) : "dN" (port));
    return ret;
}