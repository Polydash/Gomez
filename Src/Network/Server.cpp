/**
 * \file Server.cpp 
 * \brief TCP Server 
 */

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <errno.h>

#include "Server.h"
#include "../GameStd.h"
#include "../Event/EventManager.h"
#include "../Event/Events/Evt_MainGameInput.h"

Server::Server(const char* ipAddress, short int port, unsigned int maxConnections):
m_maxConnections(maxConnections)
{
	memset(&m_sa, 0, sizeof(m_sa));
	m_sa.sin_family = AF_INET;
	m_sa.sin_addr.s_addr = htonl(INADDR_ANY);
	m_sa.sin_port = htons(port);
}

Server::~Server()
{	
	SocketList::iterator i;
	for(i=m_clients.begin(); i!=m_clients.end(); i++)
	{
		if(*i != -1)
		{
			close(*i);
			*i = -1;
		}
	}
}

bool Server::Init()
{
	if((m_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
		ERROR("Failed to create server socket");
		return false;
    }
	
	if(bind(m_sockfd, (struct sockaddr*) &m_sa, sizeof(m_sa)) == -1)
	{
		ERROR("Failed to bind server");
		return false;
	}
	
	if(listen(m_sockfd, m_maxConnections) == -1)
	{
		ERROR("Failed to listen to connections");
		return false;
	}
	
	return true;
}

void Server::Select()
{
	fd_set in;
	int maxFd = m_sockfd;
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 100;
	
	FD_ZERO(&in);
	FD_SET(m_sockfd, &in);
	
	SocketList::iterator i = m_clients.begin();
	while(i != m_clients.end())
	{
		if(*i > maxFd)
			maxFd = *i;
			
		FD_SET(*i, &in);
		i++;
	}
	
	int value;
	value = select(maxFd + 1, &in, NULL, NULL, &tv);	
	if(value == -1)
	{
		ERROR("Failed to update connections with select");
		return;
	}
	else if(value)
	{
		if(FD_ISSET(m_sockfd, &in))
			AcceptClient();
		
		i = m_clients.begin();
		while(i != m_clients.end())
		{
			if(FD_ISSET(*i, &in))
			{
				if(!HandleInput(*i))
				{
					RemoveClient(*i);
					i = m_clients.erase(i);
				}
				else
					i++;
			}
			else
				i++;
		}
	}
}

void Server::Broadcast(const std::ostringstream &oss)
{
	SocketList::iterator i;
	for(i=m_clients.begin(); i!=m_clients.end(); i++)
		Send(*i, oss);	
}

void Server::Send(SockFd sockfd, const std::ostringstream &oss)
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
	if((value = send(sockfd, pBuffer, size+sizeof(int), MSG_DONTWAIT)) == -1)
		ERROR("Failed to send packet to client" << sockfd);
		
	delete [] pBuffer;
}

void Server::AcceptClient()
{
	struct sockaddr_in sa;
	socklen_t size = sizeof(sa);
	SockFd client;
	
	client = accept(m_sockfd, (struct sockaddr*) &sa, &size);
	if(m_clients.size() < m_maxConnections && client != -1)
	{
		m_clients.push_back(client);
		INFO("Connected client : " << client);
	}
	else
		ERROR("Failed to accept client connection");
}

void Server::RemoveClient(SockFd sockfd)
{
	INFO("Disconnected client : " << sockfd);
	close(sockfd);
}

bool Server::HandleInput(SockFd sockfd)
{
	bool result = false;
	
	int value, size;
	while((value = recv(sockfd, &size, sizeof(int), MSG_DONTWAIT)) > 0)
	{	
		char* pBuffer = new char[size+1];
		if((value = recv(sockfd, pBuffer, size, MSG_DONTWAIT)) != size)
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
		ERROR("Failed to receive packets from client : " << sockfd);
		return false;
	}
	
	return result;
}

void Server::HandleEvent(std::istringstream &iss)
{
	int type;
	iss >> type;
	
	EventSharedPtr pEvt;
	switch(type)
	{
		case ET_MAINGAMEINPUT :
			pEvt.reset(new Evt_MainGameInput());
			pEvt->VDeserialize(iss);
			break;
			
		default :
			ERROR("Unsupported network event");
			break;
	}
	
	if(pEvt)
		EventManager::Get()->QueueEvent(pEvt);
}
