#ifndef PROCESS_H
#define PROCESS_H

#include <tr1/memory>
using std::tr1::shared_ptr;

class Process;

typedef shared_ptr<Process> ProcessSharedPtr; 

enum eProcessState { PS_UNINITIALIZED,
					 PS_RUNNING,
					 PS_ABORTED,
					 PS_SUCCEEDED
				   };

class Process
{
private :

	ProcessSharedPtr m_pChild;
	eProcessState	 m_state;
	
public :

	Process();
	virtual ~Process();
	
	void Succeed();
	void Abort();
	bool Init();
	
	virtual void VUpdate(unsigned int elapsedTime) = 0;
	
	bool IsDone() const;
	eProcessState GetState() const;
	
	void AttachChild(ProcessSharedPtr pProcess);
	ProcessSharedPtr GetChild() const;
	ProcessSharedPtr RemoveChild();
	
protected :

	virtual bool VOnInit(){ return true; }
	virtual void VOnSuccess(){}
	virtual void VOnAbort(){}
};

#endif
