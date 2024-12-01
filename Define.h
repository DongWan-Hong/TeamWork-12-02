#pragma once

#define WINCX	800
#define WINCY	600

#define PURE	= 0
#define PI		3.14

#define OBJ_NOEVENT 0
#define OBJ_DEAD	1

extern HWND		g_hWnd;

template<typename T>
void Safe_Delete(T& temp)
{
	if (temp)
	{
		delete temp;
		temp = nullptr;
	}
}

typedef struct tagInfo
{
	float fX, fY;   // 중점
	float fCX, fCY; // 가로, 세로 길이
}INFO;

typedef struct tagWinfo
{
	LONG Lleft = LONG(20.f);
	LONG Ltop = LONG(10.f);
	LONG Lright = LONG(WINCX - 200.f);
	LONG Lbottom = LONG(WINCY - 20.f);
}WALL;


// Object ID
enum OBJID { OBJ_PLAYER, OBJ_MONSTER, OBJ_PET, OBJ_SHIELD, OBJ_BULLET, OBJ_BOSS, OBJ_BOSS_BULLET, OBJ_BUTTON, OBJ_END};


// Direction
enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };


// Bullet Direction
enum BULLETDIRECTION { DL_UP, DL_LUP, DL_RUP, DL_STAR, DL_CLOVER, DL_MY, DL_CHARSE, DL_POSIN, DL_ROTATE, DL_END };
enum BULLETSHAPE { DS_BASE, DS_MY, DS_END };
enum BULLETMYDIRECTION { MY_UP, MY_LUP, MY_RUP, MY_DOWN, MY_LDOWN, MY_RDOWN, MY_LEFT, MY_RIGHT, MY_CENTER, MY_PRACTICE };