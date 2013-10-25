#ifndef IGAMESTATE_H
#define IGAMESTATE_H

enum eGameState{ GS_INVALID = -1,
				 GS_INTRO,
				 GS_MENU,
				 GS_MAINGAME,
				 GS_PAUSE,
				 GS_PREVIOUS
			   };

class IGameState
{
public:
	
	IGameState(){}
	virtual ~IGameState(){}
	
	virtual void VUpdate(unsigned int elapsedTime) = 0;
	virtual void VOnEnter(){}
	virtual void VOnLeave(){}
	
	virtual eGameState VGetState() const = 0;
};

#endif
