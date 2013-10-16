#include <iostream>

#include "EventManager.h"
#include "TetrisStd.h"

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
	EventListenerMap::iterator i = m_eventListeners.find(eventType);
	if(i != m_eventListeners.end())
	{
		EventListenerList &list = i->second;
		for(EventListenerList::iterator j = list.begin(); j != list.end(); j++)
		{
			if(eventDelegate == (*j))
			{
				list.erase(j);
				break;
			}
		}
	}
}

void EventManager::TriggerEvent(IEvent* pEvent)
{
	EventListenerMap::iterator i = m_eventListeners.find(pEvent->VGetType());
	if(i != m_eventListeners.end())
	{
		EventListenerList &list = i->second;
		for(EventListenerList::iterator j = list.begin(); j != list.end(); j++)
		{
			EventListenerDelegate delegate = (*j);
			delegate(pEvent);
		}
	}
}
