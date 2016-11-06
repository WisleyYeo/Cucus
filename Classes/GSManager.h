#pragma once
#include "Gem.h"
class GSManager
{
public:
	GSManager();
	~GSManager(); 
	enum ESTATE {
		E_GAME_NORMAL,
		E_GAME_REMOVE,
		E_GAME_CREATE,
		E_GAME_REST,
		E_GAME_TOTAL
	};
	struct sNode {
		Gem* gem;
		ESTATE eState;
	};
#define MAX_HORIZONTAL 10
#define MAX_VERTICAL 10
	sNode **m_arrGem;
	sNode* sNodeSelected1;
	sNode* sNodeSelected2;
	USHORT shNodeX, shNodeY;
	void Init(void);
	void CheckEntireArray(void);
	void RemoveGems(void);
	void ShiftGems(void);
	void CreateGems(void);
	virtual void update(float);

	ESTATE m_eGameState;
	float m_fdeltaTime;

	bool CheckLowerX(USHORT x, USHORT y);
	bool CheckLowerY(USHORT x, USHORT y);

	void SwapGem(void);
	bool CheckSingleGem(USHORT x, USHORT y);
};

