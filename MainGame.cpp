#include "pch.h"
#include "MainGame.h"
#include "AbstractFactory.h"


MainGame::MainGame() : m_hDC(0), m_pPlayer(nullptr), m_pMonster(nullptr), m_pPet(nullptr), m_iStage(1), m_iScore(0), m_dwTime(GetTickCount64()), m_pMouse(nullptr)
{
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	srand(unsigned int(time(NULL)));	//몬스터 랜덤 생성을 위해

	if (!m_pUI)
	{
		m_pUI = new UI;
		m_pUI->Initialize();
	}

	if (!m_pMouse)
	{
		m_pMouse = new Mouse;
		m_pMouse->Initialize();
		m_pMouse->Set_UIInfo(m_pUI);
	}


	//플레이어 생성
	if (!m_pPlayer)
	{
		m_pPlayer = new Player;

		m_pPlayer->Initialize();

		m_ObjList[OBJ_PLAYER].push_back(m_pPlayer);

	}

	for (int i = 0; i < 1; ++i)
	{
		m_ObjList[OBJ_MONSTER].push_back(new Monster(20.f, 20.f, 300.f, 400.f, 0.f));
	}

	for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();
		iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		(*iter)->Initialize();
	}

	// 펫 생성
	if (nullptr == m_pPet)
	{
		m_pPet = new Pet;

		//m_pPet->Initialize();	//펫 이니셜라이즈는 밑에서

		m_ObjList[OBJ_PET].push_back(m_pPet);
	}

	//각 Obj 마다 총알 리스트 주소 넘겨줌
	for (size_t i = 0; i < OBJ_SHIELD; ++i)  //쉴드는 총알을 가질 수 없음
	{
		m_ObjList[i].back()->Get_List(&m_BulletList);
	}

	//플레이어가 접근해야 하는 리스트의 주소들 넘겨줌
	dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].back())->Get_ListShield(&m_ObjList[OBJ_SHIELD]);
//	dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].back())->Get_List(&m_BulletList);
	dynamic_cast<Pet*>(m_ObjList[OBJ_PET].back())->Get_List(&m_BulletList);
//	dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].back())->Get_ListScrewBullet(&m_ScrewBulletList);
	//펫 -> 몬스터 타겟 설정
	dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].back())->Get_Monster(&m_ObjList[OBJ_MONSTER]);
	dynamic_cast<Pet*>(m_ObjList[OBJ_PET].back())->Get_Monster(&m_ObjList[OBJ_MONSTER]);


	m_ObjList[OBJ_BOSS].push_back(CAbstractFactory<Boss_Monster>::Create()); // 보스 생성후에 BOSS 리스트에 넣기
	dynamic_cast<Boss_Monster*>(m_ObjList[OBJ_BOSS].front())->Set_Bullet(&m_ObjList[OBJ_BOSS_BULLET]); // 보스 총알 생성할시 바로 보스에게 전달

}

void MainGame::Update()
{
	m_pUI->Update();

	if (!static_cast<Mouse*>(m_pMouse)->m_bStart)
	{
		m_pMouse->Update();
	}

	if(static_cast<Mouse*>(m_pMouse)->m_bStart) // 게임 시작 버튼 이후
	{
		m_ObjList[OBJ_PLAYER].back()->Update();

		for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();
			iter != m_ObjList[OBJ_MONSTER].end();)
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				++m_iScore;
				Safe_Delete<BaseObj*>(*iter);
				iter = m_ObjList[OBJ_MONSTER].erase(iter);
			}

			else
				++iter;
		}

		//펫 이니셜라이즈 및 업데이트
		dynamic_cast<Pet*>(m_ObjList[OBJ_PET].back())->Initialize(m_ObjList[OBJ_PLAYER].back()->Get_Info().fX, m_ObjList[OBJ_PLAYER].back()->Get_Info().fY);
		m_ObjList[OBJ_PET].back()->Update();


		//쉴드 업데이트(충돌 시 삭제처리도 같이)
		for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_SHIELD].begin();
			iter != m_ObjList[OBJ_SHIELD].end();)
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				++m_iScore;
				Safe_Delete<BaseObj*>(*iter);
				iter = m_ObjList[OBJ_SHIELD].erase(iter);
			}

			else
				++iter;
		}

		//총알 업데이트(충돌 시 삭제처리도 같이)
		for (list<BaseObj*>::iterator iter = m_BulletList.begin();
			iter != m_BulletList.end();)
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<BaseObj*>(*iter);
				iter = m_BulletList.erase(iter);
			}

			else
				++iter;
		}

		//회전하는 총알 업데이트(충돌 시 삭제처리도 같이)
		for (list<BaseObj*>::iterator iter = m_ScrewBulletList.begin();
			iter != m_ScrewBulletList.end();)
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<BaseObj*>(*iter);
				iter = m_ScrewBulletList.erase(iter);
			}

			else
				++iter;
		}

		// 멈춰있는 총알 
		for (auto* pObj : m_ObjList[OBJ_BOSS_BULLET]) // 리스트 안의 모든 객체 탐색
		{
			Boss_Bullet* pBullet = dynamic_cast<Boss_Bullet*>(pObj); // 캐스팅
			if (m_ObjList[OBJ_BOSS_BULLET].size() == 5) // 스피드가 0인 총알 확인
			{
				pBullet->SetSpeed(5.f);
			}
		}

	} // 코드 추가는 이 줄 위로
}

