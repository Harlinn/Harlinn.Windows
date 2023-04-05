// PHZ
// 2018-5-15

#ifndef XOP_SOCKET_UTIL_H
#define XOP_SOCKET_UTIL_H

#include "Socket.h"
#include <string>

namespace xop
{
    
class SocketUtil
{
public:
    HW_RTSPSERVER_EXPORT static bool Bind(SOCKET sockfd, std::string ip, uint16_t port);
    HW_RTSPSERVER_EXPORT static void SetNonBlock(SOCKET fd);
    HW_RTSPSERVER_EXPORT static void SetBlock(SOCKET fd, int write_timeout=0);
    HW_RTSPSERVER_EXPORT static void SetReuseAddr(SOCKET fd);
    HW_RTSPSERVER_EXPORT static void SetReusePort(SOCKET sockfd);
    HW_RTSPSERVER_EXPORT static void SetNoDelay(SOCKET sockfd);
    HW_RTSPSERVER_EXPORT static void SetKeepAlive(SOCKET sockfd);
    HW_RTSPSERVER_EXPORT static void SetNoSigpipe(SOCKET sockfd);
    HW_RTSPSERVER_EXPORT static void SetSendBufSize(SOCKET sockfd, int size);
    HW_RTSPSERVER_EXPORT static void SetRecvBufSize(SOCKET sockfd, int size);
    HW_RTSPSERVER_EXPORT static std::string GetPeerIp(SOCKET sockfd);
    HW_RTSPSERVER_EXPORT static std::string GetSocketIp(SOCKET sockfd);
    HW_RTSPSERVER_EXPORT static int GetSocketAddr(SOCKET sockfd, struct sockaddr_in* addr);
    HW_RTSPSERVER_EXPORT static uint16_t GetPeerPort(SOCKET sockfd);
    HW_RTSPSERVER_EXPORT static int GetPeerAddr(SOCKET sockfd, struct sockaddr_in *addr);
    HW_RTSPSERVER_EXPORT static void Close(SOCKET sockfd);
    HW_RTSPSERVER_EXPORT static bool Connect(SOCKET sockfd, std::string ip, uint16_t port, int timeout=0);
};

}

#endif // _SOCKET_UTIL_H




