#pragma once
#include "Define.h"

class BaseObj
{
public:
	BaseObj();
	BaseObj(float _fCX, float _fCY, float _fX, float _fY, float _fSpeed);
	virtual ~BaseObj();

public:
	virtual void Initialize()PURE;
	virtual int	 Update()PURE;
	virtual void Late_Update()PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()PURE;

public:
	void		Update_Rect(); // 도형 업데이트 함수
	void		Set_UIInfo(BaseObj* pUIInfo) { m_pUIInfo = pUIInfo; }


	// 겟함수

////////// 동완

public: 

	RECT* Get_Rec() { return&m_tRect; }
	float Get_Speed() { return m_fSpeed; }
	INFO Get_Info() { return m_tInfo; } // 도형의 중심좌표와 가로 세로의 길이 반환

////////// 현석

public:
	const RECT* Get_Rect() { return &m_tRect; }
	bool Get_Dead() { return m_bDead; }


	////////// 셋 함수

	/////// 동완

public: // 셋함수
	void	Set_Pos(float _fX, float _fY, float _fCX, float _fXY) // 중심좌표 셋 함수
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fXY;
	}
	void	Set_Pos(float _fX, float _fY) // 중심좌표 셋 함수
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void Set_Speed(float _type) { m_fSpeed = _type; }
	void Set_Ang(float _Angle) { m_fAngle = _Angle; }
	//void Set_Dead() { bDead = true; }

	/////// 현석


	void Set_Pos(LONG _pX, LONG _pY)	//중점을 설정하는 함수
	{
		m_tInfo.fX = float(_pX);
		m_tInfo.fY = float(_pY);
	}

	void Set_Angle(float _fAngle){ m_fAngle = _fAngle; }
	void Set_Dead() { m_bDead = true; }
	void Set_Target(BaseObj* pTarget) { m_pTarget = pTarget; }

	//총알 리스트 주소를 넘겨주는 함수
	virtual void Get_List(list<BaseObj*>* pList)PURE;
	//총알을 생성하는 함수
	virtual BaseObj* CreateBullet(BULLETDIRECTION _eDriect)PURE;

	void	BSet_Pos(float _fX, float _fY) 
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

protected:
	//현석
	INFO	m_tInfo;
	RECT	m_tRect;
	WALL	m_wWall;
	list<BaseObj*>* m_pBulletList;
	ULONG64	m_Time;
	

	float	m_fSpeed;
	float	m_fAngle;
	float	m_fAngleSpeed;
	float	m_fAngleAccel;
	float	m_fDistance;
	bool	m_bDead;

	BaseObj* m_pTarget;
	

	// 동완
	bool bDead;
	float f_radius;

	// 현우
	BaseObj* m_pUIInfo;
	
};