#include "var.h"

int main()
{
    int driver=DETECT, mode=VESA_1024x768x24bit;
    initgraph(&driver, &mode, "");
    pictures = build_pic_from_bmp("bmp", pic);
    while(!stop){};
    set_timer_frequency(1193180/1000);
    old_8h = getvect(8);
    old_9h = getvect(9);
    setvect(8, int_8h);
    setvect(9, int_9h);
    install_tickvar(&game_time, 6400/_width, 0);
    install_tickvar(&retrace_count, 6400/_height, 32);

    clear_display();

    while(!stop){
/*        if (interface_changed) {
            prepare_display();
            draw_interface(interface);
            flip_display();
            interface_changed = 0;
        }

        if (interface == 0) {
            welcome_control();
            continue;
        }
        if (interface == 1) {
            need_draw = 0;
            while (prev_update_time < game_time) {
                round_move();
                prev_update_time++;
                need_draw = 1;
            }
            if (need_draw) { 
                prepare_display();
                draw_interface(1);
                draw_player(0, STILL);
                draw_player(1, STILL);
                if (shooting){
                    bullet_flying();
                    // interface = 0;
                    // interface_changed = 1;
                    continue;
                }
                if (exploding){
                    bullet_explode();
                    continue;
                }
                flip_display();
            }
            continue;
        }
        if (interface == 2) {
            help_control();
            continue;
        }*/
    }

    setvect(8, old_8h);
    setvect(9, old_9h);
    destroy_pictures();
    closegraph();
    return 0;
}
