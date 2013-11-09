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
	bool m_pressed;
	
public :

	Evt_MainGameInput(eGameInput input, bool pressed = true){ m_input = input; m_pressed = pressed; }
	~Evt_MainGameInput(){}
	
	eGameInput GetInput() const{ return m_input; }
	bool GetPressed() const{ return m_pressed; }
	
	eEventType VGetType() const{ return ET_MAINGAMEINPUT; }
};

#endif
