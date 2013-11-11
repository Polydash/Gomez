#include <sstream>

#include "ScoreCounterProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"

ScoreCounterProcess::ScoreCounterProcess(int posX, int posY, float scale):
m_currentScore(0),
m_score(0),
m_posX(posX),
m_posY(posY),
m_scale(scale),
m_currentScale(scale),
m_bIsCounting(false)
{
}

ScoreCounterProcess::~ScoreCounterProcess()
{
	g_pApp->GetGfxMgr()->RemoveElement(m_pScoreImage);
}

void ScoreCounterProcess::VUpdate(unsigned int elapsedTime)
{
	if(m_score != m_currentScore)
	{
		m_bIsCounting = true;
		unsigned int speed = (m_score - m_currentScore)*elapsedTime*0.005f;
		
		if(speed > m_score - m_currentScore)
			m_currentScore = m_score;
		else if(speed < 1)
			m_currentScore += 1;
		else if(speed > 10)
			m_currentScore += 10;
		else
			m_currentScore += speed;
		
		UpdateImage();
	}
	
	if(m_bIsCounting)
	{
		m_angle += elapsedTime*0.008f;
		if(m_angle > 5*PI/2)
		{
			if(m_currentScore == m_score)
			{
				m_bIsCounting = false;
				m_angle = PI/2;
			}
			else
				m_angle -= PI;
		}
			
		m_currentScale = m_scale + cos(m_angle)*0.15f;
		UpdateScale();
	}
}

bool ScoreCounterProcess::VOnInit()
{
	UpdateImage();
	return true;
}

void ScoreCounterProcess::UpdateImage()
{
	if(m_pScoreImage)
		g_pApp->GetGfxMgr()->RemoveElement(m_pScoreImage);
		
	std::ostringstream stream;
	stream << m_currentScore;
		
	m_pScoreImage.reset(new GfxText(2, "operator.ttf", stream.str()));
	g_pApp->GetGfxMgr()->AddElement(m_pScoreImage);
	m_pScoreImage->SetPosition(m_posX, m_posY);
	UpdateScale();
}

void ScoreCounterProcess::UpdateScale()
{
	m_pScoreImage->SetScale(m_currentScale);
}
