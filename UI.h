#pragma once
#include "BaseObj.h"

class UI : public BaseObj
{
public:
	UI();
	virtual ~UI();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	virtual void Get_List(list<BaseObj*>* pList);
	virtual BaseObj* CreateBullet(BULLETDIRECTION _eDriect);


private:
	TCHAR		m_szStart[32];

};

