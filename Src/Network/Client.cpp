#include <unistd.h>
#include <string.h>
#include <iostream>
#include <errno.h>

#include "Client.h"
#include "../GameStd.h"
#include "../Event/EventManager.h"
#include "../Event/IEvent.h"
#include "../Event/Events/Evt_NewTetrisLoop.h"

Client::Client():
m_bIsConnected(false)
{
}

Client::~Client()
{
	if(m_sockfd != -1)
	{
		close(m_sockfd);
		m_sockfd = -1;
	}
}

bool Client::Init()
{
	if((m_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        ERROR("Failed to create client socket");
		return false;
    }
    
    return true;
}

bool Client::Connect(const char* ipAddress, short int port)
{
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress, &sa.sin_addr.s_addr);
	
	if(connect(m_sockfd, (struct sockaddr*) &sa, sizeof(sa)) == -1)
	{
		ERROR("Failed to connect to server");
		return false;
	}
	
	m_bIsConnected = true;
	return true;
}

void Client::Select()
{
	fd_set in;
	int maxFd = m_sockfd;
	
	FD_ZERO(&in);
	FD_SET(m_sockfd, &in);
	
	int value;
	value = select(maxFd + 1, &in, NULL, NULL, 0);
	if(value == -1)
	{
		ERROR("Failed to update connection with select");
		return;
	}
	else if(value)
	{
		if(FD_ISSET(m_sockfd, &in))
		{
			if(!HandleInput())
				m_bIsConnected = false;
		}
	}
}

void Client::Send(const std::ostringstream &oss)
{
	std::string str = oss.str();
	
	int size = strlen(str.c_str());
	if(size > MAX_PACKET_SIZE)
	{
		ERROR("Packet size exceeded its maximum value");
		return;
	}
	
	char* pBuffer = new char[size + sizeof(int)];
	memcpy(pBuffer, &size, sizeof(int));
	memcpy(pBuffer+sizeof(int), str.c_str(), size);
	
	int value;
	if((value = send(m_sockfd, pBuffer, size+sizeof(int), MSG_DONTWAIT)) == -1)
	{
		ERROR("Failed to send packet to server");
		m_bIsConnected = false;
	}
	
	delete [] pBuffer;
}

bool Client::HandleInput()
{
	bool result = false;
	
	int value, size;
	while((value = recv(m_sockfd, &size, sizeof(int), MSG_DONTWAIT)) > 0)
	{	
		char* pBuffer = new char[size+1];
		if((value = recv(m_sockfd, pBuffer, size, MSG_DONTWAIT)) != size)
		{
			ERROR("Incomplete packet");
			return false;
		}
		else
		{
			pBuffer[size] = '\0';
			std::istringstream iss;
			iss.str(pBuffer);
			HandleEvent(iss);
			result = true;
		}
		delete [] pBuffer;
	}
	
	if(value == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
	{
		ERROR("Failed to receive packets from server");
		return false;
	}
	
	return result;
}

void Client::HandleEvent(std::istringstream &iss)
{
	int type;
	iss >> type;
	
	//Debugging 
	LOG(iss.str());
	
	EventSharedPtr pEvt;
	switch(type)
	{	
		case ET_NEWTETRISLOOP :
			pEvt.reset(new Evt_NewTetrisLoop());
			pEvt->VDeserialize(iss);
			break;
		
		default :
			ERROR("Unsupported network event");
			break;
	}
	
	if(pEvt)
		EventManager::Get()->QueueEvent(pEvt);
}

