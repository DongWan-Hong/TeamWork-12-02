#include "pch.h"
#include "Mouse.h"

Mouse::Mouse() : m_bStart(false)
{
}

Mouse::~Mouse()
{
    Release();
}

void Mouse::Initialize()
{
    m_tInfo.fCX = 40.f;
    m_tInfo.fCY = 40.f;
}

int Mouse::Update()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	return OBJ_NOEVENT;
}

void Mouse::Late_Update()
{
	const RECT* pUIRect = m_pUIInfo->Get_Rect();
	MouseOverUI(*pUIRect);
	LeftClickCheck();

	if (pUIRect && MouseOverUI(*pUIRect) && LeftClickCheck()) {
		m_bStart = true;
	}

}

void Mouse::Render(HDC hDC)
{
}

void Mouse::Release()
{
}

void Mouse::Get_List(list<BaseObj*>* pList)
{
}

BaseObj* Mouse::CreateBullet(BULLETDIRECTION _eDriect)
{
	return nullptr;
}

bool Mouse::LeftClickCheck() const
{
	return (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
}

bool Mouse::MouseOverUI(const RECT& UIRect)
{
	return (m_tInfo.fX >= UIRect.left && m_tInfo.fX <= UIRect.right &&
		m_tInfo.fY >= UIRect.top && m_tInfo.fY <= UIRect.bottom);
}
