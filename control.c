#include "var.h"

void init_player();
void init_round();
void init_time();
void cal_hurt();

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
	if (anykey) {
		interface = 1;
		interface_changed = 1;
	}
}

void round_move()
{
	int i, index;

	if (new_game) {
		init_player();
		init_round(0);
		init_time();
		new_game = 0;
	}

	index = bout.playerNum;

	if (aiming && !key[_SPACE]) {
		aiming = 0;
		shooting = 1;
		bullet.time = 0;
		bullet.x = player[index].x;
		bullet.y = player[index].y;
		bullet.face = player[index].face;
		bullet.xspeed = cos(bullet.angle) * bullet.strenth;
		return;
	}

	if (key[_LEFT]) {
		player[index].face = 0;
		if (player[index].x > 0){
			player[index].x--;
			for (i = _height; i > 0; i--) {
				if (map[player[index].x][i]) {
					player[index].y = i;
					break;
				}
			}
		}
	}

	if (key[_RIGHT]) {
		player[index].face = 1;
		if (player[index].x < _width - 1){
			player[index].x++;
			for (i = _height; i > 0; i--) {
				if (map[player[index].x][i]) {
					player[index].y = i;
					break;
				}
			}
		}
	}

	if (key[_UP]) {
		bullet.angle++;
		if (bullet.angle >= 360) {
			bullet.angle -= 360;
		}
	}

	if (key[_DOWN]) {
		bullet.angle--;
		if (bullet.angle < 0) {
			bullet.angle += 360;
		}
	}

	if (key[_SPACE]) {
		aiming = 1;
		if (bullet.strenth < MAXSTRENTH) {
			bullet.strenth++;
		}
	}

}

void bullet_flying()
{
	bullet.time++;
	bullet.x += bullet.xspeed;
	bullet.yspeed = bullet.strenth * sin(bullet.angle) - GRAV * bullet.time;
	bullet.y += bullet.yspeed;
	if (!map[bullet.x][bullet.y]) {
		shooting = 0;
		exploding = 1;
		bullet_explode();
	} else {
		draw_bullet();
	}
}

void bullet_explode()
{
	explode_state++;
	draw_explode();
	if (explode_state >= 31) {
		explode_state = 0;
		exploding = 0;
		cal_hurt();
	}
}

void cal_hurt()
{
	int i, dist;

	for (i = 0; i < 2; i++) {
		dist = sqrt((bullet.x - player[i].x) * (bullet.x - player[i].x) + (bullet.y - player[i].y) * (bullet.y - player[i].y));
		if (dist < RAID) {
			player[i].hp -= BASICHURT / dist / dist;
			if (player[i].hp <= 0) {
				interface = 5 - i;
			}
		}
	}

}

void init_player()
{
	int i, j;

	player[1].x = _width / 2 - PLAYEROFFSET;
	player[2].x = _width / 2 + PLAYEROFFSET;

	for (i = 0; i < 2; i++) {
		player[i].hp = 100;
		player[i].face = 1 - i;		//0 is left, 1 is right
		for (j = _height; j > 0; j--){
			if (map[player[i].x][j]) {
				player[i].y = j;
				break;
			}
		}
		draw_player(i, STILL);
	}

}

void init_round(int p)
{
	bout.playerNum = p;			//player 1 first
	bullet.strenth = 0;
}

void init_time()
{
	game_time = 0;
	prev_update_time = 0;
}
