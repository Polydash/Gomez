#ifndef IGAMESTATE_H
#define IGAMESTATE_H

enum eGameState{ GS_INTRO,
				 GS_MENU };

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


class IntroState : public IGameState
{
public:

	IntroState(){}
	virtual ~IntroState(){}
	
	virtual void VUpdate(unsigned int elapsedTime){}
	virtual eGameState VGetState() const {return GS_INTRO;}
};

class MenuState : public IGameState
{
public:

	MenuState(){}
	~MenuState(){}
	
	virtual void VUpdate(unsigned int elapsedTime){}
	virtual eGameState VGetState() const {return GS_MENU;}
};

#endif
