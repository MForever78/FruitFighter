#include "var.h"

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
    draw_picture(pic[AWEL], 0, 0);

    while(!stop){}

    setvect(8, old_8h);
    setvect(9, old_9h);
    destroy_pictures();
    closegraph();
    return 0;
}
