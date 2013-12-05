#ifndef CLIENT_H
#define CLIENT_H

/**
 * \file Client.h 
 * \brief TCP Client 
 */

#include <arpa/inet.h>
#include <sstream>

#define MAX_PACKET_SIZE 1024

class Client
{
private :

	typedef int SockFd;
	
	bool m_bIsConnected;
	SockFd m_sockfd;
	
public :

	Client();
	~Client();
	
	bool Init();
	bool Connect(const char* ipAddress, short int port);
	void Select();
	void Send(const std::ostringstream &oss);
	
	bool IsConnected() const{ return m_bIsConnected; }
	
private :

	bool HandleInput();
	void HandleEvent(std::istringstream &iss);
};

#endif
