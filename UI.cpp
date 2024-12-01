#include "pch.h"
#include "UI.h"

UI::UI()
{
	ZeroMemory(m_szStart, sizeof(m_szStart));
}

UI::~UI()	
{
	Release();
}

void UI::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 120.f, 100.f }; // GameStart 박스 크기
	_tcscpy_s(m_szStart, _T("Game Start"));
}

int UI::Update()
{
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void UI::Late_Update()
{
}

void UI::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom
	);

	// Game Start 텍스트 위치
	TextOut(hDC, static_cast<int>(m_tInfo.fX) - 35, static_cast<int>(m_tInfo.fY) - 8,
		m_szStart, static_cast<int>(_tcslen(m_szStart)));
}

void UI::Release()
{
}

void UI::Get_List(list<BaseObj*>* pList)
{
}

BaseObj* UI::CreateBullet(BULLETDIRECTION _eDriect)
{
	return nullptr;
}
