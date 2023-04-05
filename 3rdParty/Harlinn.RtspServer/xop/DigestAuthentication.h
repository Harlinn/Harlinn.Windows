//PHZ
//2019-10-6

#ifndef RTSP_DIGEST_AUTHENTICATION_H
#define RTSP_DIGEST_AUTHENTICATION_H

#include <xop/RtspServerDef.h>

#include <cstdint>
#include <string>

namespace xop
{

class DigestAuthentication
{
public:
	HW_RTSPSERVER_EXPORT DigestAuthentication(std::string realm, std::string username, std::string password);
	HW_RTSPSERVER_EXPORT virtual ~DigestAuthentication();

	std::string GetRealm() const
	{ return realm_; }

	std::string GetUsername() const
	{ return username_; }

	std::string GetPassword() const
	{ return password_; }

	HW_RTSPSERVER_EXPORT std::string GetNonce();
	HW_RTSPSERVER_EXPORT std::string GetResponse(std::string nonce, std::string cmd, std::string url);

private:
	std::string realm_;
	std::string username_;
	std::string password_;

};

}

#endif
