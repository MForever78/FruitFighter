#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <dos.h>

#define UP 0x48                 /*按键定义*/
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define ENTER 0x1c
#define ESC 0x01
#define SPACEUP 0xb9
#define SPACEDOWN 0x39
#define WEAPON 0x1e

#define PAINT paint(option[interface], point, player, &bout, winner)

typedef struct {                /*结构定义*/
    int have;
    unsigned long color;
}POINT;
typedef struct {
    int hp;
    int weapon;
    int weaponNum[4];
    int x, y;
    int xaim, yaim;
    int face;
    double angle;
}PLAYER;
typedef struct {
    int boutNum;
    int playerNum;
    int strenth;
    int wind;
}BOUT;

int key;
int second = 45;                /*倒计时*/
int interface = 0;             /*界面标号*/

/*中断函数*/
void install(void interrupt (*interruptVect)(void), int interruptNum);
void interrupt int8h(void);
void interrupt int9h(void);

/*初始化函数*/
void initialize(POINT (*point)[1024], PLAYER *player, BOUT *pbout);

/*移动函数*/
void move(POINT (*point)[1024], PLAYER *player, BOUT *pbout);
void jump(POINT (*point)[1024], PLAYER *player, BOUT *pbout);

/*写屏函数*/
void paint(int option, POINT (*point)[1024], PLAYER *player, BOUT *pbout, int winner);

void paint00(void);
void paint01(void);
void paint02(void);
void paint03(void);

void paint10(POINT (*point)[1024], PLAYER *player, BOUT *pbout);

void paint20(int *weaponNum);
void paint21(int *weaponNum);
void paint22(int *weaponNum);
void paint23(int *weaponNum);
void paint24(int *weaponNum);
void paint25(int *weaponNum);
void paint26(int *weaponNum);
void paint27(int *weaponNum);

void paint30(void);
void paint31(void);
void paint32(void);
void paint33(void);
void paint34(void);

void paint40(int winner);
void paint41(int winner);
void paint42(int winner);

void paint50(void);

void paint60(void);

void paint70(void);
void paint71(void);

