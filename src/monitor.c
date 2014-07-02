/*
 *  monitor.c The Display is about to get real (values... hopefully)
 */

#include "monitor.h"

u16int i;
u16int *video_memory = (u16int* ) 0xb8000;
s32int cursor_x = 0, cursor_y = 0;

// Update you hardware cursor!
static void move_cursor() {
    u16int cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);                    // VGA controler, prepare yourself
    outb(0x3D5, cursorLocation >> 8);   // Oh you don't like 16 bit values
    outb(0x3D4, 15);                    // So be it, we'll be back
    outb(0x3D5, cursorLocation);        // And in greater numbers!
}

// Text scrolling, almost like going back in time
static void scroll() {
    u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    if (cursor_y >= 25) {
        // Shifting everything up by 80 chars 
        for (i = 0*80; i < 24*80; i++) {
            video_memory[i] = video_memory[i + 80];
        }
        // Setting the new line to blank
        for (i = 24*80; i < 25*80; i++) {
            video_memory[i] = blank;
        }
        // And finally setting the cursor to the new line
        cursor_y = 24;
    }
}

// Let's see if we can get the screen to listen
void monitor_put(char c) {
    u8int backColor = 0;    // background: black
    u8int foreColor = 15;   // foregorund: white

    u8int attributeByte = (backColor << 4) | (foreColor & 0x0F);
    u16int attribute = attributeByte << 8;
    u16int *location;
    switch (c) {
        case 0x08: // Backspace!
            if (cursor_x) {
                cursor_x-=2;
            }
            break;
        case 0x09: // Tabs, too many tabs
            cursor_x = (cursor_x + 8) & ~(8 - 1);
            break;
        case '\r': // Return? I never left!
            cursor_x = 0;
            break;
        case '\n': // Newline, Oldline, ???, profit!
            cursor_x = 0;
            cursor_y++;
            break;
        default: // Handle all other characters here!
            if (c >= ' ') {
                location = video_memory + (cursor_y * 80 + cursor_x);
                *location = c | attribute;
                cursor_x++;
            }
            break;
    }
    // I've got nothing
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }
    // Scroll if need be
    scroll();
    // reposition the cursor
    move_cursor();
}
// Clears the monitor, in theory anyways
void monitor_clear() {
    u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    for (i = 0; i < 80*25; i++) {
        video_memory[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}
// Now watch us handle strings! 
void monitor_write(char *c) {
    i = 0;
    while (c[i]) {
        monitor_put(c[i++]);
    }
    scroll();
}
