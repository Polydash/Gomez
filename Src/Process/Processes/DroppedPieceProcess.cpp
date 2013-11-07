#include "DroppedPieceProcess.h"
#include "DeleteLinesProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"

DroppedPieceProcess::DroppedPieceProcess(TetrisGrid *pGrid, TetrisPiece *pPiece, GfxImageSharedPtr pImage):
m_pGrid(pGrid),
m_pPiece(pPiece),
m_pImage(pImage),
m_accel(0.75f),
m_speed(0.0f),
m_maxSpeed(15.0f)
{
}

DroppedPieceProcess::~DroppedPieceProcess()
{
	SAFE_DELETE(m_pPiece);
}

void DroppedPieceProcess::SetVelocity(float accel, float maxSpeed)
{
	m_accel = accel;
	m_maxSpeed = maxSpeed;
}

void DroppedPieceProcess::VUpdate(unsigned int elapsedTime)
{
	float diff = fabs(m_pImage->GetPosY() - ((m_pPiece->GetCenterY()+0.5f)*TetrisGfxBlock::s_pieceSize + 60));
	
	m_speed += m_accel;
	
	if(m_speed > m_maxSpeed)
		m_speed = m_maxSpeed;
	
	if(diff < m_speed)
	{
		float x = m_pImage->GetPosX();
		m_pImage->SetPosition(x, (m_pPiece->GetCenterY()+0.5f)*TetrisGfxBlock::s_pieceSize + 60);
		Success();
	}
	else
	{
		m_pImage->Translate(0, m_speed);
	}
}

bool DroppedPieceProcess::VOnInit()
{
	while(Lower());	
	return true;
}

void DroppedPieceProcess::VOnSuccess()
{
	PlacePiece();
}

bool DroppedPieceProcess::Lower()
{
	m_pPiece->Move(0, 1);
	if(CheckCollision())
	{
		m_pPiece->Move(0, -1);
		return false;
	}
		
	return true;
}

bool DroppedPieceProcess::CheckCollision()
{
	int **positions = m_pPiece->GetPositions();
	int centerX = m_pPiece->GetCenterX();
	int centerY = m_pPiece->GetCenterY();
	int gridWidth = m_pGrid->GetWidth();
	int gridHeight = m_pGrid->GetHeight();
	
	if(centerX < 0 || centerX >= gridWidth || centerY < 0 || centerY >= gridHeight)
		return true;
		
	if(m_pGrid->GetBlock(centerX, centerY) != NULL)
		return true;
		
	for(int i=0; i<3; i++)
	{
		int x = centerX + positions[i][0];
		int y = centerY + positions[i][1];
		
		if(x < 0 || x >= gridWidth || y < 0 || y >= gridHeight)
			return true;
			
		if(m_pGrid->GetBlock(x, y) != NULL)
			return true;
	}
		
	return false;
}

void DroppedPieceProcess::PlacePiece()
{
	int **positions = m_pPiece->GetPositions();
	ePieceType type = m_pPiece->GetPieceType();
	int centerX = m_pPiece->GetCenterX();
	int centerY = m_pPiece->GetCenterY();
	
	m_pGrid->AddBlock(centerX, centerY, type);
	
	for(int i=0; i<3; i++)
	{
		int x = centerX + positions[i][0];
		int y = centerY + positions[i][1];
		
		m_pGrid->AddBlock(x, y, type);
	}
	
	g_pApp->GetGfxMgr()->RemoveElement(m_pImage);
	SAFE_DELETE(m_pPiece);
	
	ProcessSharedPtr pProc = ProcessSharedPtr(new DeleteLinesProcess(m_pGrid));
	AttachChild(pProc);
}
