#ifndef XOP_ACCEPTOR_H
#define XOP_ACCEPTOR_H

#include <functional>
#include <memory>
#include <mutex>
#include "Channel.h"
#include "TcpSocket.h"

namespace xop
{

typedef std::function<void(SOCKET)> NewConnectionCallback;

class EventLoop;

class Acceptor
{
public:	
	HW_RTSPSERVER_EXPORT Acceptor(EventLoop* eventLoop);
	HW_RTSPSERVER_EXPORT virtual ~Acceptor();

	void SetNewConnectionCallback(const NewConnectionCallback& cb)
	{ new_connection_callback_ = cb; }

	HW_RTSPSERVER_EXPORT int  Listen(std::string ip, uint16_t port);
	HW_RTSPSERVER_EXPORT void Close();

private:
	HW_RTSPSERVER_EXPORT void OnAccept();

	EventLoop* event_loop_ = nullptr;
	std::mutex mutex_;
	std::unique_ptr<TcpSocket> tcp_socket_;
	ChannelPtr channel_ptr_;
	NewConnectionCallback new_connection_callback_;
};

}

#endif 