int main(void)
{
    int interfaceTemp, option[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int star = 0, over = 0, quit = 0;

    int driver = 0, mode = VESA_1024x768x32bit;
    POINT point[768][1024];

    PLAYER player[2];
    int winner;
    BOUT bout;
    int space = 0;

    void interrupt (*old8h)(void);
    void interrupt (*old9h)(void);

    old8h = getvect(8);
    old9h = getvect(9);
    install(int8h, 8);
    install(int9h, 9);

    initgraph(&driver, &mode, "");
    PAINT;
    while (!quit) {
        key = 0;
        while (!key) {
            if (second == 0) {
                over = 1;
                break;
            }
        }
        switch (interface) {								//default is 0
            case 0:											//Welcome interface
                switch (key) {
                    case UP:
                        option[interface] -= 1;
                        if (option[interface] < 0) {
                            option[interface] += 4;			//loop
                        }
                        PAINT;
                        break;
                    case DOWN:
                        option[interface] += 1;
                        if (option[interface] > 3) {
                            option[interface] -= 4;			//loop
                        }
                        PAINT;
                        break;
                    case ENTER:
                        switch (option[interface]) {
                            case 0:							//game start
                                interface = 1;
                                initialize(point, player, &bout);
                                PAINT;
                                break;
                            case 1:
                                interfaceTemp = interface;
                                interface = 5;
                                PAINT;
                                break;
                            case 2:
                                interface = 6;
                                PAINT;
                                break;
                            case 3:
                                interfaceTemp = interface;
                                interface = 7;
                                PAINT;
                                break;
                        }
                        break;
                    case ESC:
                        interfaceTemp = interface;
                        interface = 7;
                        PAINT;
                        break;
                }
                break;
            case 1:														//game interface
                switch (key) {
                    case UP:
                        if (star == 1) {
                            player[bout.playerNum].yaim -= 1;
                            if (player[bout.playerNum].yaim < 0) {
                                player[bout.playerNum].yaim = 0;
                            }
                        }
                        else {
                            player[bout.playerNum].angle += PI/32;
                            if (player[bout.playerNum].angle > PI/2) {
                                player[bout.playerNum].angle = PI/2;
                            }
                        }
                        PAINT;
                        break;
                    case DOWN:
                        if (star == 1) {
                            player[bout.playerNum].yaim += 1;
                            if (player[bout.playerNum].yaim > 767) {
                                player[bout.playerNum].yaim = 767;
                            }
                        }
                        else {
                            player[bout.playerNum].angle -= PI/32;
                            if (player[bout.playerNum].angle < -PI/2) {
                                player[bout.playerNum].angle = -PI/2;
                            }
	                        PAINT;
	                        break;
	                    }
                    case LEFT:
                        if (star == 1) {
                            player[bout.playerNum].xaim -= 1;
                            if (player[bout.playerNum].xaim < 0) {
                                player[bout.playerNum].xaim = 0;
                            }
                        }
                        else {
                            move(point, player, &bout);
                        }
                        PAINT;
                        break;
                    case RIGHT:
                    	if (star == 1) {
                            player[bout.playerNum].xaim += 1;
                            if (player[bout.playerNum].xaim > 1023) {
                                player[bout.playerNum].xaim = 1023;
                            }
                        }
                        else {
                            move(point, player, &bout);
                        }
                        PAINT;
                        break;
                    case ENTER:
                        jump(point, player, &bout);
                        PAINT;
                        break;
                    case ESC:
                        interface = 3;									//pause
                        PAINT;
                        break;
                    case SPACEUP:
                        space = 0;
                        over = 1;
                        switch(player[bout.playerNum].weapon) {
                            case 0:
                                 PAINT;
                                 break;
                            case 1:
                                player[bout.playerNum].weaponNum[0]--;
                                PAINT;
                                break;
                            case 2:
                                player[bout.playerNum].weaponNum[1]--;
                                PAINT;
                                break;
                            case 3:
                                player[bout.playerNum].weaponNum[2]--;
                                PAINT;
                                break;
                            case 4:														//transmit
                                player[bout.playerNum].weaponNum[3]--;
                                player[bout.playerNum].x = player[bout.playerNum].xaim;
                                player[bout.playerNum].y = player[bout.playerNum].yaim;
                                PAINT;
                                break;
                            case 5:
                                PAINT;
                                break;
                            case 6:
                                PAINT;
                                break;
                            case 7:
                                break;
                            case 8:
                                player[bout.playerNum].hp = 0;							//kill himself
                                break;
                        }
                    case SPACEDOWN:
                        if (player[bout.playerNum].weapon < 3) {
                            if (space == 0) {
                                space = 1;
                                bout.strenth = 0;
                            }
                            else {
                                bout.strenth++;

                            }
                        }
                        break;
                    case WEAPON:
                        interface = 2;
                        PAINT;
                        break;
                }
                break;
            case 2:										//weapon interface
                switch (key) {
                    case UP:
                        option[interface] -= 4;
                        if (option[interface] < 0) {
                            option[interface] += 8;
                        }
                        PAINT;
                        break;
                    case DOWN:
                        option[interface] += 4;
                        if (option[interface] > 7) {
                            option[interface] -= 8;
                        }
                        PAINT;
                        break;
                    case LEFT:
                        option[interface] -= 1;
                        if (option[interface] < 0 || option[interface] == 4) {
                            option[interface] += 4;
                        }
                        PAINT;
                        break;
                    case RIGHT:
                        option[interface] += 1;
                        if (option[interface] > 7 || option[interface] == 5) {
                            option[interface] -= 4;
                        }
                        PAINT;
                        break;
                    case ENTER:
                        if (option[interface] >= 1 && option[interface] <= 4) {
                            if (player[bout.playerNum].weaponNum[option[interface]-1] == 0) {
                                break;
                            }
                            else {
                                if (option[interface] != 2) {
                                    star = 1;
                                }
                                else {
                                    star = 0;
                                }
                            }
                        }
                        else {
                            star = 0;
                        }
                        player[bout.playerNum].weapon = option[interface];
                        PAINT;
                        break;
                    case ESC:
                        interface = 1;
                        PAINT;
                        break;
                }
                break;
            case 3:
                switch (key) {
                    case UP:
                        option[interface] -= 1;
                        if (option[interface] < 0) {
                            option[interface] += 5;
                        }
                        PAINT;
                        break;
                    case DOWN:
                        option[interface] += 1;
                        if (option[interface] > 4) {
                            option[interface] -= 5;
                        }
                        PAINT;
                        break;
                    case ENTER:
                        switch (option[interface]) {
                            case 0:
                                interface = 7;
                                PAINT;
                                break;
                            case 1:
                                interface = 1;
                                PAINT;
                                break;
                            case 2:
                                interfaceTemp = interface;
                                interface = 5;
                                PAINT;
                                break;
                            case 3:
                                interface = 7;
                                PAINT;
                                break;
                            case 4:
                                interfaceTemp = interface;
                                interface = 7;
                                PAINT;
                                break;
                        }
                        break;
                    case ESC:
                        interface = 1;
                        PAINT;
                        break;
                }
                break;
            case 4:
                switch (key) {
                    case UP:
                        option[interface] -= 1;
                        if (option[interface] < 0) {
                            option[interface] += 3;
                        }
                        PAINT;
                        break;
                    case DOWN:
                        option[interface] += 1;
                        if (option[interface] > 2) {
                            option[interface] -= 3;
                        }
                        PAINT;
                        break;
                    case ENTER:
                        switch (option[interface]) {
                            case 0:
                                interface = 1;
                                initialize(point, player, &bout);
                                PAINT;
                                break;
                            case 1:
                                interface = 0;
                                PAINT;
                                break;
                            case 2:
                                interfaceTemp = interface;
                                interface = 7;
                                PAINT;
                                break;
                        }
                        break;
                    case ESC:
                        interface = 0;
                        PAINT;
                        break;
                }
                break;
            case 5:
                switch (key) {
                    case ENTER:
                    case ESC:
                        interface = interfaceTemp;
                        PAINT;
                        break;
                }
                break;
            case 6:
                switch (key) {
                    case ENTER:
                    case ESC:
                        interface = 0;
                        PAINT;
                        break;
                }
                break;
            case 7:
                switch (key) {
                    case LEFT:
                        option[interface] -= 1;
                        if (option[interface] < 0) {
                            option[interface] += 2;
                        }
                        PAINT;
                        break;
                    case RIGHT:
                        option[interface] += 1;
                        if (option[interface] > 1) {
                            option[interface] -= 2;
                        }
                        PAINT;
                        break;
                    case ENTER:
                        if (option[interface] == 0) {
                            interface = interfaceTemp;
                            PAINT;
                        }
                        else {
                            quit = 1;
                        }
                        break;
                    case ESC:
                        interface = interfaceTemp;
                        PAINT;
                        break;
                }
                break;
        }
        if (over) {
            over = 0;
            second = 45;
            if (player[0].hp > 0 && player[1].hp > 0){
                bout.boutNum++;
                bout.playerNum = !bout.playerNum;
                bout.wind = rand()%101-50;
            }
            else {
                if (player[0].hp <= 0 && player[1].hp <= 0) {
                    winner = -1;
                }
                else if (player[0].hp <= 0) {
                    winner = 1;
                }
                else {
                    winner = 0;
                }
                interface = 4;
                PAINT;
            }
        }
    }
    install(old8h, 8);
    install(old9h, 9);

    return 0;
}

/*选择写屏函数*/
void paint(int option, POINT (*point)[1024], PLAYER *player, BOUT *pbout, int winner)
{
    switch (interface) {
        case 0:
            switch (option) {
                case 0:
                    paint00();
                    break;
                case 1:
                    paint01();
                    break;
                case 2:
                    paint02();
                    break;
                case 3:
                    paint03();
                    break;
            }
            break;
        case 1:
            paint10(point, player, pbout);
        case 2:
            switch (option) {
                case 0:
                    paint20(player[pbout->playerNum].weaponNum);
                    break;
                case 1:
                    paint21(player[pbout->playerNum].weaponNum);
                    break;
                case 2:
                    paint22(player[pbout->playerNum].weaponNum);
                    break;
                case 3:
                    paint23(player[pbout->playerNum].weaponNum);
                    break;
                case 4:
                    paint24(player[pbout->playerNum].weaponNum);
                    break;
                case 5:
                    paint25(player[pbout->playerNum].weaponNum);
                    break;
                case 6:
                    paint26(player[pbout->playerNum].weaponNum);
                    break;
                case 7:
                    paint27(player[pbout->playerNum].weaponNum);
                    break;
            }
            break;
        case 3:
            switch (option) {
                case 0:
                    paint30();
                    break;
                case 1:
                    paint31();
                    break;
                case 2:
                    paint32();
                    break;
                case 3:
                    paint33();
                    break;
                case 4:
                    paint34();
                    break;
            }
            break;
        case 4:
            switch (option) {
                case 0:
                    paint40(winner);
                    break;
                case 1:
                    paint41(winner);
                    break;
                case 2:
                    paint42(winner);
                    break;
            }
            break;
        case 5:
            switch (option) {
                case 0:
                    paint50();
                    break;
            }
            break;
        case 6:
            switch (option) {
                case 0:
                    paint60();
                    break;
            }
            break;
        case 7:
            switch (option) {
                case 0:
                    paint70();
                    break;
                case 1:
                    paint71();
                    break;
            }
            break;
    }
}

void install(void interrupt (*interruptVect)(void), int interruptNum)
{
    disable();
    setvect(interruptNum, interruptVect);
    enable();
}

/*时钟中断*/
void interrupt int8h(void)
{
    static int count = 0;

    if (interface == 1) {
        count++;
        if (count < 18) {
            goto EOI;
        }
        count = 0;
        if (second > 0) {
            second--;
        }
    }
    EOI: outportb(0x20, 0x20);
}

/*键盘中断*/
void interrupt int9h(void)
{
    key = inportb(0x60);
    outportb(0x61, inportb(0x61) | 0x80);
    outportb(0x61, inportb(0x61) & 0x7f);
    outportb(0x20, 0x20);
}

/*初始化函数*/
void initialize(POINT (*point)[1024], PLAYER *player, BOUT *pbout)
{
    int i, j;

    srand(time(0));
    for (i = 0; i < 2; i++) {
        player[i].hp = 100;
        player[i].weapon = 0;
        for (j = 0; j < 4; j++) {
            if (j != 2) {
                player[i].weaponNum[j] = 1;
            }
            else {
                player[i].weaponNum[j] = 0;
            }
        }
        player[i].x = rand()%1024;
        player[i].xaim = 512;
        player[i].yaim = 384;
        player[i].face = 0;
        player[i].angle = 0;
    }
    pbout->boutNum = 1;
    pbout->playerNum = 0;
    pbout->wind = rand()%101-50;
}

/*游戏界面写屏函数*/
void paint10(POINT (*point)[1024], PLAYER *player, BOUT *pbout)
{
    int xdirection, ydirection;

    if (player[pbout->playerNum].face == 0) {                    /*准星坐标计算*/
        xdirection = player[pbout->playerNum].x-100*cos(player[pbout->playerNum].angle);
        ydirection = player[pbout->playerNum].y-100*sin(player[pbout->playerNum].angle);
    }
    else {
        xdirection = player[pbout->playerNum].x+100*cos(player[pbout->playerNum].angle);
        ydirection = player[pbout->playerNum].y-100*sin(player[pbout->playerNum].angle);
    }
}
