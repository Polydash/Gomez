#include "FallingPieceProcess.h"
#include "../../GameStd.h"
#include "../../Event/EventManager.h"
#include "../../Event/Events/Evt_MainGameInput.h"
#include "../../Event/Events/Evt_AttachLogicProcess.h"

FallingPieceProcess::FallingPieceProcess(TetrisGrid *pGrid):
m_pGrid(pGrid),
m_pPiece(NULL)
{
}

FallingPieceProcess::~FallingPieceProcess()
{
	UnregisterEvents();
}

bool FallingPieceProcess::VOnInit()
{
	RegisterEvents();	
	return true;
}

void FallingPieceProcess::VUpdate(unsigned int elapsedTime)
{
}

void FallingPieceProcess::MainGameInputDelegate(EventSharedPtr pEvent)
{
	shared_ptr<Evt_MainGameInput> pEvt = static_pointer_cast<Evt_MainGameInput>(pEvent);
	eGameInput input = pEvt->GetInput();
	
	switch(input)
	{
		case GI_MOVELEFT :
			INFO("Moved left");
			break;
			
		case GI_MOVERIGHT :
			INFO("Moved right");
			break;
			
		case GI_DROP :
			INFO("Dropped");
			break;
			
		case GI_ROTATE :
			INFO("Rotated");
			break;
			
		default :
			break;
	}
}

void FallingPieceProcess::RegisterEvents()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &FallingPieceProcess::MainGameInputDelegate), ET_MAINGAMEINPUT);
}

void FallingPieceProcess::UnregisterEvents()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &FallingPieceProcess::MainGameInputDelegate), ET_MAINGAMEINPUT);
}
