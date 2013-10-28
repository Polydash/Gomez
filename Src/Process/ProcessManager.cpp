#include "ProcessManager.h"

ProcessManager::ProcessManager()
{
}

ProcessManager::~ProcessManager()
{
	Clear();
}

void ProcessManager::UpdateProcesses(unsigned int elapsedTime)
{
	ProcessList::iterator nextIt = m_processList.begin();
	ProcessList::iterator currIt;
	
	while(nextIt != m_processList.end())
	{
		ProcessSharedPtr pProcess = (*nextIt);
		
		currIt = nextIt;
		nextIt++;
		
		if(pProcess->GetState() == PS_UNINITIALIZED)
		{
			if(!pProcess->Init())
				pProcess->Abort();
		}
		
		if(pProcess->GetState() == PS_RUNNING)
			pProcess->VUpdate(elapsedTime);
			
		if(pProcess->IsDone())
		{
			switch(pProcess->GetState())
			{
				case PS_SUCCEEDED :
					{
						ProcessSharedPtr pChild = pProcess->RemoveChild();
						if(pChild)
							AttachProcess(pChild);
					}
					break;
				
				case PS_ABORTED :
					break;
				
				default :
					break;
			}
			
			m_processList.erase(currIt);
		}
	}
}

void ProcessManager::AttachProcess(ProcessSharedPtr pProcess)
{
	m_processList.push_back(pProcess);
}

void ProcessManager::AbortAllProcesses()
{
	ProcessList::iterator i;
	
	for(i = m_processList.begin(); i != m_processList.end(); i++)
		(*i)->Abort();
}

void ProcessManager::Clear()
{
	m_processList.clear();
}
