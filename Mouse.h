#pragma once
#include "BaseObj.h"
class Mouse : public BaseObj
{
public:
	Mouse();
	virtual ~Mouse();

public:
	virtual void	Initialize()override;
	virtual int		Update()override;
	virtual void	Late_Update()override;
	virtual void	Render(HDC hDC)override;
	virtual void	Release()override;

	virtual void Get_List(list<BaseObj*>* pList);
	virtual BaseObj* CreateBullet(BULLETDIRECTION _eDriect);

public:
	bool m_bStart;

private:
	bool	LeftClickCheck() const;
	bool	MouseOverUI(const RECT& UIRect);

};

