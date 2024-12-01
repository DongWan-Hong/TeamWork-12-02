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

	srand(unsigned int(time(NULL)));	//���� ���� ������ ����

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


	//�÷��̾� ����
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

	// �� ����
	if (nullptr == m_pPet)
	{
		m_pPet = new Pet;

		//m_pPet->Initialize();	//�� �̴ϼȶ������ �ؿ���

		m_ObjList[OBJ_PET].push_back(m_pPet);
	}

	//�� Obj ���� �Ѿ� ����Ʈ �ּ� �Ѱ���
	for (size_t i = 0; i < OBJ_SHIELD; ++i)  //����� �Ѿ��� ���� �� ����
	{
		m_ObjList[i].back()->Get_List(&m_BulletList);
	}

	//�÷��̾ �����ؾ� �ϴ� ����Ʈ�� �ּҵ� �Ѱ���
	dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].back())->Get_ListShield(&m_ObjList[OBJ_SHIELD]);
//	dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].back())->Get_List(&m_BulletList);
	dynamic_cast<Pet*>(m_ObjList[OBJ_PET].back())->Get_List(&m_BulletList);
//	dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].back())->Get_ListScrewBullet(&m_ScrewBulletList);
	//�� -> ���� Ÿ�� ����
	dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].back())->Get_Monster(&m_ObjList[OBJ_MONSTER]);
	dynamic_cast<Pet*>(m_ObjList[OBJ_PET].back())->Get_Monster(&m_ObjList[OBJ_MONSTER]);


	m_ObjList[OBJ_BOSS].push_back(CAbstractFactory<Boss_Monster>::Create()); // ���� �����Ŀ� BOSS ����Ʈ�� �ֱ�
	dynamic_cast<Boss_Monster*>(m_ObjList[OBJ_BOSS].front())->Set_Bullet(&m_ObjList[OBJ_BOSS_BULLET]); // ���� �Ѿ� �����ҽ� �ٷ� �������� ����

}

void MainGame::Update()
{
	m_pUI->Update();

	if (!static_cast<Mouse*>(m_pMouse)->m_bStart)
	{
		m_pMouse->Update();
	}

	if(static_cast<Mouse*>(m_pMouse)->m_bStart) // ���� ���� ��ư ����
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

		//�� �̴ϼȶ����� �� ������Ʈ
		dynamic_cast<Pet*>(m_ObjList[OBJ_PET].back())->Initialize(m_ObjList[OBJ_PLAYER].back()->Get_Info().fX, m_ObjList[OBJ_PLAYER].back()->Get_Info().fY);
		m_ObjList[OBJ_PET].back()->Update();


		//���� ������Ʈ(�浹 �� ����ó���� ����)
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

		//�Ѿ� ������Ʈ(�浹 �� ����ó���� ����)
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

		//ȸ���ϴ� �Ѿ� ������Ʈ(�浹 �� ����ó���� ����)
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

		// �����ִ� �Ѿ� 
		for (auto* pObj : m_ObjList[OBJ_BOSS_BULLET]) // ����Ʈ ���� ��� ��ü Ž��
		{
			Boss_Bullet* pBullet = dynamic_cast<Boss_Bullet*>(pObj); // ĳ����
			if (m_ObjList[OBJ_BOSS_BULLET].size() == 5) // ���ǵ尡 0�� �Ѿ� Ȯ��
			{
				pBullet->SetSpeed(5.f);
			}
		}

	} // �ڵ� �߰��� �� �� ����
}

void MainGame::Late_Update()
{
	if (!static_cast<Mouse*>(m_pMouse)->m_bStart)
	{
		m_pMouse->Late_Update();
	}
	
	
	//�÷��̾� ����Ʈ ������Ʈ
	m_ObjList[OBJ_PLAYER].back()->Late_Update();

	//���� ����Ʈ ������Ʈ
	for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();
		iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		(*iter)->Late_Update();
	}

	//�� ����Ʈ ������Ʈ
	m_ObjList[OBJ_PET].back()->Late_Update();

	//�Ѿ� ����Ʈ ������Ʈ
	for (list<BaseObj*>::iterator iter = m_BulletList.begin();
		iter != m_BulletList.end(); ++iter)
	{
		(*iter)->Late_Update();
	}

	//��ũ�� �Ѿ� ����Ʈ ������Ʈ
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
	
	
	//��� �簢�� �׸���
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	//���� ���� �簢�� �׸���
	Rectangle(m_hDC, WINCX - 200, 0, WINCX, WINCY);

	// ���� �ؽ�Ʈ ���
	//Render_BulletNumber();
	//Render_Score();
	//Render_Stage();

	//�÷��̾� ���
	m_ObjList[OBJ_PLAYER].back()->Render(m_hDC);

	////���� ���(��� ���°� �ƴҽÿ��� ���)
	for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();
		iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		if (false == (*iter)->Get_Dead())
		{
			(*iter)->Render(m_hDC);
		}
	}

	////�� ���(��� ���°� �ƴҽÿ��� ���)
	//m_ObjList[OBJ_PET].back()->Render(m_hDC);

	////���� ���(��� ���°� �ƴҽÿ��� ���)
	//for (list<BaseObj*>::iterator iter = m_ObjList[OBJ_SHIELD].begin();
	//	iter != m_ObjList[OBJ_SHIELD].end(); ++iter)
	//{
	//	if (false == (*iter)->Get_Dead())
	//	{
	//		(*iter)->Render(m_hDC);
	//	}
	//}

	//�Ѿ� ���(��� ���°� �ƴҽÿ��� ���)
	for (list<BaseObj*>::iterator iter = m_BulletList.begin();
		iter != m_BulletList.end(); ++iter)
	{
		if (false == (*iter)->Get_Dead())
		{
			(*iter)->Render(m_hDC);
		}
	}

	////ȸ���ϴ� �Ѿ� ���(��� ���°� �ƴҽÿ��� ���)
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

