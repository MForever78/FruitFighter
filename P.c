#include "var.h"

void draw_interface(int interface)
{
	switch (interface) {
		case 0:	//welcome interface
			// set_palette(game_palette[AWEL]);
			draw_picture(pic[AWEL], 0, 0);
			break;
		case 1: //game interface
			draw_picture(pic[BGAME], 0, 0);
			// set_palette(game_palette[BMOUNT]);
			// draw_picture(pic[BMOUNT], 0, 0);
			break;
		case 2: //help interface
			// set_palette(game_palette[HELP]);
			draw_picture(pic[HELP], 0, 0);
			break;
		case 3: //pause interface
			// set_palette(game_palette[CPAUSE]);
			draw_picture(pic[CPAUSE], 0, 0);
			break;
		case 4: //WIN1 interface
			// set_palette(game_palette[DWIN1]);
			draw_picture(pic[DWIN1], 0, 0);
			break;
		case 5: //WIN2 interface
			// set_palette(game_palette[DWIN2]);
			draw_picture(pic[DWIN2], 0, 0);
			break;
	}
}

void draw_player(int index, int moving)
{
	PIC worm;
	if (index == 0) {
		if (moving) {
			worm = pic[WORM01];
			// set_palette(game_palette[WORM01]);
		} else {
			worm = pic[WORM00];
			// set_palette(game_palette[WORM00]);
		}
	} else {
		if (moving) {
			worm = pic[WORM11];
			// set_palette(game_palette[WORM11]);
		} else {
			worm = pic[WORM10];
			// set_palette(game_palette[WORM10]);
		}
	}
	putimage(player[index].x - worm.mask->picwidth / 2, player[index].y - worm.mask->picheight, worm.mask, AND_PUT);
	putimage(player[index].x - worm.img->picwidth / 2, player[index].y - worm.img->picheight, worm.img, OR_PUT);
}

void draw_bullet()
{
	// set_palette(game_palette[BULLET0]);
	draw_picture(pic[BULLET0], bullet.x, bullet.y);
}

void draw_explode()
{
	// set_palette(game_palette[EXPLO0 + explode_state]);
	draw_picture(pic[EXPLO0 + explode_state], bullet.x, bullet.y);	
}
