#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

/**
 * \file ProcessManager.h 
 * \brief Manager allowing processes to be updated and attached 
 */

#include <list>

#include "Process.h"

/**
 * \class ProcessManager
 * \brief Manager allowing processes to be updated and attached
 * 
 * This manager allows Processes to be attached to a process list that
 * is updated with the ProcessManager. A "child" Process may be attached
 * on a Process success. All Processes may also be aborted.
 */
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
