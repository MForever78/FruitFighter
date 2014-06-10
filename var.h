#ifndef VAR_H
#define VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <io.h>

//game variables
int stop = 0;

//bmp variables
int pictures = 0;
RGB game_palette[256];
PIC pic[100];
#define AWEL         0
#define BGAME        1
#define CPAUSE       2
#define DWIN1        3
#define DWIN2        4

//key variables
int key[256];

//timer variables
volatile int frame_count, fps;
volatile word game_time, retrace_count;

InterruptFunctionPointer old_8h, old_9h;
#define TICKVARS 10
volatile word *ptickvar[TICKVARS]={NULL};
volatile word max_ticks[TICKVARS]={0};
volatile word interval[TICKVARS]={0};
volatile word max_interval[TICKVARS]={0};

//bmp function
int  build_pic_from_bmp(char *dir, PIC ppic[]);
void build_this_pic(char *filename, PIC *p);
long get_file_len(FILE *fp);
void get_palette_from_bmp(char *filename, RGB palette[]);
void set_palette(RGB palette[]);
void draw_picture(PIC p, int x, int y);
void clear_picture(struct picture *p);
struct picture * build_mask_from_pic(struct picture *p);
void destroy_pictures(void);
struct picture * create_picture(int w, int h);

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
