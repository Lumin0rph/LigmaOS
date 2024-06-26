#include "vbe_graphics.h"

void VBE_plot_pixel_32bpp(u16 x,u16 y,u32 color){
    if ((x<=SCREEN_WIDTH) & (y<=SCREEN_HEIGHT)){
        u32 *pixel = (u32*)(fb + pitch * y + (bpp/8) * x);
        *pixel = color;
    }
}

void VBE_put_char(char c,u16 x,u16 y,u32 color){
    u8 row, col;
    for (row = 0; row < CHAR_WIDTH; row++) {
        for (col = 0; col < CHAR_HEIGHT; col++) {
            if (font8x8_basic[c+ASCII_BITMAP_SHIFT][row] & (1 << col)) {
                VBE_plot_pixel_32bpp(col+x,row+y,color);
            }
        }
    }
}

void VBE_put_char_2x(char c,u16 x,u16 y,u32 color){
    u8 row, col;
    for (row = 0; row < CHAR_WIDTH; row++) {
        for (col = 0; col < CHAR_HEIGHT; col++) {
            if (font8x8_basic[c+ASCII_BITMAP_SHIFT][row] & (1 << col)) {
                VBE_plot_pixel_32bpp(2*col+x,2*row+y,color);
                VBE_plot_pixel_32bpp(2*col+x+1,2*row+y,color);
                VBE_plot_pixel_32bpp(2*col+x,2*row+y+1,color);
                VBE_plot_pixel_32bpp(2*col+x+1,2*row+y+1,color);
            }
        }
    }
}

void VBE_delete_char(u16 x,u16 y){
    for (u8 row = 0; row < CHAR_WIDTH; row++) {
        for (u8 col = 0; col < CHAR_HEIGHT; col++) {
            VBE_plot_pixel_32bpp(col+x,row+y,BLACK);
        }
    }
}

void VBE_put_string(char * s,u16 x,u16 y,u32 color){
    u16  tmp_cursor_x=x;
    for (u16 i=0;i<strlen(s);i++){
        VBE_put_char(s[i],tmp_cursor_x,y,color);
        tmp_cursor_x+=8;
    }
}

void VBE_delete_char_2x(u16 x,u16 y){
    for (u8 row = 0; row < CHAR_WIDTH*2; row++) {
        for (u8 col = 0; col < CHAR_HEIGHT*2; col++) {
            VBE_plot_pixel_32bpp(col+x,row+y,BLACK);
        }
    }
}













