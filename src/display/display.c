#include "display.h"

uint16_t *videomem ;
uint16_t screen_row;
uint16_t screen_col;

uint16_t tovideomem(char c, char color){
    return ((color<<8) | c) ;           // color first due to small endian !
}

void putchar(int x, int y, char c, char color){
    videomem[(y*VGA_WIDTH)+x]=tovideomem(c,color);    
}

void writechar(char c){
    if(c =='\n'){   
        while(screen_col<VGA_WIDTH){
            putchar(screen_col,screen_row,' ',BLACK);
            screen_col++;
        }
        screen_col=0;
        screen_row++;
        return;
    }
    putchar(screen_col,screen_row,c,WHITE);     // default white
    screen_col++;
    if(screen_col>=VGA_WIDTH){
        screen_row++;
        screen_col=0;
    }

}

void terminal_init(){
    videomem = (uint16_t *)VIDEO_MEMORY_START;
    screen_row = 0;
    screen_col = 0;
    for(int y=0;y<VGA_HEIGHT;y++){
        for(int x=0;x<VGA_WIDTH;x++){
            putchar(x,y,' ',BLACK);
        }
    }
}   



void write(const char* str, size_t len){
    for(int i=0;i<len;i++){
        writechar(str[i]);
    }
}

void print(const char *str){
    write(str,strlen(str));
}