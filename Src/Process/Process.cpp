#include "Process.h"

Process::Process():
m_state(PS_UNINITIALIZED)
{
}

Process::~Process()
{
}

void Process::Succeed()
{
	m_state = PS_SUCCEEDED;
	VOnSuccess();
}

void Process::Abort()
{
	m_state = PS_ABORTED;
	VOnAbort();
}

bool Process::Init()
{
	m_state = PS_RUNNING;
	return VOnInit();
}

bool Process::IsDone() const
{
	return (m_state == PS_SUCCEEDED || m_state == PS_ABORTED);
}

eProcessState Process::GetState() const
{
	return m_state;
}

void Process::AttachChild(ProcessSharedPtr pProcess)
{
	if(m_pChild)
	{
		m_pChild->AttachChild(pProcess);
	}
	else
	{
		m_pChild = pProcess;
	}	
}

ProcessSharedPtr Process::GetChild() const
{
	return m_pChild;
}

ProcessSharedPtr Process::RemoveChild()
{
	ProcessSharedPtr pProcess = m_pChild;
	m_pChild.reset();
	return pProcess;
}
