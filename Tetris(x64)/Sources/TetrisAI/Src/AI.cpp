/**
 * \file AI.cpp 
 * \brief Artificial Intelligence
 */

#include "AI.h"
#include "../../Tetris/Src/TetrisLogic/TetrisPiece.h"
#include "../../Tetris/Src/Event/EventManager.h"
#include "../../Tetris/Src/Event/Events/Evt_NewTetrisLoop.h"

AI::AI(Client *pClient):
m_pClient(pClient)
{
}

AI::~AI()
{
	SAFE_DELETE(m_pGrid);
	UnregisterEvents();
}

bool AI::Init()
{
	m_pGrid = new GridInfo(10, 20);
	RegisterEvents();
	
	return true;
}

void AI::CalculateAI()
{
	TetrisPiece *pPiece = new TetrisPiece(m_pieceType);

	int bestRotation = -1;
	int bestPosition = -1;
	float bestScore = -10000;
	float currentScore;

	for(int i=0; i<4; i++) //for each rotation
	{
		for(int j=0; j<m_pGrid->GetWidth(); j++)
		{
			pPiece->InitPosition(j, 2);
			if(CheckCollision(pPiece))
				continue;
			
			currentScore = CalculateScore(pPiece);
			if(currentScore > bestScore)
			{
				bestRotation = i;
				bestPosition = j;
				bestScore = currentScore;
			}
		}
		
		if(pPiece->GetPieceType() == PT_OBLOCK)
			break;
		
		pPiece->RotateRight();
	}
	
	INFO(bestScore);
	
	if(bestScore != -10000) //perform moves
	{
		for(int i=0; i<bestRotation; i++)
			SendMessage(GI_ROTATE);
		
		int initPosition = (m_pGrid->GetWidth()-1)/2;
		eGameInput input = (initPosition - bestPosition > 0)? GI_MOVELEFT : GI_MOVERIGHT;
		
		for(int i=0; i<fabs(initPosition - bestPosition); i++)
			SendMessage(input);
	}
	
	SendMessage(GI_DROP);
	
	delete pPiece;
}

bool AI::CheckCollision(TetrisPiece *pPiece)
{
	int **positions = pPiece->GetPositions();
	int centerX = pPiece->GetCenterX();
	int centerY = pPiece->GetCenterY();
	int gridWidth = m_pGrid->GetWidth();
	int gridHeight = m_pGrid->GetHeight();
	
	if(centerX < 0 || centerX >= gridWidth || centerY < 0 || centerY >= gridHeight)
		return true;
		
	if(m_pGrid->Get(centerX, centerY))
		return true;
		
	for(int i=0; i<3; i++)
	{
		int x = centerX + positions[i][0];
		int y = centerY + positions[i][1];
		
		if(x < 0 || x >= gridWidth || y < 0 || y >= gridHeight)
			return true;
			
		if(m_pGrid->Get(x, y))
			return true;
	}
		
	return false;
}

void AI::SendMessage(eGameInput input)
{
	EventSharedPtr pEvt;
	pEvt.reset(new Evt_MainGameInput(input));
	std::ostringstream oss;
	pEvt->VSerialize(oss);
	
	m_pClient->Send(oss);	
}

void AI::DropPiece(TetrisPiece *pPiece)
{
	do
	{
		pPiece->Move(0, 1);
	}
	while(!CheckCollision(pPiece));
	pPiece->Move(0, -1);
}

float AI::CalculateScore(TetrisPiece *pPiece)
{
	DropPiece(pPiece);
	GridInfo *pTempGrid = m_pGrid->GetDuplicate();
	
	//RowNbTest must always be the first test
	int rowsNb = RowsNbTest(pTempGrid, pPiece);
	float height = AverageHeightTest(pPiece);
	int holesNb = HolesNbTest(pTempGrid);
	int pipesNb = PipesNbTest(pTempGrid);
	
	float cHeight = 1.0f;
	float cHoles = -2.5f;
	float cRows = 1.0f;
	float cPipes = -1.0f;
	
	float result = cHeight*height + cHoles*holesNb + cRows*rowsNb + cPipes*pipesNb;
	
	delete pTempGrid;
	
	return result;
}

