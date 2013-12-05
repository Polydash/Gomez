#ifndef SERVER_H
#define SERVER_H

/**
 * \file Server.h 
 * \brief TCP Server 
 */

#include <list>
#include <arpa/inet.h>
#include <sstream>

#define MAX_PACKET_SIZE 1024

class Server
{
private :

	typedef int SockFd;
	typedef std::list<SockFd> SocketList;
	
	SocketList m_clients;
	SockFd m_sockfd;

	struct sockaddr_in m_sa;
	unsigned int m_maxConnections;
	
public :

	Server(const char* ipAddress, short int port, unsigned int maxConnections = 1);
	~Server();
	
	bool Init();
	void Select();
	void Broadcast(const std::ostringstream &oss);
	void Send(SockFd sockfd, const std::ostringstream &oss);
	
private :

	void AcceptClient();
	void RemoveClient(SockFd sockfd);
	bool HandleInput(SockFd sockfd);
	void HandleEvent(std::istringstream &iss);
};

#endif
