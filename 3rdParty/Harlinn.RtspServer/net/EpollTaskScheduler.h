// PHZ
// 2018-5-15

#ifndef XOP_EPOLL_TASK_SCHEDULER_H
#define XOP_EPOLL_TASK_SCHEDULER_H

#include "TaskScheduler.h"
#include <mutex>
#include <unordered_map>

namespace xop
{	
class EpollTaskScheduler : public TaskScheduler
{
public:
	HW_RTSPSERVER_EXPORT EpollTaskScheduler(int id = 0);
	HW_RTSPSERVER_EXPORT virtual ~EpollTaskScheduler();

	HW_RTSPSERVER_EXPORT void UpdateChannel(ChannelPtr channel);
	HW_RTSPSERVER_EXPORT void RemoveChannel(ChannelPtr& channel);

	// timeout: ms
	HW_RTSPSERVER_EXPORT bool HandleEvent(int timeout);

private:
	HW_RTSPSERVER_EXPORT void Update(int operation, ChannelPtr& channel);

	int epollfd_ = -1;
	std::mutex mutex_;
	std::unordered_map<int, ChannelPtr> channels_;
};

}

#endif
