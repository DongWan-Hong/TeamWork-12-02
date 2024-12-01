#pragma once
#include "BaseObj.h"
#include "Bullet.h"
#include "Pet.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "Monster.h"

enum Bullet_Direction { Up, Down, Right, Left, first, second };

class Player : public BaseObj
{
public:
	Player();
	virtual ~Player();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	virtual void		Get_List(list<BaseObj*>* pList) override;
	virtual BaseObj*	CreateBullet(BULLETDIRECTION _eDriect) override;

	void Get_ListShield(list<BaseObj*>* pListShield);
	//void Get_ListScrewBullet(list<BaseObj*>* pListScrewBullet);
	void Get_Monster(list<BaseObj*>* pMonster) { m_pMonsterList = pMonster; }

	

	//void        Set_Bullet(list<BaseObj*>* pBullet) { m_pBullet = pBullet; }

public:
	void		Key_Input();
	BaseObj*	CreateShield();
//	BaseObj*	CreateScrewBullet(BULLETMYDIRECTION _eDriect);

private:
	list<BaseObj*>* m_pBulletList;
	list<BaseObj*>* m_pShieldList;
//	list<BaseObj*>* m_pScrewBulletList;
	list<BaseObj*>* m_pMonsterList; //Ÿ�� ������ ����
	list<BaseObj*>* m_pBullet;
	POINT			m_tPosin;
	BaseObj*		m_pPet;
	unsigned long long m_ullLast_Fire;
	Bullet_Direction Bullet_Di;

	float m_fOrbit_Gap;    // �÷��̾���� �Ÿ�
	float m_fOrbitSpeed;     // ���� �ӵ�
	float m_fOrbitAngle;     // ���� ����
	POINT m_tOrbitP_Ob;       // �����ϴ� ���׶���� ���� ��ǥ


};

