;;kernel.asm
;;Welcome to the main assembly file of BurdOS, it doesn't do a damn thing 
;;but for the moment, we're ok with that

MBOOT_PAGE_ALIGN    equ 1<<0    ; Loading kernel modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Kernel memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ;Magic, seriously
; NOTE: Not using MBOOT_AOUT_KLUDGE, meaning that grub won't pass us 
; a symbol table
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]                       ; All instructions from here on out shall
                                ; be no more then 32 bits!

[GLOBAL mboot]                  ; Make 'mboot' avalible to C code
[EXTERN code]                   ; Start of the '.text' section
[EXTERN bss]                    ; Start of the '.bss' section
[EXTERN end]                    ; End of the last loadable section

mboot:
    dd MBOOT_HEADER_MAGIC       ; We know you're watching grub
    dd MBOOT_HEADER_FLAGS       ; And here be yer settings!
    dd MBOOT_CHECKSUM           ; And a checksum for good measure!

    dd mboot                    ; Setting location vars
    dd code
    dd bss
    dd end
    dd start

[GLOBAL start]
[EXTERN main]

start:
    push ebx                    ; Load multiboot header location for main()
    
    cli                         ; Disable interrupts
    call main                   ; Calling out main function
    jmp $                       ; Enter an infinite loop to stop the processor
                                ; executing whatever is left in memory
                                ; after the kernel is done with it's bi'ness