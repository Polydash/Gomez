/**
 * \file EventManager.h 
 * \brief Manager allowing Events to be triggered
 */

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>
#include <map>

#include "IEvent.h"

/**
 * \class EventManager
 * \brief Manager allowing Events to be triggered
 * 
 * This manager allows objects to subscribe a method to an event type. 
 * Each time an event is triggered, subscribed methods are called 
 * according to the event type.
 * 
 * There is also an event queue in order to queue events and trigger
 * them at the same time.
 * 
 * This manager uses delegates from the "FastDelegate" library.
 */
class EventManager
{

	typedef std::list<EventListenerDelegate> EventListenerList;
	typedef std::list<EventSharedPtr> EventQueue;

private :

	static EventManager* s_pInstance;

	int m_activeQueue;

	EventQueue m_eventQueue[2];
	EventListenerList m_eventListeners[EVENT_NB];

public :

	static void Create();
	static EventManager* Get();
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