int AI::RowsNbTest(GridInfo *pGrid, TetrisPiece *pPiece)
{
	int **positions = pPiece->GetPositions();
	int centerY = pPiece->GetCenterY();
	int centerX = pPiece->GetCenterX();
	
	pGrid->SetBlock(centerX, centerY, true);
	for(int i = 0; i < 3; i++)
	{
		pGrid->SetBlock(centerX + positions[i][0], centerY + positions[i][1], true);
	}
	
	int rowNb = 0;
	for(int j=0; j<pGrid->GetHeight(); j++)
	{
		for(int i=0; i<pGrid->GetWidth(); i++)
		{
			if(!pGrid->Get(i, j))
				break;
			else if(i == pGrid->GetWidth()-1)
			{		
				rowNb++;
				pGrid->DeleteLine(j);
			}
		}
	}
	
	return rowNb;
}

float AI::AverageHeightTest(TetrisPiece *pPiece)
{
	int **positions = pPiece->GetPositions();
	int centerY = pPiece->GetCenterY();
	float totalHeight = centerY;
	
	for(int i=0; i<3; i++)
		totalHeight += centerY + positions[i][1];
	
	return totalHeight/4.0f;
}

int AI::HolesNbTest(GridInfo *pGrid)
{
	int holesNb = 0;
	
	for(int i=0; i<pGrid->GetWidth(); i++)
	{
		bool foundBlock = false;
		for(int j=0; j<pGrid->GetHeight(); j++)
		{
			if(pGrid->Get(i, j))
				foundBlock = true;
			else if(foundBlock)
				holesNb++;
		}
	}
	
	return holesNb;
}

int AI::PipesNbTest(GridInfo *pGrid)
{
	int pipesNb = 0;
	int pipeIncr = 0;
	
	for(int j=0; j<pGrid->GetHeight(); j++)
	{
		if(!pGrid->Get(0, j) && pGrid->Get(1, j) && !pipeIncr)
		{	
			pipesNb += 1;
			pipeIncr += 1;
		}
		else if(!pGrid->Get(0, j) && pipeIncr)
		{
			pipesNb += pipeIncr;
			pipeIncr += 1;
		}
		else if(pGrid->Get(0, j))
			pipeIncr = 0;
	}
	
	pipeIncr = 0;
	for(int j=0; j<pGrid->GetHeight(); j++)
	{
		if(!pGrid->Get(pGrid->GetWidth()-1, j) && pGrid->Get(pGrid->GetWidth()-2, j) && !pipeIncr)
		{	
			pipesNb += 1;
			pipeIncr += 1;
		}
		else if(!pGrid->Get(pGrid->GetWidth()-1, j) && pipeIncr)
		{
			pipesNb += pipeIncr;
			pipeIncr += 1;
		}
		else if(pGrid->Get(pGrid->GetWidth()-1, j))
			pipeIncr = 0;
	}
	
	for(int i=1; i<pGrid->GetWidth()-1; i++)
	{
		pipeIncr = 0;
		for(int j=0; j<pGrid->GetHeight(); j++)
		{
			if(!pGrid->Get(i, j) && pGrid->Get(i+1, j) && pGrid->Get(i-1, j) && !pipeIncr)
			{	
				pipesNb += 1;
				pipeIncr += 1;
			}
			else if(!pGrid->Get(i, j) && pipeIncr)
			{
				pipesNb += pipeIncr;
				pipeIncr += 1;
			}
			else if(pGrid->Get(i, j))
				pipeIncr = 0;
		}
	}
	
	return pipesNb;
}

void AI::NewTetrisLoopDelegate(EventSharedPtr pEvent)
{
	shared_ptr<Evt_NewTetrisLoop> pEvt = static_pointer_cast<Evt_NewTetrisLoop>(pEvent);
	m_pGrid->Set(pEvt->GetGrid());
	m_pieceType = pEvt->GetPieceType();
	
	CalculateAI();
}

void AI::RegisterEvents()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &AI::NewTetrisLoopDelegate), ET_NEWTETRISLOOP);
}

void AI::UnregisterEvents()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &AI::NewTetrisLoopDelegate), ET_NEWTETRISLOOP);
}
