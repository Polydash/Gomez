#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>
#include <map>

#include "IEvent.h"

class EventManager
{

	typedef std::list<EventListenerDelegate> EventListenerList;
	typedef std::map<eEventType, EventListenerList> EventListenerMap;

private :

	static EventManager* m_pEventMgr;

	EventListenerMap m_eventListeners;

public :

	static EventManager* Create();
	static void Destroy();

	void AddListener(const EventListenerDelegate &eventListener, eEventType eventType);
	void RemoveListener(const EventListenerDelegate &eventListener, eEventType eventType);

	void TriggerEvent(IEvent* pEvent);

private :

	EventManager();
	~EventManager();

};

#endif
