#ifndef XOP_RTSP_PUSHER_H
#define XOP_RTSP_PUSHER_H

#include <mutex>
#include <map>
#include "rtsp.h"

namespace xop
{

class RtspConnection;

class RtspPusher : public Rtsp
{
public:
	HW_RTSPSERVER_EXPORT static std::shared_ptr<RtspPusher> Create(xop::EventLoop* loop);
	HW_RTSPSERVER_EXPORT ~RtspPusher();

	HW_RTSPSERVER_EXPORT void AddSession(MediaSession* session);
	HW_RTSPSERVER_EXPORT void RemoveSession(MediaSessionId session_id);

	HW_RTSPSERVER_EXPORT int  OpenUrl(std::string url, int msec = 3000);
	HW_RTSPSERVER_EXPORT void Close();
	HW_RTSPSERVER_EXPORT bool IsConnected();

	HW_RTSPSERVER_EXPORT bool PushFrame(MediaChannelId channelId, AVFrame frame);

private:
	friend class RtspConnection;

	HW_RTSPSERVER_EXPORT RtspPusher(xop::EventLoop *event_loop);
	HW_RTSPSERVER_EXPORT MediaSession::Ptr LookMediaSession(MediaSessionId session_id);

	xop::EventLoop* event_loop_ = nullptr;
	xop::TaskScheduler* task_scheduler_ = nullptr;
	std::mutex mutex_;
	std::shared_ptr<RtspConnection> rtsp_conn_;
	std::shared_ptr<MediaSession> media_session_;
};

}

#endif