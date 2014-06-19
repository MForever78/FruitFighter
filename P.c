#include "var.h"

void draw_interface(int interface)
{
	switch (interface) {
		case 0:	//welcome interface
			draw_picture(pic[AWEL], 0, 0);
			break;
		case 1: //game interface
			// draw_picture(pic[BGAME], 0, 0);
			draw_picture(pic[BMOUNT], 0, 310);
			break;
		case 2: //help interface
			draw_picture(pic[HELP], 0, 0);
			break;
		case 3: //pause interface
			draw_picture(pic[PAUSE], 0, 0);
			break;
		case 4: //WIN1 interface
			draw_picture(pic[WIN1], 0, 0);
			break;
		case 5: //WIN2 interface
			draw_picture(pic[WIN2], 0, 0);
			break;
	}
}

void draw_players()
{
	int i;
	for (i = 0; i < 2; i++) {
		draw_this_player(i);
	}
}

void draw_this_player(int index)
{
	PIC worm;
	//make rules to judge worm's status
	worm = pic[WORM000 + index * 4 + player[index].status * 2 + player[index].face];
	draw_picture(worm, player[index].x - worm.mask->picwidth / 2, player[index].y - worm.mask->picheight);
}

void draw_bullet()
{
	draw_picture(pic[BULLET0 + bullet.status], bullet.x - pic[BULLET0].img->picwidth / 2, bullet.y - pic[BULLET0].img->picheight / 2);
}

void draw_explode()
{
	draw_picture(pic[BUMP1 + explode_state], bullet.x, bullet.y);	
}

void draw_target()
{
	int x, y, index;
	index = bout.playerNum;
	x = player[index].x + cos(bullet.angle * PI / 180.0) * TDISTANCE;
	y = player[index].y + sin(bullet.angle * PI / 180.0) * TDISTANCE;
	draw_picture(pic[TARGET], x - pic[TARGET].img->picwidth / 2, y - pic[TARGET].img->picheight / 2);
}
