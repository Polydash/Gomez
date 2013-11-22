#include <iostream>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>

#include "Server.h"
#include "../GameStd.h"

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
	value = select(maxFd + 1, &in, NULL, NULL, 0);
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
		size = MAX_PACKET_SIZE;
		ERROR("Sent message was truncated");
	}
	
	if(send(sockfd, str.c_str(), size, MSG_DONTWAIT) == -1)
	{
		ERROR("Failed to send message to : " << sockfd);
		return;
	}
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
	char buffer[MAX_PACKET_SIZE+1];
	
	int value;
	if((value = recv(sockfd, buffer, MAX_PACKET_SIZE, MSG_DONTWAIT)) == -1)
	{
		ERROR("Failed to receive message from client : " << sockfd);
		return false;
	}
	else if(value)
	{
		buffer[value] = '\0';
		std::istringstream iss;
		iss.str(buffer);
		//QueueEvent
		std::cout << "Message received" << std::endl;
	}
	else
		return false;
		
	return true;
}
