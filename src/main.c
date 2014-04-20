/*
 *  main.c The C kernel entry point for BurdOS!
 */

void main(struct multiboot *mboot_ptr) {
    #include "common.h"
    #include "monitor.h"
    const char src[50] = "Hello World! Big brother is watching!";
    char dest[50];
    memcpy(dest, src, strlen(src));
    memset(dest, 'F', strlen(dest));
    monitor_clear();
    monitor_write(dest);  
}
