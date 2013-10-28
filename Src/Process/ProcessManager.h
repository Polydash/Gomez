#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <list>

#include "Process.h"

class ProcessManager
{
private :

	typedef std::list<ProcessSharedPtr> ProcessList;
	
	ProcessList m_processList;

public :

	ProcessManager();
	~ProcessManager();
	
	void UpdateProcesses(unsigned int elapsedTime);
	void AttachProcess(ProcessSharedPtr pProcess);
	void AbortAllProcesses();
	int GetProcessCount() const;
	
private :

	void Clear();
};

#endif
