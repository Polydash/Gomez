#include <unistd.h>
#include <string.h>
#include <iostream>

#include "Client.h"
#include "../GameStd.h"

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
		size = MAX_PACKET_SIZE;
		ERROR("Sent message was truncated");
	}
	
	if(send(m_sockfd, str.c_str(), size, MSG_DONTWAIT) == -1)
	{
		ERROR("Failed to send message to server");
		m_bIsConnected = false;
		return;
	}
}

bool Client::HandleInput()
{
	char buffer[MAX_PACKET_SIZE+1];
	
	int value;
	if((value = recv(m_sockfd, buffer, MAX_PACKET_SIZE, MSG_DONTWAIT)) == -1)
	{
		ERROR("Failed to receive message from server");
		return false;
	}
	else if(value)
	{
		buffer[value] = '\0';
		std::istringstream iss;
		iss.str(buffer);
		//QueueEvent
		INFO("Message received");
	}
	else
		return false;
		
	return true;
}
