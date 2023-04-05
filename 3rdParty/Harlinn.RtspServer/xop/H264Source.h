// PHZ
// 2018-5-16

#ifndef XOP_H264_SOURCE_H
#define XOP_H264_SOURCE_H

#include "MediaSource.h"
#include "rtp.h"

namespace xop
{ 

class H264Source : public MediaSource
{
public:
	HW_RTSPSERVER_EXPORT static H264Source* CreateNew(uint32_t framerate=25);
	HW_RTSPSERVER_EXPORT ~H264Source();

	void SetFramerate(uint32_t framerate)
	{ framerate_ = framerate; }

	uint32_t GetFramerate() const 
	{ return framerate_; }

	HW_RTSPSERVER_EXPORT virtual std::string GetMediaDescription(uint16_t port);

	HW_RTSPSERVER_EXPORT virtual std::string GetAttribute();

	HW_RTSPSERVER_EXPORT virtual bool HandleFrame(MediaChannelId channel_id, AVFrame frame);

	HW_RTSPSERVER_EXPORT static uint32_t GetTimestamp();
	
private:
	HW_RTSPSERVER_EXPORT H264Source(uint32_t framerate);

	uint32_t framerate_ = 25;
};
	
}

#endif



