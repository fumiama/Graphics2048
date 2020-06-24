#pragma once

#include <conio.h>
#include <graphics.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#include "online.h"

#define COLOR2048       0x03c7eb
#define COLOR1024       0x15b9e3
#define COLOR512         0x50c8ec
#define COLOR256         0x61cced
#define COLOR128         0x71ceed
#define COLOR64           0x3b5df6
#define COLOR32           0x5f7cf5
#define COLOR16           0x6395f5
#define COLOR8             0x79b1f2
#define COLOR4             0xc8e0ec
#define COLOR2             0xdae4ee
#define MEATCOLOR		0xb7c8ff

static short arr[6][6];
#define CH arr[0][5]
#define CHILDMSG arr[5][4]
#define CUR arr[5][0]
#define FLAG arr[0][4]
#define FLAG2 arr[5][1]
#define FLAG3 arr[5][2]
#define FLAG4 arr[5][3]
#define ISFAIL arr[0][1]
#define ISWIN arr[0][0]
#define NOMOV arr[0][2]
#define SCORE arr[0][3]
static short arr2[6][6];
#define savestage() memcpy(arr2, arr, sizeof(arr))

static IMAGE stage;
#define merge(x, y) FLAG3 = x(); FLAG4 = y(); NOMOV = FLAG3 && !FLAG4
#define drawb(color) setfillcolor(color);fillroundrect(118 + 104 * (i - 1), 179 + 108 * (j - 1), 208 + 104 * (i - 1), 269 + 108 * (j - 1), 36, 36)
#define drawt(color, text) settextcolor(color);drawtext(_T(text), &square, DT_CENTER | DT_VCENTER | DT_SINGLELINE)

static MOUSEMSG mmsg;
#define ISINCLEAN (mmsg.x >= 560 && mmsg.x <= 610 && mmsg.y >= 490 && mmsg.y <= 540)
#define ISINRET (mmsg.x >= 560 && mmsg.x <= 610 && mmsg.y >= 385 && mmsg.y <= 435)
#define ISIN1 (mmsg.x >= 220 && mmsg.x <= 420 && mmsg.y >= 170 && mmsg.y <= 220)
#define ISIN2 (mmsg.x >= 220 && mmsg.x <= 420 && mmsg.y >= 250 && mmsg.y <= 300)
#define ISIN3 (mmsg.x >= 220 && mmsg.x <= 420 && mmsg.y >= 330 && mmsg.y <= 380)
#define ISIN4 (mmsg.x >= 220 && mmsg.x <= 420 && mmsg.y >= 410 && mmsg.y <= 460)
#define selmenu(judge, cur) if (judge) {\
	CUR = cur;\
	if (mmsg.mkLButton) {\
		mmsg.mkLButton = 0;\
		FLAG = EOF;\
	}\
	else FLAG = 1;\
}

#define listenprepare(func) _beginthreadex(NULL, 0, func, NULL, 0, NULL)
#define listendestroy() CHILDMSG = 0

short calScore(short arr[6][6]);
int downadd();
int downmove();
void drawblocks();
void gamedisplay();
int havempty();
void initui();
int leftadd();
int leftmove();
unsigned int __stdcall listenmenu(PVOID pM);
unsigned int __stdcall listenplay(PVOID pM);
int menu();
void newblock();
void onlineinit();
int operate();
void print2score();
void printmyscore();
int rightadd();
int rightmove();
int upadd();
int upmove();

