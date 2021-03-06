#ifndef EVT_MAINGAMEINPUT
#define EVT_MAINGAMEINPUT

/**
 * \file Evt_MainGameInput.h 
 * \brief Main Game Input Event
 */

#include "../IEvent.h"

/// Enumeration defining every game input
enum eGameInput{ GI_MOVELEFT,
				 GI_MOVERIGHT,
				 GI_ROTATE,
				 GI_LOWER,
				 GI_DROP
			   };

/**
 * \class Evt_MainGameInput
 * \brief Main Game Input Event
 * 
 * Event indicating a new Game Input. It also indicates wether it is
 * pressed or not (useful for buttons, for instance) 
 */
class Evt_MainGameInput : public IEvent
{
private :

	eGameInput m_input;
	bool m_pressed;
	
public :

	Evt_MainGameInput(){}
	Evt_MainGameInput(eGameInput input, bool pressed = true){ m_input = input; m_pressed = pressed; }
	~Evt_MainGameInput(){}
	
	eGameInput GetInput() const{ return m_input; }
	bool GetPressed() const{ return m_pressed; }
	
	eEventType VGetType() const{ return ET_MAINGAMEINPUT; }
	
	virtual void VSerialize(std::ostringstream &oss)
	{
		int type = static_cast<eEventType>(VGetType());
		int input = static_cast<eGameInput>(m_input);
		oss << type << " ";
		oss << input << " ";
		oss << m_pressed;
	}
	
	virtual void VDeserialize(std::istringstream &iss)
	{
		int input;
		iss >> input;
		iss >> m_pressed;
		m_input = static_cast<eGameInput>(input);
	}
};

#endif
