#pragma once
#include "Define.h"
#include "Player.h"
#include "Monster.h"
#include "CollisionMgr.h"
#include "Pet.h"
#include "ScrewBullet.h"
#include "Mouse.h"
#include "UI.h"
#include "Boss_Monster.h"
#include "Boss_Bullet.h"



class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render();
	void	Release();

private:
	HDC			m_hDC;
	list<BaseObj*> m_ObjList[OBJ_END];
	BaseObj* m_pPlayer;
	BaseObj* m_pMonster;
	BaseObj* m_pPet;
	BaseObj* m_pUI;
	BaseObj* m_pMouse;

	list<BaseObj*> m_BulletList;
	list<BaseObj*> m_ScrewBulletList;


	ULONG64	m_dwTime;
	int		m_iStage;
	int		m_iScore;
	WALL	m_wWall;


};

