#include <iostream>

#include "EventManager.h"
#include "../GameStd.h"

EventManager* EventManager::m_pEventMgr = NULL;

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

EventManager* EventManager::Create()
{
	if(m_pEventMgr)
		ERROR("EventManager already created");
	else
		m_pEventMgr = new EventManager;

	return m_pEventMgr;
}

void EventManager::Destroy()
{
	SAFE_DELETE(m_pEventMgr);
}

void EventManager::AddListener(const EventListenerDelegate &eventDelegate, const eEventType eventType)
{
	EventListenerList &list = m_eventListeners[eventType];
	for(EventListenerList::iterator i = list.begin(); i != list.end(); i++)
	{
		if(eventDelegate == (*i))
			ERROR("Failed to register listener : Already registered");
	}
	
	list.push_back(eventDelegate);
}

void EventManager::RemoveListener(const EventListenerDelegate &eventDelegate, eEventType eventType)
{
	EventListenerList &list = m_eventListeners[eventType];
	if(!list.empty())
	{
		for(EventListenerList::iterator i = list.begin(); i != list.end(); i++)
		{
			if(eventDelegate == (*i))
			{
				list.erase(i);
				break;
			}
		}
	}
}

void EventManager::TriggerEvent(IEvent* pEvent)
{
	EventListenerList &list = m_eventListeners[pEvent->VGetType()];
	if(!list.empty())
	{
		for(EventListenerList::iterator i = list.begin(); i != list.end(); i++)
		{
			EventListenerDelegate delegate = (*i);
			delegate(pEvent);
		}
	}
}
