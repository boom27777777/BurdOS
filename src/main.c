/*
 *  main.c The C kernel entry point for BurdOS!
 */

int main(struct multiboot *mboot_ptr) {
    #include "common.h"
    #include "monitor.h"
    monitor_clear();
    monitor_write("Hello World! Big brother is watching");  
    return 0;
}