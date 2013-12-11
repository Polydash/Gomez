#ifndef SCORECOUNTERPROCESS_H
#define SCORECOUNTERPROCESS_H

/**
 * \file ScoreCounterProcess.h 
 * \brief Process managing a score counter with animations 
 */

#include "../Process.h"
#include "../../Graphics/GfxText.h"

/**
 * \class ScoreCounterProcess 
 * \brief Process managing a score counter with animations 
 * 
 * This Process makes the score increase slowly to the current score
 * value with a scale animation.
 */
class ScoreCounterProcess : public Process
{
private :

	unsigned int m_currentScore;
	unsigned int m_score;
	
	int m_posX, m_posY;
	float m_scale;
	float m_currentScale;
	float m_angle;
	
	bool m_bIsCounting;
	
	GfxTextSharedPtr m_pScoreImage;
	
public :

	ScoreCounterProcess(int posX, int posY, float scale);
	~ScoreCounterProcess();
	
	void AddScore(unsigned int scoreToAdd){ m_score += scoreToAdd; }
	bool IsCounting() const{ return m_bIsCounting; }
	
	virtual void VUpdate(unsigned int elapsedTime);
	
protected :

	virtual bool VOnInit();
	virtual void VOnSuccess();
	virtual void VOnAbort();
	
private :

	void UpdateImage();
	void UpdateScale();
};

#endif
