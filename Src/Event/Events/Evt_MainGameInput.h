#ifndef EVT_MAINGAMEINPUT
#define EVT_MAINGAMEINPUT

#include "../IEvent.h"

enum eGameInput{ GI_MOVELEFT,
				 GI_MOVERIGHT,
				 GI_ROTATE,
				 GI_DROP
			   };

class Evt_MainGameInput : public IEvent
{
private :

	eGameInput m_input;
	
public :

	Evt_MainGameInput(eGameInput input){ m_input = input; }
	~Evt_MainGameInput(){}
	
	eGameInput GetInput() const{ return m_input; }
	
	eEventType VGetType() const{ return ET_MAINGAMEINPUT; }
};

#endif
