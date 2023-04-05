// PHZ
// 2018-5-15

#ifndef XOP_TCP_SOCKET_H
#define XOP_TCP_SOCKET_H

#include <cstdint>
#include <string>
#include "Socket.h"

namespace xop
{
    
class TcpSocket
{
public:
    HW_RTSPSERVER_EXPORT TcpSocket(SOCKET sockfd=-1);
    HW_RTSPSERVER_EXPORT virtual ~TcpSocket();

    HW_RTSPSERVER_EXPORT SOCKET Create();
    HW_RTSPSERVER_EXPORT bool   Bind(std::string ip, uint16_t port);
    HW_RTSPSERVER_EXPORT bool   Listen(int backlog);
    HW_RTSPSERVER_EXPORT SOCKET Accept();
    HW_RTSPSERVER_EXPORT bool   Connect(std::string ip, uint16_t port, int timeout = 0);
    HW_RTSPSERVER_EXPORT void   Close();
    HW_RTSPSERVER_EXPORT void   ShutdownWrite();
    SOCKET GetSocket() const { return sockfd_; }
    
private:
    SOCKET sockfd_ = -1;
};

}

#endif
