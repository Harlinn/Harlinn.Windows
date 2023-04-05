// PHZ
// 2020-4-2

#ifndef XOP_RTSP_SERVER_H
#define XOP_RTSP_SERVER_H

#include <memory>
#include <string>
#include <mutex>
#include <unordered_map>
#include "net/TcpServer.h"
#include "rtsp.h"

namespace xop
{

class RtspConnection;

class RtspServer : public Rtsp, public TcpServer
{
public:    
    HW_RTSPSERVER_EXPORT static std::shared_ptr<RtspServer> Create(xop::EventLoop* loop);
    HW_RTSPSERVER_EXPORT ~RtspServer();

    HW_RTSPSERVER_EXPORT MediaSessionId AddSession(MediaSession* session);
    HW_RTSPSERVER_EXPORT void RemoveSession(MediaSessionId sessionId);

    HW_RTSPSERVER_EXPORT bool PushFrame(MediaSessionId sessionId, MediaChannelId channelId, AVFrame frame);

private:
    friend class RtspConnection;

    HW_RTSPSERVER_EXPORT RtspServer(xop::EventLoop* loop);
    HW_RTSPSERVER_EXPORT MediaSession::Ptr LookMediaSession(const std::string& suffix);
    HW_RTSPSERVER_EXPORT MediaSession::Ptr LookMediaSession(MediaSessionId session_id);
    HW_RTSPSERVER_EXPORT virtual TcpConnection::Ptr OnConnect(SOCKET sockfd);

    std::mutex mutex_;
    std::unordered_map<MediaSessionId, std::shared_ptr<MediaSession>> media_sessions_;
    std::unordered_map<std::string, MediaSessionId> rtsp_suffix_map_;
};

}

#endif

