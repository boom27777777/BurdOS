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

// Super simple memcpy, could be faster
void *memcpy(void *dest, const void *src, u16int count) {
    
    void *ret = dest;

    while (count--) {
        *(u8int *)dest = *(u8int *)src;
        dest = (u8int *)dest + 1;
        src = (u8int *)src + 1;
    }
    return ret;
}

/* Stripped down Gcc 32bit implmentation (http://goo.gl/B48kO),
   /should/ be pretty shwanky. */
u16int strlen(str) 
        const char *str;
    {
    // "Memory is memory is memory" -David
    const char *char_ptr; 
    const unsigned long int *longword_prt;
    unsigned long int longword, magic_bits, himagic, lomagic;

    // Looking for a char on a long word boundry
    for (char_ptr = str; ((unsigned long int) char_ptr 
        & (sizeof (longword) - 1)) != 0;
        ++char_ptr) {
        // if we come to the Null Governator before that, just return
        if (*char_ptr == '\0') {
            return char_ptr - str;
        }
    }
    // Casting the current position in the sting to a long word pointer
    longword_prt = (unsigned long int *) char_ptr;

    /* Now this is some magic that the Gcc guy's came up with, but this
       value has some special binary features that will let us find null
       chars within the bounds of a long word. Check their source, they 
       have a great explanation*/
    magic_bits = 0x7efefeffL;
    himagic = 0x80808080L;
    lomagic = 0x01010101L;

    for (;;) {
        longword = *longword_prt++;

        if (
#if 0
    (((longword + magic_bits) ^ ~longword) & ~magic_bits)
#else 
    ((longword - lomagic) & himagic)
#endif
        != 0) {
            /* grabbing the long word we're on, and checking the chars
               for the Null Governator */
            const char *cp = (const char *) (longword_prt - 1);

            if (cp[0] == 0) {
                return cp - str;
            }
            if (cp[1] == 0) {
                return cp - str + 1; 
            }
            if (cp[2] == 0) {
                return cp - str + 2;
            }
            if (cp[3] == 0) {
                return cp - str + 3;
            }

        }
    }

}

// Super simple memset, once again, could be faster.
void *memset(void *str, int val, u16int count) {
    unsigned char *char_ptr = str;

    while (count--) {
        *char_ptr++ = (unsigned char)val;
    }
    return str;
}