short calScore(short arr[6][6]) {
	SCORE = 0;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			SCORE += arr[i][j];
		}
	}
	return SCORE % 9999 + 1;
}
int downadd() {
	FLAG = 0;
	for (int j = 1; j <= 4; j++)
		switch ((arr[1][j] ? 8 : 0) + (arr[2][j] ? 4 : 0) + (arr[3][j] ? 2 : 0) + (arr[4][j] ? 1 : 0)) {
		case 0: case 1: break;
		case 3:
			if (arr[3][j] == arr[4][j]) {
				arr[4][j] *= 2;
				FLAG++;
				arr[3][j] = 0;
			}
			break;
		case 7:
			if (arr[3][j] == arr[4][j]) {
				arr[4][j] *= 2;
				FLAG++;
				arr[3][j] = arr[2][j];
				arr[2][j] = 0;
			}
			else if (arr[2][j] == arr[3][j]) {
				arr[3][j] *= 2;
				FLAG++;
				arr[2][j] = 0;
			}
			break;
		case 15:
			if (arr[3][j] == arr[4][j]) {
				arr[4][j] *= 2;
				FLAG++;
				arr[3][j] = 0;
			}
			else if (arr[2][j] == arr[3][j]) {
				arr[3][j] *= 2;
				FLAG++;
				arr[2][j] = 0;
			}
			if (arr[1][j] == arr[2][j]) {
				arr[2][j] *= 2;
				FLAG++;
				arr[1][j] = 0;
			}
			downmove();
			break;
		}
	return FLAG;
}
int downmove() {
	FLAG2 = 0;
	for (int j = 1; j <= 4; j++)
		switch ((arr[1][j] ? 8 : 0) + (arr[2][j] ? 4 : 0) + (arr[3][j] ? 2 : 0) + (arr[4][j] ? 1 : 0)) {
		case 0: case 1: case 3: case 7: case 15: FLAG2++; break;
		case 2: arr[4][j] = arr[3][j]; arr[3][j] = 0; break;
		case 4: arr[4][j] = arr[2][j]; arr[2][j] = 0; break;
		case 5: arr[3][j] = arr[2][j]; arr[2][j] = 0; break;
		case 6: arr[4][j] = arr[3][j]; arr[3][j] = arr[2][j]; arr[2][j] = 0; break;
		case 8: arr[4][j] = arr[1][j]; arr[1][j] = 0; break;
		case 9: arr[3][j] = arr[1][j]; arr[1][j] = 0; break;
		case 10: arr[4][j] = arr[3][j]; arr[3][j] = arr[1][j]; arr[1][j] = 0; break;
		case 11: arr[2][j] = arr[1][j]; arr[1][j] = 0; break;
		case 12: arr[4][j] = arr[2][j]; arr[3][j] = arr[1][j]; arr[1][j] = arr[2][j] = 0; break;
		case 13: arr[3][j] = arr[2][j]; arr[2][j] = arr[1][j]; arr[1][j] = 0; break;
		case 14: arr[4][j] = arr[3][j]; arr[3][j] = arr[2][j]; arr[2][j] = arr[1][j]; arr[1][j] = 0; break;
		default: break;
		}
	return (FLAG2 == 4);
}
void drawblocks() {
	putimage(116, 177, &stage);
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			RECT square = { 118 + 104 * (i - 1), 179 + 108 * (j - 1), 208 + 104 * (i - 1), 269 + 108 * (j - 1) };
			switch (arr[i][j]) {
			//case 0:
			//	drawb(WHITE);
			//	break;
			case 2:
				drawb(COLOR2);
				drawt(DARKGRAY, "2");
				break;
			case 4:
				drawb(COLOR4);
				drawt(DARKGRAY, "4");
				break;
			case 8:
				drawb(COLOR8);
				drawt(WHITE, "8");
				break;
			case 16:
				drawb(COLOR16);
				drawt(WHITE, "16");
				break;
			case 32:
				drawb(COLOR32);
				drawt(WHITE, "32");
				break;
			case 64:
				drawb(COLOR64);
				drawt(WHITE, "64");
				break;
			case 128:
				drawb(COLOR128);
				drawt(WHITE, "128");
				break;
			case 256:
				drawb(COLOR256);
				drawt(WHITE, "256");
				break;
			case 512:
				drawb(COLOR512);
				drawt(WHITE, "512");
				break;
			case 1024:
				drawb(COLOR1024);
				drawt(WHITE, "1024");
				break;
			case 2048:
				drawb(COLOR2048);
				drawt(WHITE, "2048");
				break;
			}
		}
	}
}
void gamedisplay() {
	loadimage(NULL, L"IMG", L"MIKU", 640, 640);
	loadimage(&stage, L"IMG", L"STAGE", 407, 419);
	RECT r = { 28, 10, 208, 160 };
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 48;						// 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, _T("华文行楷"));		// 设置字体为“华文行楷”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	f.lfWeight = FW_HEAVY;
	settextstyle(&f);						// 设置字体样式
	settextcolor(BLUE);
	setbkmode(TRANSPARENT);
	memset(arr, 0, sizeof(arr));
	memset(arr2, 0, sizeof(arr));
}
int havempty() {
	FLAG = 0;
	for (int i = 1; i <= 4; i++) for (int j = 1; j <= 4; j++) {
		setbkcolor(MEATCOLOR);
		setbkmode(OPAQUE);
		settextcolor(WHITE);
		if (arr[i][j]) FLAG++;
		if (arr[i][j] == 2048 && !ISWIN) {
			outtextxy(260, 61, L"WIN");
			setbkmode(TRANSPARENT);
			return ISWIN = 1;
			break;
		}
		else if (ISWIN) return ISWIN = 0;
	}
	if (FLAG >= 16) {
		if (!ISFAIL) {
			outtextxy(260, 61, L"FAIL");
			setbkmode(TRANSPARENT);
			return ISFAIL = 1;
		}
	}
	else {
		ISFAIL = 0;
		outtextxy(260, 61, L"         ");
		setbkmode(TRANSPARENT);
	}
	return !ISFAIL;
}
void initui() {
	initgraph(640, 640);// 绘图窗口初始化
	loadimage(NULL, L"IMG", L"MENU", 640, 640);// 读取图片至绘图窗口

	setbkmode(TRANSPARENT);//设置字体背景透明
	settextcolor(COLOR2048);
	settextstyle(130, 70, _T("Consolas"));
	outtextxy(180, 30, _T("2048"));//设置字体坐标

	setfillcolor(0x32df1c);
	fillroundrect(220, 170, 420, 220, 20, 20);
	setfillcolor(0xd1edc8);
	fillroundrect(220, 250, 420, 300, 20, 20);
	fillroundrect(220, 330, 420, 380, 20, 20);
	fillroundrect(220, 410, 420, 460, 20, 20);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);//设置字体背景透明
	settextstyle(45, 0, _T("Consolas"));
	outtextxy(235, 175, _T("单人模式"));
	settextstyle(45, 0, _T("Consolas"));
	outtextxy(235, 255, _T("联机模式"));
	settextstyle(45, 0, _T("Consolas"));
	outtextxy(235, 335, _T("游戏说明"));
	settextstyle(45, 0, _T("Consolas"));
	outtextxy(235, 415, _T("退出游戏"));

	srand(time(0));
}
int leftadd() {
	FLAG = 0;
	for (int j = 1; j <= 4; j++)
		switch ((arr[j][1] ? 8 : 0) + (arr[j][2] ? 4 : 0) + (arr[j][3] ? 2 : 0) + (arr[j][4] ? 1 : 0)) {
		case 0: case 8: break;
		case 12:
			if (arr[j][1] == arr[j][2]) {
				arr[j][1] *= 2;
				FLAG++;
				arr[j][2] = 0;
			}
			break;
		case 14:
			if (arr[j][1] == arr[j][2]) {
				arr[j][1] *= 2;
				FLAG++;
				arr[j][2] = arr[j][3];
				arr[j][3] = 0;
			}
			else if (arr[j][2] == arr[j][3]) {
				arr[j][2] *= 2;
				FLAG++;
				arr[j][3] = 0;
			}
			break;
		case 15:
			if (arr[j][1] == arr[j][2]) {
				arr[j][1] *= 2;
				FLAG++;
				arr[j][2] = 0;
			}
			else if (arr[j][2] == arr[j][3]) {
				arr[j][2] *= 2;
				FLAG++;
				arr[j][3] = 0;
			}
			if (arr[j][3] == arr[j][4]) {
				arr[j][3] *= 2;
				FLAG++;
				arr[j][4] = 0;
			}
			leftmove();
			break;
		}
	return FLAG;
}
int leftmove() {
	FLAG2 = 0;
	for (int j = 1; j <= 4; j++)
		switch ((arr[j][1] ? 8 : 0) + (arr[j][2] ? 4 : 0) + (arr[j][3] ? 2 : 0) + (arr[j][4] ? 1 : 0)) {
		case 0: case 8: case 12: case 14: case 15: FLAG2++; break;
		case 1: arr[j][1] = arr[j][4]; arr[j][4] = 0; break;
		case 2: arr[j][1] = arr[j][3]; arr[j][3] = 0; break;
		case 3: arr[j][1] = arr[j][3]; arr[j][2] = arr[j][4]; arr[j][3] = arr[j][4] = 0; break;
		case 4: arr[j][1] = arr[j][2]; arr[j][2] = 0; break;
		case 5: arr[j][1] = arr[j][2]; arr[j][2] = arr[j][4]; arr[j][4] = 0; break;
		case 6: arr[j][1] = arr[j][2]; arr[j][2] = arr[j][3]; arr[j][3] = 0; break;
		case 7: arr[j][1] = arr[j][2]; arr[j][2] = arr[j][3]; arr[j][3] = arr[j][4]; arr[j][4] = 0; break;
		case 9: arr[j][2] = arr[j][4]; arr[j][4] = 0; break;
		case 10: arr[j][2] = arr[j][3]; arr[j][3] = 0; break;
		case 11: arr[j][2] = arr[j][3]; arr[j][3] = arr[j][4]; arr[j][4] = 0; break;
		case 13: arr[j][3] = arr[j][4]; arr[j][4] = 0; break;
		default: break;
		}
	return (FLAG2 == 4);
}
unsigned int __stdcall listenmenu(PVOID pM) {
	CHILDMSG = 0;
	while (!CHILDMSG) {
		mmsg = GetMouseMsg();
		selmenu(ISIN1, 1) else selmenu(ISIN2, 2) else selmenu(ISIN3, 3) else selmenu(ISIN4, 4);
		FlushMouseMsgBuffer();
	}
	return 0;
}
unsigned int __stdcall listenplay(PVOID pM) {
	CHILDMSG = 0;
	while (!CHILDMSG) {
		while (!CHILDMSG && !mmsg.mkLButton) mmsg = GetMouseMsg();
		mmsg.mkLButton = 0;
		if (ISINCLEAN) { gamedisplay(); newblock(); drawblocks();}
		else if (ISINRET) { memcpy(arr, arr2, sizeof(arr)); drawblocks(); printmyscore();}
		FlushMouseMsgBuffer();
	}
	return 0;
}
int menu() {
	CUR = 1;
	FLAG = 0;
	listenprepare(listenmenu);
	while (~FLAG) {
		Sleep(100);
		switch (CUR){
		case 1:
			setfillcolor(0x32df1c);
			fillroundrect(220, 170, 420, 220, 20, 20);
			setfillcolor(0xd1edc8);
			fillroundrect(220, 250, 420, 300, 20, 20);
			fillroundrect(220, 330, 420, 380, 20, 20);
			fillroundrect(220, 410, 420, 460, 20, 20);
			break;
		case 2:
			setfillcolor(0x32df1c);
			fillroundrect(220, 250, 420, 300, 20, 20);
			setfillcolor(0xd1edc8);
			fillroundrect(220, 170, 420, 220, 20, 20);
			fillroundrect(220, 330, 420, 380, 20, 20);
			fillroundrect(220, 410, 420, 460, 20, 20);
			break;
		case 3:
			setfillcolor(0x32df1c);
			fillroundrect(220, 330, 420, 380, 20, 20);
			setfillcolor(0xd1edc8);
			fillroundrect(220, 170, 420, 220, 20, 20);
			fillroundrect(220, 250, 420, 300, 20, 20);
			fillroundrect(220, 410, 420, 460, 20, 20);
			break;
		case 4:
			setfillcolor(0x32df1c);
			fillroundrect(220, 410, 420, 460, 20, 20);
			setfillcolor(0xd1edc8);
			fillroundrect(220, 170, 420, 220, 20, 20);
			fillroundrect(220, 250, 420, 300, 20, 20);
			fillroundrect(220, 330, 420, 380, 20, 20);
			break;
		}
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);//设置字体背景透明
		settextstyle(45, 0, _T("Consolas"));
		outtextxy(235, 175, _T("单人模式"));
		settextstyle(45, 0, _T("Consolas"));
		outtextxy(235, 255, _T("联机模式"));
		settextstyle(45, 0, _T("Consolas"));
		outtextxy(235, 335, _T("游戏说明"));
		settextstyle(45, 0, _T("Consolas"));
		outtextxy(235, 415, _T("退出游戏"));
	}
	listendestroy();
	return CUR;
}
void newblock() {
	int x = rand() % 4 + 1;
	int y = rand() % 4 + 1;
	while (arr[x][y]) {
		x = rand() % 4 + 1;
		y = rand() % 4 + 1;
	}
	if (!(rand() % 10)) arr[x][y] = 4;
	else arr[x][y] = 2;
}
void onlineinit() {
	closegraph();
	init();
	printf("The id you've got:%d\n", getnewcid());
	getlist();
	printf("Please choose your friend's id:\n");
	setfrid();
}
int operate() {
	NOMOV = 1;
	while (NOMOV && _getch() != 0x1B) switch (_getch()) {
	case 72: savestage(); merge(leftmove, leftadd); break;
	case 80: savestage(); merge(rightmove, rightadd); break;
	case 75: savestage(); merge(upmove, upadd); break;
	case 77: savestage(); merge(downmove, downadd); break;
	}
	return NOMOV;
}
void print2score() {
	if (ISWIN || ISFAIL) return;
	TCHAR my_score[5] = { 0 };
	TCHAR fri_score[5] = { 0 };
	_stprintf_s(my_score, _T("%hd"), calScore(arr));
	num_t.num = calScore(arr);
	sendscore();
	_stprintf_s(fri_score, _T("%hd"), recvscore() % 9999);
	setbkcolor(MEATCOLOR);
	setbkmode(OPAQUE);
	settextcolor(WHITE);
	outtextxy(63, 61, L"         ");
	outtextxy(257, 61, L"         ");
	outtextxy(65, 61, my_score);
	outtextxy(260, 61, fri_score);
	setbkmode(TRANSPARENT);
}
void printmyscore() {
	TCHAR my_score[5] = { 0 };
	_stprintf_s(my_score, _T("%hd"), calScore(arr));
	setbkcolor(MEATCOLOR);
	setbkmode(OPAQUE);
	settextcolor(WHITE);
	outtextxy(63, 61, L"         ");
	outtextxy(65, 61, my_score);
	setbkmode(TRANSPARENT);
}
int rightadd() {
	FLAG = 0;
	for (int j = 1; j <= 4; j++)
		switch ((arr[j][1] ? 8 : 0) + (arr[j][2] ? 4 : 0) + (arr[j][3] ? 2 : 0) + (arr[j][4] ? 1 : 0)) {
		case 0: case 1: break;
		case 3:
			if (arr[j][3] == arr[j][4]) {
				arr[j][4] *= 2;
				FLAG++;
				arr[j][3] = 0;
			}
			break;
		case 7:
			if (arr[j][3] == arr[j][4]) {
				arr[j][4] *= 2;
				FLAG++;
				arr[j][3] = arr[j][2];
				arr[j][2] = 0;
			}
			else if (arr[j][2] == arr[j][3]) {
				arr[j][3] *= 2;
				FLAG++;
				arr[j][2] = 0;
			}
			else FLAG++;
			break;
		case 15:
			if (arr[j][3] == arr[j][4]) {
				arr[j][4] *= 2;
				FLAG++;
				arr[j][3] = 0;
			}
			else if (arr[j][2] == arr[j][3]) {
				arr[j][3] *= 2;
				FLAG++;
				arr[j][2] = 0;
			}
			if (arr[j][1] == arr[j][2]) {
				arr[j][2] *= 2;
				FLAG++;
				arr[j][1] = 0;
			}
			rightmove();
			break;
		}
	return FLAG;
}
int rightmove() {
	FLAG2 = 0;
	for (int j = 1; j <= 4; j++)
		switch ((arr[j][1] ? 8 : 0) + (arr[j][2] ? 4 : 0) + (arr[j][3] ? 2 : 0) + (arr[j][4] ? 1 : 0)) {
		case 0: case 1: case 3: case 7: case 15: FLAG2++; break;
		case 2: arr[j][4] = arr[j][3]; arr[j][3] = 0; break;
		case 4: arr[j][4] = arr[j][2]; arr[j][2] = 0; break;
		case 5: arr[j][3] = arr[j][2]; arr[j][2] = 0; break;
		case 6: arr[j][4] = arr[j][3]; arr[j][3] = arr[j][2]; arr[j][2] = 0; break;
		case 8: arr[j][4] = arr[j][1]; arr[j][1] = 0; break;
		case 9: arr[j][3] = arr[j][1]; arr[j][1] = 0; break;
		case 10: arr[j][4] = arr[j][3]; arr[j][3] = arr[j][1]; arr[j][1] = 0; break;
		case 11: arr[j][2] = arr[j][1]; arr[j][1] = 0; break;
		case 12: arr[j][4] = arr[j][2]; arr[j][3] = arr[j][1]; arr[j][1] = arr[j][2] = 0; break;
		case 13: arr[j][3] = arr[j][2]; arr[j][2] = arr[j][1]; arr[j][1] = 0; break;
		case 14: arr[j][4] = arr[j][3]; arr[j][3] = arr[j][2]; arr[j][2] = arr[j][1]; arr[j][1] = 0; break;
		default: break;
		}
	return (FLAG2 == 4);
}
int upadd() {
	FLAG = 0;
	for (int j = 1; j <= 4; j++)
		switch ((arr[1][j] ? 8 : 0) + (arr[2][j] ? 4 : 0) + (arr[3][j] ? 2 : 0) + (arr[4][j] ? 1 : 0)) {
		case 0: case 8: break;
		case 12:
			if (arr[1][j] == arr[2][j]) {
				arr[1][j] *= 2;
				FLAG++;
				arr[2][j] = 0;
			}
			break;
		case 14:
			if (arr[1][j] == arr[2][j]) {
				arr[1][j] *= 2;
				FLAG++;
				arr[2][j] = arr[3][j];
				arr[3][j] = 0;
			}
			else if (arr[2][j] == arr[3][j]) {
				arr[2][j] *= 2;
				FLAG++;
				arr[3][j] = 0;
			}
			break;
		case 15:
			if (arr[1][j] == arr[2][j]) {
				arr[1][j] *= 2;
				FLAG++;
				arr[2][j] = 0;
			}
			else if (arr[2][j] == arr[3][j]) {
				arr[2][j] *= 2;
				FLAG++;
				arr[3][j] = 0;
			}
			if (arr[3][j] == arr[4][j]) {
				arr[3][j] *= 2;
				FLAG++;
				arr[4][j] = 0;
			}
			upmove();
			break;
		}
	return FLAG;
}
int upmove() {
	FLAG2 = 0;
	for (int j = 1; j <= 4; j++)
		switch ((arr[1][j] ? 8 : 0) + (arr[2][j] ? 4 : 0) + (arr[3][j] ? 2 : 0) + (arr[4][j] ? 1 : 0)) {
		case 0: case 8: case 12: case 14: case 15: FLAG2++; break;
		case 1: arr[1][j] = arr[4][j]; arr[4][j] = 0; break;
		case 2: arr[1][j] = arr[3][j]; arr[3][j] = 0; break;
		case 3: arr[1][j] = arr[3][j]; arr[2][j] = arr[4][j]; arr[3][j] = arr[4][j] = 0; break;
		case 4: arr[1][j] = arr[2][j]; arr[2][j] = 0; break;
		case 5: arr[1][j] = arr[2][j]; arr[2][j] = arr[4][j]; arr[4][j] = 0; break;
		case 6: arr[1][j] = arr[2][j]; arr[2][j] = arr[3][j]; arr[3][j] = 0; break;
		case 7: arr[1][j] = arr[2][j]; arr[2][j] = arr[3][j]; arr[3][j] = arr[4][j]; arr[4][j] = 0; break;
		case 9: arr[2][j] = arr[4][j]; arr[4][j] = 0; break;
		case 10: arr[2][j] = arr[3][j]; arr[3][j] = 0; break;
		case 11: arr[2][j] = arr[3][j]; arr[3][j] = arr[4][j]; arr[4][j] = 0; break;
		case 13: arr[3][j] = arr[4][j]; arr[4][j] = 0; break;
		default: break;
		}
	return (FLAG2 == 4);
}
