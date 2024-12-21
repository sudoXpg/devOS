#ifndef WELCOME_H
#define WELCOME_H

#include "../display/display.h"
#include "colors.h"
#include "../string/string.h"

void start(){
    cls(BLACK);
    const char* msg = "devOS - v1";
    int x=VGA_WIDTH/2 - strlen(msg)/2;
    int y=VGA_HEIGHT/2-5;
    for(int i=0;i<strlen(msg);i++){
        putchar(x,y,msg[i],WHITE);
        x++;
    }
}


#endif