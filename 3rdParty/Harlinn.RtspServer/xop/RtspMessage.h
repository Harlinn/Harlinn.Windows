// PHZ
// 2018-6-8

#ifndef XOP_RTSP_MESSAGE_H
#define XOP_RTSP_MESSAGE_H

#include <utility>
#include <unordered_map>
#include <string>
#include <cstring>
#include "rtp.h"
#include "media.h"
#include "net/BufferReader.h"

namespace xop
{

class RtspRequest
{
public:
	enum Method
	{
		OPTIONS=0, DESCRIBE, SETUP, PLAY, TEARDOWN, GET_PARAMETER, 
		RTCP, NONE,
	};

	const char* MethodToString[8] =
	{
		"OPTIONS", "DESCRIBE", "SETUP", "PLAY", "TEARDOWN", "GET_PARAMETER",
		"RTCP", "NONE"
	};

	enum RtspRequestParseState
	{
		kParseRequestLine,
		kParseHeadersLine,
		//kParseBody,	
		kGotAll,
	};

	HW_RTSPSERVER_EXPORT bool ParseRequest(xop::BufferReader *buffer);

	bool GotAll() const
	{ return state_ == kGotAll; }

	void Reset()
	{
		state_ = kParseRequestLine;
		request_line_param_.clear();
		header_line_param_.clear();
	}

	Method GetMethod() const
	{ return method_; }

	HW_RTSPSERVER_EXPORT uint32_t GetCSeq() const;

	HW_RTSPSERVER_EXPORT std::string GetRtspUrl() const;

	HW_RTSPSERVER_EXPORT std::string GetRtspUrlSuffix() const;

	HW_RTSPSERVER_EXPORT std::string GetIp() const;

	HW_RTSPSERVER_EXPORT std::string GetAuthResponse() const;

	TransportMode GetTransportMode() const
	{ return transport_; }

	MediaChannelId GetChannelId() const
	{ return channel_id_; }

	HW_RTSPSERVER_EXPORT uint8_t  GetRtpChannel() const;
	HW_RTSPSERVER_EXPORT uint8_t  GetRtcpChannel() const;
	HW_RTSPSERVER_EXPORT uint16_t GetRtpPort() const;
	HW_RTSPSERVER_EXPORT uint16_t GetRtcpPort() const;

	HW_RTSPSERVER_EXPORT int BuildOptionRes(const char* buf, int buf_size);
	HW_RTSPSERVER_EXPORT int BuildDescribeRes(const char* buf, int buf_size, const char* sdp);
	HW_RTSPSERVER_EXPORT int BuildSetupMulticastRes(const char* buf, int buf_size, const char* multicast_ip, uint16_t port, uint32_t session_id);
	HW_RTSPSERVER_EXPORT int BuildSetupTcpRes(const char* buf, int buf_size, uint16_t rtp_chn, uint16_t rtcp_chn, uint32_t session_id);
	HW_RTSPSERVER_EXPORT int BuildSetupUdpRes(const char* buf, int buf_size, uint16_t rtp_chn, uint16_t rtcp_chn, uint32_t session_id);
	HW_RTSPSERVER_EXPORT int BuildPlayRes(const char* buf, int buf_size, const char* rtp_info, uint32_t session_id);
	HW_RTSPSERVER_EXPORT int BuildTeardownRes(const char* buf, int buf_size, uint32_t session_id);
	HW_RTSPSERVER_EXPORT int BuildGetParamterRes(const char* buf, int buf_size, uint32_t session_id);
	HW_RTSPSERVER_EXPORT int BuildNotFoundRes(const char* buf, int buf_size);
	HW_RTSPSERVER_EXPORT int BuildServerErrorRes(const char* buf, int buf_size);
	HW_RTSPSERVER_EXPORT int BuildUnsupportedRes(const char* buf, int buf_size);
	HW_RTSPSERVER_EXPORT int BuildUnauthorizedRes(const char* buf, int buf_size, const char* realm, const char* nonce);

private:
	HW_RTSPSERVER_EXPORT bool ParseRequestLine(const char* begin, const char* end);
	HW_RTSPSERVER_EXPORT bool ParseHeadersLine(const char* begin, const char* end);
	HW_RTSPSERVER_EXPORT bool ParseCSeq(std::string& message);
	HW_RTSPSERVER_EXPORT bool ParseAccept(std::string& message);
	HW_RTSPSERVER_EXPORT bool ParseTransport(std::string& message);
	HW_RTSPSERVER_EXPORT bool ParseSessionId(std::string& message);
	HW_RTSPSERVER_EXPORT bool ParseMediaChannel(std::string& message);
	HW_RTSPSERVER_EXPORT bool ParseAuthorization(std::string& message);

	Method method_;
	MediaChannelId channel_id_;
	TransportMode transport_;
	std::string auth_response_;
	std::unordered_map<std::string, std::pair<std::string, uint32_t>> request_line_param_;
	std::unordered_map<std::string, std::pair<std::string, uint32_t>> header_line_param_;

	RtspRequestParseState state_ = kParseRequestLine;
};

class RtspResponse
{
public:
	enum Method
	{
		OPTIONS=0, DESCRIBE, ANNOUNCE, SETUP, RECORD, RTCP,
		NONE, 
	};

	HW_RTSPSERVER_EXPORT bool ParseResponse(xop::BufferReader *buffer);

	Method GetMethod() const
	{ return method_; }

	uint32_t GetCSeq() const
	{ return cseq_;  }

	std::string GetSession() const
	{ return session_; }

	void SetUserAgent(const char *user_agent) 
	{ user_agent_ = std::string(user_agent); }

	void SetRtspUrl(const char *url)
	{ rtsp_url_ = std::string(url); }

	HW_RTSPSERVER_EXPORT int BuildOptionReq(const char* buf, int buf_size);
	HW_RTSPSERVER_EXPORT int BuildDescribeReq(const char* buf, int buf_size);
	HW_RTSPSERVER_EXPORT int BuildAnnounceReq(const char* buf, int buf_size, const char *sdp);
	HW_RTSPSERVER_EXPORT int BuildSetupTcpReq(const char* buf, int buf_size, int channel);
	HW_RTSPSERVER_EXPORT int BuildRecordReq(const char* buf, int buf_size);

private:
	Method method_;
	uint32_t cseq_ = 0;
	std::string user_agent_;
	std::string rtsp_url_;
	std::string session_;
};

}

#endif
