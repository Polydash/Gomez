#include "TetrisScore.h"
#include "../GameApp/SDLApp.h"
#include "../Graphics/GfxManager.h"
#include "../Graphics/GfxText.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_AddScore.h"
#include "../Event/Events/Evt_AttachLogicProcess.h"
#include "../Process/Processes/ScoreCounterProcess.h"

TetrisScore::TetrisScore(int width, int height, int posX, int posY):
m_width(width),
m_height(height),
m_posX(posX),
m_posY(posY),
m_score(0)
{
	m_pTitle.reset(new GfxText(2, "operator.ttf", "SCORE"));
	m_pTitle->SetPosition(posX + width/2, posY + height/8);
	m_pTitle->SetScale((width/240)*0.4f);
	g_pApp->GetGfxMgr()->AddElement(m_pTitle);
	
	EventSharedPtr pEvt;
	m_pCounterProc.reset(new ScoreCounterProcess(posX + width/2, posY + height/8*5, 0.5f));
	pEvt.reset(new Evt_AttachLogicProcess(m_pCounterProc));
	EventManager::Get()->QueueEvent(pEvt);
	
	RegisterEvents();
}

TetrisScore::~TetrisScore()
{
	UnregisterEvents();
	m_pCounterProc->Success();
	g_pApp->GetGfxMgr()->RemoveElement(m_pTitle);
}

unsigned int TetrisScore::GetScoreValue(int lineNb)
{
	unsigned int value = 0;
	
	switch(lineNb)
	{
		case 1 : 
			value = 40;
			break;
			
		case 2 :
			value = 100;
			break;
			
		case 3 : 
			value = 300;
			break;
			
		case 4 :
			value = 1200;
			break;
			
		default :
			break;
	}
	
	return value;
}
void TetrisScore::RegisterEvents()
{
	EventManager::Get()->AddListener(MakeDelegate(this, &TetrisScore::AddScoreDelegate), ET_ADDSCORE);
}

void TetrisScore::UnregisterEvents()
{
	EventManager::Get()->RemoveListener(MakeDelegate(this, &TetrisScore::AddScoreDelegate), ET_ADDSCORE);
}

void TetrisScore::AddScoreDelegate(EventSharedPtr pEvent)
{
	shared_ptr<Evt_AddScore> pEvt = static_pointer_cast<Evt_AddScore>(pEvent);
	unsigned int scoreToAdd = pEvt->GetScore();
	
	m_score += scoreToAdd;
	m_pCounterProc->AddScore(scoreToAdd);
}
