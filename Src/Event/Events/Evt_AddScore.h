#ifndef EVT_ADDSCORE_H
#define EVT_ADDSCORE_H

#include "../IEvent.h"

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
