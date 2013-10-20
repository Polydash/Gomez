#include <iostream>

#include "EventManager.h"
#include "Events.h"
#include "../GameStd.h"

EventManager* EventManager::s_pEventMgr = NULL;

EventManager::EventManager():
m_activeQueue(0)
{
}

EventManager::~EventManager()
{
}

EventManager* EventManager::Create()
{
	if(s_pEventMgr)
		ERROR("EventManager already created");
	else
		s_pEventMgr = new EventManager;

	return s_pEventMgr;
}

void EventManager::Destroy()
{
	SAFE_DELETE(s_pEventMgr);
}

void EventManager::Update()
{
	int updatedQueue = m_activeQueue;
	
	if(!m_activeQueue)
		m_activeQueue = 1;
	else
		m_activeQueue = 0;
		
	m_eventQueue[m_activeQueue].clear();
		
	while(!m_eventQueue[updatedQueue].empty())
	{
		EventSharedPtr pEvent = m_eventQueue[updatedQueue].front();
		m_eventQueue[updatedQueue].pop_front();
		
		TriggerEvent(pEvent);
	}
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

void EventManager::TriggerEvent(EventSharedPtr pEvent)
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

void EventManager::QueueEvent(EventSharedPtr pEvent)
{
	m_eventQueue[m_activeQueue].push_back(pEvent);
}
