#ifndef EVT_ADDSCORE_H
#define EVT_ADDSCORE_H

/**
 * \file Evt_AddScore.h 
 * \brief Add Score Event
 */

#include "../IEvent.h"

/**
 * \class Evt_AddScore
 * \brief Add Score Event
 * 
 * Event allowing an object to add score to TetrisScore object.
 */
class Evt_AddScore : public IEvent
{
private :

	unsigned int m_scoreToAdd;
	
public :

	Evt_AddScore(unsigned int scoreToAdd){ m_scoreToAdd = scoreToAdd; }
	~Evt_AddScore(){}
	
	unsigned int GetScore() const{ return m_scoreToAdd; }
	virtual eEventType VGetType() const{ return ET_ADDSCORE; }
};

#endif
