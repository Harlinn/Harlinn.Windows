// PHZ
// 2018-5-16

#ifndef XOP_H265_SOURCE_H
#define XOP_H265_SOURCE_H

#include "MediaSource.h"
#include "rtp.h"

namespace xop
{

class H265Source : public MediaSource
{
public:
	HW_RTSPSERVER_EXPORT static H265Source* CreateNew(uint32_t framerate=25);
	HW_RTSPSERVER_EXPORT ~H265Source();

	void Setframerate(uint32_t framerate)
	{ framerate_ = framerate; }

	uint32_t GetFramerate() const 
	{ return framerate_; }

	HW_RTSPSERVER_EXPORT virtual std::string GetMediaDescription(uint16_t port=0);

	HW_RTSPSERVER_EXPORT virtual std::string GetAttribute();

	HW_RTSPSERVER_EXPORT virtual bool HandleFrame(MediaChannelId channelId, AVFrame frame);

	HW_RTSPSERVER_EXPORT static uint32_t GetTimestamp();
	 
private:
	HW_RTSPSERVER_EXPORT H265Source(uint32_t framerate);

	uint32_t framerate_ = 25;
};
	
}

#endif


