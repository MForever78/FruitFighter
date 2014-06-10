#include "var.h"

void draw_interface(int interface)
{
	clear_display();
	switch (interface) {
		case 0:	//welcome interface
			set_palette(game_palette[AWEL]);
			draw_picture(pic[AWEL], 0, 0);
			break;
		case 1: //game interface
			set_palette(game_palette[BGAME]);
			draw_picture(pic[BGAME], 0, 0);
			set_palette(game_palette[BMOUNT]);
			draw_picture(pic[BMOUNT], 0, 0);
			break;
		case 2: //help interface
			set_palette(game_palette[HELP]);
			draw_picture(pic[HELP], 0, 0);
			break;
		case 3: //pause interface
			set_palette(game_palette[CPAUSE]);
			draw_picture(pic[CPAUSE], 0, 0);
			break;
		case 4: //WIN1 interface
			set_palette(game_palette[DWIN1]);
			draw_picture(pic[DWIN1], 0, 0);
			break;
		case 5: //WIN2 interface
			set_palette(game_palette[DWIN2]);
			draw_picture(pic[DWIN2], 0, 0);
			break;
	}
}