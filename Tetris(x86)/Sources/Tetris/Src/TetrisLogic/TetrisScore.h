#ifndef TETRISSCORE_H
#define TETRISSCORE_H

/**
 * \file TetrisScore.h 
 * \brief Graphic element showing current score
 */

#include "../Graphics/GfxText.h"
#include "../Event/IEvent.h"
#include "../Process/Process.h"

class ScoreCounterProcess;

/**
 * \class TetrisScore 
 * \brief Graphic element showing current score
 * 
 * This class contains the current score and displays it.
 */
class TetrisScore
{
private :
 
	int m_width, m_height;
	int m_posX, m_posY;
	
	unsigned int m_score;
	
	GfxTextSharedPtr m_pTitle;
	shared_ptr<ScoreCounterProcess> m_pCounterProc;
	
public :

	TetrisScore(int width, int height, int posX, int posY);
	~TetrisScore();

	static unsigned int GetScoreValue(int lineNb);
	
private :

	void RegisterEvents();
	void UnregisterEvents();
	void AddScoreDelegate(EventSharedPtr pEvent);
};

#endif
