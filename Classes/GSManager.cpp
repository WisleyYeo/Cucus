#include "GSManager.h"


GSManager::GSManager()
{
	m_arrGem = NULL;
	sNodeSelected1 = NULL;
	sNodeSelected2 = NULL; 
	shNodeX = 0;
	shNodeY = 0;
}
void GSManager::Init()
{
	m_arrGem = new sNode*[MAX_HORIZONTAL];
	for (int i = 0; i < MAX_HORIZONTAL; i++) {
		m_arrGem[i] = new sNode[MAX_VERTICAL];
		for (int j = 0; j < MAX_VERTICAL; j++) {
			m_arrGem[i][j].gem = NULL;
		}
	}

	for (int i = 0; i < MAX_HORIZONTAL; i++) {
		for (int j = 0; j < MAX_VERTICAL; j++) {
			m_arrGem[i][j].gem = new Gem();
		}
	}

	

	m_eGameState = E_GAME_NORMAL;
	m_fdeltaTime = 0.0f;

}
void GSManager::update(float dt)
{
	m_fdeltaTime += dt;
	switch (m_eGameState) {
	case E_GAME_NORMAL:
		if (m_fdeltaTime > 1.0f) {
			CheckEntireArray();
			break;
		}
	case E_GAME_REMOVE:
		if (m_fdeltaTime > 1.0f) {
			RemoveGems();
			m_fdeltaTime = 0;
		}
		break;
	case E_GAME_CREATE:
		if (m_fdeltaTime > 1.0f) {
			ShiftGems();
			m_fdeltaTime = 0;
		}
		break;
	case E_GAME_REST:
		if (m_fdeltaTime > 1.0f) {
			m_eGameState = E_GAME_NORMAL;
		}
		break;
	default:
		m_eGameState = E_GAME_NORMAL;
		break;
	}
}
bool GSManager::CheckLowerX(USHORT x, USHORT y)
{
	if (x<2)return true;
	for (int i = 1; i < 3; i++)
	{
		if (m_arrGem[x][y].gem->getType() != m_arrGem[x - i][y].gem->getType())
			return true;
	}
	return false;
}
bool GSManager::CheckLowerY(USHORT x, USHORT y)
{
	if (y < 2) return true;
	for (int i = 1; i < 3; i++)
	{
		if (m_arrGem[x][y].gem->getType() != m_arrGem[x][y - i].gem->getType())
			return true;
	}
	return false;
}
void GSManager::CheckEntireArray()
{
	for (int i = 0; i < MAX_HORIZONTAL; ++i)
		for (int j = 0; j < MAX_VERTICAL; ++j) {
			if (!CheckLowerX(i, j)) {
				for (int k = 0; k < 3; k++) {
					m_arrGem[i - k][j].eState = E_GAME_REMOVE;
				}
				m_eGameState = E_GAME_REMOVE;
			}
			if (!CheckLowerY(i, j)) {
				for (int k = 0; k < 3; k++) {
					m_arrGem[i][j - k].eState = E_GAME_REMOVE;
				}
				m_eGameState = E_GAME_REMOVE;
			}
		}
}
void GSManager::RemoveGems()
{
	for (int i = 0; i<MAX_HORIZONTAL; ++i)
		for (int j = 0; j <MAX_VERTICAL; ++j)
			if (m_arrGem[i][j].eState == E_GAME_REMOVE)
				m_arrGem[i][j].gem->ChangeTexture(E_EMPTY);

	m_eGameState = E_GAME_CREATE;
}
void GSManager::ShiftGems()
{
	USHORT shCur;
	for (int i = 0; i<MAX_HORIZONTAL; ++i) {
		shCur = MAX_VERTICAL;
		for (int j = MAX_VERTICAL - 1; j >= 0; --j) {
			if (m_arrGem[i][j].eState == E_GAME_REMOVE) {
				if (shCur == MAX_VERTICAL)shCur = j;
			}
			else {
				if (shCur != MAX_VERTICAL) {
					m_arrGem[i][shCur].gem->ChangeTexture
					(m_arrGem[i][j].gem->getType());
					m_arrGem[i][shCur].eState = E_GAME_NORMAL;
					m_arrGem[i][j].gem->ChangeTexture(E_EMPTY);
					m_arrGem[i][j].eState = E_GAME_REMOVE;
					if (m_arrGem[i][shCur - 1].eState = E_GAME_REMOVE)
						shCur--;
					else
						shCur = j;
				}
			}
		}
	}
	CreateGems();
}
void GSManager::CreateGems()
{
	for (int i = 0; i<MAX_HORIZONTAL; ++i)
		for (int j = 0; j<MAX_VERTICAL; ++j)
			if (m_arrGem[i][j].eState == E_GAME_REMOVE) {
				m_arrGem[i][j].gem->ChangeTexture((
					E_GEM_TYPES)(INT)(CCRANDOM_0_1()*(E_TOTAL - 1)));
				m_arrGem[i][j].eState = E_GAME_REST;
			}
	m_eGameState = E_GAME_REST;
}
void GSManager::SwapGem(void)
{
	E_GEM_TYPES eGemType = sNodeSelected2->gem->getType();
	sNodeSelected2->gem->ChangeTexture(sNodeSelected1->gem->getType());
	sNodeSelected1->gem->ChangeTexture(eGemType);
}
bool GSManager::CheckSingleGem(USHORT x, USHORT y)
{
	for (int i = 0; i < MAX_HORIZONTAL; i++)
		if (!CheckLowerX(i, y))
			return true;
	for (int i = 0; i < MAX_VERTICAL; i++)
		if (!CheckLowerY(x, i))
			return true;
	return false;
}
GSManager::~GSManager()
{
	if (m_arrGem != NULL)
	{
		delete m_arrGem;
		m_arrGem = NULL;
	}
}
