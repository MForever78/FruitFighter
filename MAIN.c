#include "var.h"

//game variables
int stop = 0;
int interface = 0;               //default welcome interface
int interface_changed = 1;       //default changed in order to draw welcome interface at the begining
int new_game = 1;                //default regard as a new game so that init functions can be trigered
int map[1025][769];        //0:filled, 1:empty
int aiming = 0;
int aiming_count = 0;
int shooting = 0;
int exploding = 0;
int explode_state = 0;
int explode_count = 0;
int need_draw = 0;
BULLET bullet;
BOUT bout;
PLAYER player[2];

//bmp variables
int pictures = 0;
PIC pic[100];


//key variables
int key[256];
int anykey = 0;


//timer variables
volatile int frame_count, fps;
volatile word game_time, retrace_count;
word prev_update_time;
InterruptFunctionPointer old_8h, old_9h;
volatile word *ptickvar[TICKVARS]={NULL};
volatile word max_ticks[TICKVARS]={0};
volatile word interval[TICKVARS]={0};
volatile word max_interval[TICKVARS]={0};

int main()
{
    int driver=DETECT, mode=VESA_1024x768x24bit;
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

    while(!stop){
        if (interface_changed) {
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
                if (shooting) {
                    bullet_flying();
                    prev_update_time++;
                    need_draw = 1;
                    continue;
                }
                if (exploding) {
                    bullet_explode();
                    prev_update_time++;
                    need_draw = 1;
                    continue;
                }
                round_move();
                prev_update_time++;
                need_draw = 1;
            }
            if (need_draw) { 
                prepare_display();
                draw_interface(1); 
                draw_players();
                draw_target();
                if (shooting){
                    draw_bullet();
                }
                if (exploding){
                    draw_explode();
                }
                flip_display();
            }
        }

        if (interface == 3) {
            pause_control();
        }

        if (interface == 2 || interface == 4 || interface == 5) {
            new_game = 1;
            help_control();
        }
    }

    setvect(8, old_8h);
    setvect(9, old_9h);
    destroy_pictures();
    closegraph();
    return 0;
}
