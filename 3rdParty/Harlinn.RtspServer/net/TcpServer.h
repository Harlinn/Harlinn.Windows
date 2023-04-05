// PHZ
// 2018-11-10

#ifndef XOP_TCPSERVER_H
#define XOP_TCPSERVER_H

#include <memory>
#include <string>
#include <mutex>
#include <unordered_map>
#include "Socket.h"
#include "TcpConnection.h"

namespace xop
{

class Acceptor;
class EventLoop;

class TcpServer
{
public:	
	HW_RTSPSERVER_EXPORT TcpServer(EventLoop* event_loop);
	HW_RTSPSERVER_EXPORT virtual ~TcpServer();

	HW_RTSPSERVER_EXPORT virtual bool Start(std::string ip, uint16_t port);
	HW_RTSPSERVER_EXPORT virtual void Stop();

	std::string GetIPAddress() const
	{ return ip_; }

	uint16_t GetPort() const 
	{ return port_; }

protected:
	HW_RTSPSERVER_EXPORT virtual TcpConnection::Ptr OnConnect(SOCKET sockfd);
	HW_RTSPSERVER_EXPORT virtual void AddConnection(SOCKET sockfd, TcpConnection::Ptr tcp_conn);
	HW_RTSPSERVER_EXPORT virtual void RemoveConnection(SOCKET sockfd);

	EventLoop* event_loop_;
	uint16_t port_;
	std::string ip_;
	std::unique_ptr<Acceptor> acceptor_; 
	bool is_started_;
	std::mutex mutex_;
	std::unordered_map<SOCKET, TcpConnection::Ptr> connections_;
};

}

#endif 
