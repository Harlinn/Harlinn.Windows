// PHZ
// 2018-5-16

#ifndef XOP_G711A_SOURCE_H
#define XOP_G711A_SOURCE_H

#include "MediaSource.h"
#include "rtp.h"

namespace xop
{

class G711ASource : public MediaSource
{
public:
	HW_RTSPSERVER_EXPORT static G711ASource* CreateNew();
	HW_RTSPSERVER_EXPORT virtual ~G711ASource();

	uint32_t GetSampleRate() const
	{ return samplerate_; }

	uint32_t GetChannels() const
	{ return channels_; }

	HW_RTSPSERVER_EXPORT virtual std::string GetMediaDescription(uint16_t port=0);

	HW_RTSPSERVER_EXPORT virtual std::string GetAttribute();

	HW_RTSPSERVER_EXPORT virtual bool HandleFrame(MediaChannelId channel_id, AVFrame frame);

	HW_RTSPSERVER_EXPORT static uint32_t GetTimestamp();

private:
	HW_RTSPSERVER_EXPORT G711ASource();

	uint32_t samplerate_ = 8000;   
	uint32_t channels_ = 1;       
};

}

#endif
