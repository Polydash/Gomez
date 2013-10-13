#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <list>

class IGUIElement;

class GUIManager
{
private :

	typedef std::list<IGUIElement> GUIElementList;
	
	GUIElementList m_guiElements;
	
public :

	GUIManager();
	~GUIManager();
	
	void Init();
	void Update(unsigned int elapsedTime);
	void Render();
	
	void AddGUIElement(IGUIElement* pGUIElement);
	IGUIElement* GetGUIElement() const;
};

#endif
