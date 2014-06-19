#include "var.h"

void init_player();
void init_round();
void init_time();
void cal_hurt();
void build_map();

/*
** use num 1, 2, 3 to choose interface
*/
void welcome_control()
{
	if (key[NUM_1]) {
		interface = 1;			//begin game
		interface_changed = 1;
	} else if (key[NUM_2]) {
		interface = 2;			//help
		interface_changed = 1;
	} else if (key[NUM_3]) {
		stop = 1;				//exit
	}
}

/*
** if any key is trigered, return to welcome interface
*/

void help_control()
{
	if (key[_ENTER]) {
		interface = 0;
		interface_changed = 1;
	}
}

void pause_control()
{
	if (key[_ENTER]) {
		interface = 1;
		interface_changed = 1;
	}
}


void round_move()
{
	int i, index;

	if (new_game) {
		build_map();
		init_player();
		init_round(0);
		init_time();
		new_game = 0;
	}

	index = bout.playerNum;

	if (aiming && !key[_SPACE]) {
		aiming = 0;
		aiming_count = 0;
		shooting = 1;
		bullet.time = 0;
		bullet.x = player[index].x;
		bullet.y = player[index].y;
		bullet.xspeed = cos(PI * bullet.angle / 180.0) * bullet.strenth;
		return;
	}

	if (key[_ENTER]) {
		key[_ENTER] = 0;
		interface = 3;
		interface_changed = 1;
	}

	if (key[_LEFT]) {
		player[index].face = 0;
		player[index].status_count++;
		if (player[index].status_count > STATUSCOUNT) {
			player[index].status_count -= STATUSCOUNT;
			player[index].status = !player[index].status;
		}
		if (player[index].x > 0){
			player[index].x--;
			for (i = 0; i < _height; i++) {
				if (!map[player[index].x][i]) {
					player[index].y = i;
					break;
				}
			}
		}
		return;
	}

	if (key[_RIGHT]) {
		player[index].face = 1;
		player[index].status_count++;
		if (player[index].status_count > STATUSCOUNT) {
			player[index].status_count -= STATUSCOUNT;
			player[index].status = !player[index].status;
		}
		if (player[index].x < _width - 1){
			player[index].x++;
			for (i = 0; i < _height; i++) {
				if (!map[player[index].x][i]) {
					player[index].y = i;
					break;
				}
			}
		}
		return;
	}

	if (key[_DOWN]) {
		bullet.angle++;
		if (bullet.angle >= 360) {
			bullet.angle -= 360;
		}
		return;
	}

	if (key[_UP]) {
		bullet.angle--;
		if (bullet.angle < 0) {
			bullet.angle += 360;
		}
		return;
	}

	if (key[_SPACE]) {
		aiming = 1;
		aiming_count++;
		if (aiming_count > AIMCOUNT) {
			aiming_count = 0;
			if (bullet.strenth < MAXSTRENTH) {
				bullet.strenth++;
			}
			return;
		}
	}
}

void bullet_flying()
{
	bullet.count++;
	if (bullet.count >= BULLETCOUNT) {
		bullet.count = 0;
		bullet.time++;
		bullet.status++;
		if (bullet.status > 11) {
			bullet.status = 0;
		}
		bullet.x += bullet.xspeed;
		bullet.yspeed = bullet.strenth * sin(PI * bullet.angle / 180.0) + GRAV * bullet.time;
		bullet.y += bullet.yspeed;
		if (bullet.x < 0 || bullet.x >= 1023 || bullet.y <= 0 || bullet.y >= 767 || !map[bullet.x][bullet.y]) {
			shooting = 0;
			exploding = 1;
		}
	}
}

void bullet_explode()
{
	explode_count++;
	if (explode_count > EXPLODECOUNT) {
		explode_count = 0;
		explode_state++;
	}
	if (explode_state >= 23) {
		explode_state = 0;
		exploding = 0;
		init_round(!bout.playerNum);
		cal_hurt();
	}
}

void cal_hurt()
{
	int i, dist;

	for (i = 0; i < 2; i++) {
		// dist = sqrt((bullet.x - player[i].x) * (bullet.x - player[i].x) + (bullet.y - player[i].y) * (bullet.y - player[i].y));
		dist = (abs(bullet.x - player[i].x) + abs(bullet.y - player[i].y)) / 2;
		if (dist < RAID) {
			player[i].hp -= BASICHURT - dist;
			if (player[i].hp <= 0) {
				interface = 5 - i;
				interface_changed = 1;
				break;
			}
		}
	}

}

void init_player()
{
	int i, j;

	player[0].x = _width / 2 - PLAYEROFFSET;
	player[1].x = _width / 2 + PLAYEROFFSET;

	for (i = 0; i < 2; i++) {
		player[i].hp = 100;
		player[i].status = 0;
		player[i].status_count = 0;
		player[i].face = 1 - i;		//0 is left, 1 is right
		for (j = 0; j < _height; j++){
			if (!map[player[i].x][j]) {
				player[i].y = j;
				break;
			}
		}
	}

}

void init_round(int p)
{
	bout.playerNum = p;			//player 1 first
	bullet.strenth = 0;
	bullet.angle = 0;
	bullet.status = 0;
}

void init_time()
{
	game_time = 0;
	prev_update_time = 0;
}

void build_map()
{
	PIC *p = &pic[BMOUNT];
	int i, j, width, height;
	long *color;
	byte *q;

	for (i = 0; i < _width; i++) {
		for (j = 0; j < 310; j++) {
			map[i][j] = 1;
		}
	}

	q = &p->img->buffer;
	for (i = 0; i < p->img->picwidth * p->img->picheight; i++) {
		color = (long *)q;
		if ((*color & 0xFFFFFF00) == 0xFFFFFF00) {
			height = i / p->img->picwidth;
			width = i % p->img->picwidth;
			map[width][height + 310] = 1;
		}
		q += 3;
	}
}
