/*
 *  monitor.h Interface for reasons!
 */

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

extern u16int *video_memory;

extern s32int cursor_x, cursor_y;

// Write a char to the screen, like a boss !
void monitor_put(char c);

// Clear what we just wrote, because!
void monitor_clear();

// Output a null-terminated ASCII string, for science!
void monitor_write(char *c);

#endif