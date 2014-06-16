#include "var.h"

void draw_interface(int interface)
{
	switch (interface) {
		case 0:	//welcome interface
			draw_picture(pic[AWEL], 0, 0);
			break;
		case 1: //game interface
			draw_picture(pic[BGAME], 0, 0);
			draw_picture(pic[BMOUNT], 0, 0);
			break;
		case 2: //help interface
			draw_picture(pic[HELP], 0, 0);
			break;
		case 3: //pause interface
			draw_picture(pic[CPAUSE], 0, 0);
			break;
		case 4: //WIN1 interface
			draw_picture(pic[DWIN1], 0, 0);
			break;
		case 5: //WIN2 interface
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
		} else {
			worm = pic[WORM00];
		}
	} else {
		if (moving) {
			worm = pic[WORM11];
		} else {
			worm = pic[WORM10];
		}
	}
	draw_picture(worm, player[index].x - worm.mask->picwidth / 2, player[index].y - worm.mask->picheight);
}

void draw_bullet()
{
	draw_picture(pic[BULLET0], bullet.x, bullet.y);
}

void draw_explode()
{
	draw_picture(pic[EXPLO0 + explode_state], bullet.x, bullet.y);	
}
