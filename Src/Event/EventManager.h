#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>
#include <map>

#include "IEvent.h"

class EventManager
{

	typedef std::list<EventListenerDelegate> EventListenerList;
	typedef std::list<EventSharedPtr> EventQueue;

private :

	static EventManager* s_pEventMgr;

	int m_activeQueue;

	EventQueue m_eventQueue[2];
	EventListenerList m_eventListeners[EVENT_NB];

public :

	static EventManager* Create();
	static void Destroy();
	
	void Update();

	void AddListener(const EventListenerDelegate &eventListener, eEventType eventType);
	void RemoveListener(const EventListenerDelegate &eventListener, eEventType eventType);

	void TriggerEvent(EventSharedPtr pEvent);
	void QueueEvent(EventSharedPtr pEvent);

private :

	EventManager();
	~EventManager();
};

#endif