void MainGame::Late_Update()
{
	if (!static_cast<Mouse*>(m_pMouse)->m_bStart)
	{
		m_pMouse->Late_Update();
	}
	
	
	//플레이어 레이트 업데이트
	m_ObjList[OBJ_PLAYER].back()->Late_Update();

	//몬스터 레이트 업데이트
	for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();
		iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		(*iter)->Late_Update();
	}

	//펫 레이트 업데이트
	m_ObjList[OBJ_PET].back()->Late_Update();

	//총알 레이트 업데이트
	for (list<BaseObj*>::iterator iter = m_BulletList.begin();
		iter != m_BulletList.end(); ++iter)
	{
		(*iter)->Late_Update();
	}

	//스크류 총알 레이트 업데이트
	for (list<BaseObj*>::iterator iter = m_ScrewBulletList.begin();
		iter != m_ScrewBulletList.end(); ++iter)
	{
		(*iter)->Late_Update();
	}

}

void MainGame::Render()
{
	if (!static_cast<Mouse*>(m_pMouse)->m_bStart)
	{
		m_pUI->Render(m_hDC);
		m_pMouse->Render(m_hDC);
	}
	
	else
	{
	
	
	//배경 사각형 그리기
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	//게임 범위 사각형 그리기
	Rectangle(m_hDC, WINCX - 200, 0, WINCX, WINCY);

	// 각종 텍스트 출력
	//Render_BulletNumber();
	//Render_Score();
	//Render_Stage();

	//플레이어 출력
	m_ObjList[OBJ_PLAYER].back()->Render(m_hDC);

	////몬스터 출력(사망 상태가 아닐시에만 출력)
	for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();
		iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		if (false == (*iter)->Get_Dead())
		{
			(*iter)->Render(m_hDC);
		}
	}

	////펫 출력(사망 상태가 아닐시에만 출력)
	//m_ObjList[OBJ_PET].back()->Render(m_hDC);

	////쉴드 출력(사망 상태가 아닐시에만 출력)
	//for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_SHIELD].begin();
	//	iter != m_ObjList[OBJ_SHIELD].end(); ++iter)
	//{
	//	if (false == (*iter)->Get_Dead())
	//	{
	//		(*iter)->Render(m_hDC);
	//	}
	//}

	//총알 출력(사망 상태가 아닐시에만 출력)
	for (list<BaseObj*>::iterator iter = m_BulletList.begin();
		iter != m_BulletList.end(); ++iter)
	{
		if (false == (*iter)->Get_Dead())
		{
			(*iter)->Render(m_hDC);
		}
	}

	////회전하는 총알 출력(사망 상태가 아닐시에만 출력)
	//for (list<BaseObj*>::iterator iter = m_ScrewBulletList.begin();
	//	iter != m_ScrewBulletList.end(); ++iter)
	//{
	//	if (false == (*iter)->Get_Dead())
	//	{
	//		(*iter)->Render(m_hDC);
	//	}
	//}

	}
}

void MainGame::Release()
{
	for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_PLAYER].begin();
		iter != m_ObjList[OBJ_PLAYER].end(); ++iter)
	{
		Safe_Delete<BaseObj*>(*iter);
	}
	m_ObjList[OBJ_PLAYER].clear();

	for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();
		iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		Safe_Delete<BaseObj*>(*iter);
	}
	m_ObjList[OBJ_MONSTER].clear();

	for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_PET].begin();
		iter != m_ObjList[OBJ_PET].end(); ++iter)
	{
		Safe_Delete<BaseObj*>(*iter);
	}
	m_ObjList[OBJ_PET].clear();

	for (list<BaseObj*>::iterator iter = m_BulletList.begin();
		iter != m_BulletList.end(); ++iter)
	{
		Safe_Delete<BaseObj*>(*iter);
	}
	m_BulletList.clear();

	for (list<BaseObj*>::iterator iter = m_ScrewBulletList.begin();
		iter != m_ScrewBulletList.end(); ++iter)
	{
		Safe_Delete<BaseObj*>(*iter);
	}
	m_ScrewBulletList.clear();

	ReleaseDC(g_hWnd, m_hDC);
}

