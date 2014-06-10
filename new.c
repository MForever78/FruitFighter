#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <io.h>

int pictures = 0;

volatile int frame_count, fps;
volatile word game_time, retrace_count;

RGB game_palette[256];
PIC pic[100];
byte key[256];

#define AWEL         0
#define BGAME        1
#define CPAUSE       2
#define DWIN1        3
#define DWIN2        4

int main()
{
    int driver=DETECT, mode=VESA_1024x768x8bit;
    word prev_update_time;
    initgraph(&driver, &mode, "");
    pictures = build_pic_from_bmp("bmp", pic);
    set_timer_frequency(1193180/1000);
    old_8h = getvect(8);
    old_9h = getvect(9);
    setvect(8, int_8h);
    setvect(9, int_9h);
    install_tickvar(&game_time, 6400/_width, 0);
    install_tickvar(&retrace_count, 6400/_height, 32);

    clear_display();
    draw_picture(pic[AWEL]);

    setvect(8, old_8h);
    setvect(9, old_9h);
    distroy_pictures();
    closegraph();
    return 0;
}
