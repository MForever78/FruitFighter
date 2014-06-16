#ifndef VAR_H
#define VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <io.h>
#include <math.h>

//game struct
typedef struct _PLAYER {
	int x, y, hp, face;
} PLAYER;

typedef struct _BOUT {
	int playerNum;
} BOUT;

typedef struct _BULLET {
	int x, y, xspeed, yspeed, angle, strenth, time, face;
} BULLET;

//keyboard definition
#define NUM_1		2
#define NUM_2		3
#define NUM_3		4
#define _SPACE		0x39

//game variables
extern int stop;
extern int interface;				//default welcome interface
extern int interface_changed;		//default changed in order to draw welcome interface at the begining
extern int new_game;				//default regard as a new game so that init functions can be trigered
extern int map[1025][769];		//1:filled, 0:empty
extern int aiming;
extern int shooting;
extern int exploding;
extern int explode_state;
extern int need_draw;
extern BULLET bullet;
extern BOUT bout;
extern PLAYER player[2];

#define STILL		0
#define MOVE 		1
#define GRAV		5
#define MAXSTRENTH	50
#define RAID		20
#define BASICHURT	100
#define PLAYEROFFSET	300


//bmp variables
extern int pictures;
extern PIC pic[100];
#define AWEL		0
#define BGAME		1
#define BMOUNT		2
#define BULLET0		3
#define CPAUSE		4
#define DWIN1		5
#define DWIN2		6
#define EXPLO0		12
#define HELP 		12
#define WORM00		7
#define WORM01 		8
#define WORM10 		9
#define WORM11		10


//key variables
extern int key[256];
extern int anykey;

//timer variables
extern volatile int frame_count, fps;
extern volatile word game_time, retrace_count;
extern word prev_update_time;
extern InterruptFunctionPointer old_8h, old_9h;
#define TICKVARS 10
extern volatile word *ptickvar[TICKVARS];
extern volatile word max_ticks[TICKVARS];
extern volatile word interval[TICKVARS];
extern volatile word max_interval[TICKVARS];

//bmp function
int  build_pic_from_bmp(char *dir, PIC ppic[]);
void build_this_pic(char *filename, PIC *p);
long get_file_len(FILE *fp);
void draw_picture(PIC p, int x, int y);
void clear_picture(struct picture *p);
void destroy_pictures(void);

//paint function
void draw_interface();
void draw_bullet();
void draw_explode();
void draw_player(int index, int moving);

//control function
void welcome_control();
void help_control();
void round_move();
void bullet_flying();
void bullet_explode();

//timer function
void interrupt int_8h(void);
int install_tickvar(volatile word *p, word minterval, word mticks);
void uninstall_tickvar(int i);

//display function
void clear_display(void);
void prepare_display(void);
void flip_display(void);

//key function
void interrupt int_9h(void);

#endif
