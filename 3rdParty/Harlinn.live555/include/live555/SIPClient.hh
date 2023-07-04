/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// "liveMedia"
// Copyright (c) 1996-2023 Live Networks, Inc.  All rights reserved.
// A generic SIP client
// C++ header

#ifndef _SIP_CLIENT_HH
#define _SIP_CLIENT_HH

#ifndef _MEDIA_SESSION_HH
#include "MediaSession.hh"
#endif
#ifndef _NET_ADDRESS_HH
#include "NetAddress.hh"
#endif
#ifndef _DIGEST_AUTHENTICATION_HH
#include "DigestAuthentication.hh"
#endif

// Possible states in the "INVITE" transition diagram (RFC 3261, Figure 5)
enum inviteClientState { Calling, Proceeding, Completed, Terminated };

class SIPClient: public Medium {
public:
  LIVE555_EXPORT static SIPClient* createNew(UsageEnvironment& env,
			      unsigned char desiredAudioRTPPayloadFormat,
			      char const* mimeSubtype = NULL,
			      int verbosityLevel = 0,
			      char const* applicationName = NULL);

  LIVE555_EXPORT void setProxyServer(struct sockaddr_storage const& proxyServerAddress,
		      portNumBits proxyServerPortNum);

  void setClientStartPortNum(portNumBits clientStartPortNum) {
    fClientStartPortNum = clientStartPortNum;
  }

  LIVE555_EXPORT char* invite(char const* url, Authenticator* authenticator = NULL);
      // Issues a SIP "INVITE" command
      // Returns the session SDP description if this command succeeds
  LIVE555_EXPORT char* inviteWithPassword(char const* url,
			   char const* username, char const* password);
      // Uses "invite()" to do an "INVITE" - first
      // without using "password", then (if we get an Unauthorized
      // response) with an authentication response computed from "password"

  LIVE555_EXPORT Boolean sendACK(); // on current call
  LIVE555_EXPORT Boolean sendBYE(); // on current call

  LIVE555_EXPORT static Boolean parseSIPURL(UsageEnvironment& env, char const* url,
			     NetAddress& address, portNumBits& portNum);
      // (ignores any "<username>[:<password>]@" in "url")
  LIVE555_EXPORT static Boolean parseSIPURLUsernamePassword(char const* url,
					     char*& username,
					     char*& password);
  char const* getInviteSdpReply() const { return fInviteSDPDescriptionReturned; }

  LIVE555_EXPORT void setUserAgentString(char const* userAgentName);
       // sets an alternative string to be used in SIP "User-Agent:" headers

protected:
	LIVE555_EXPORT virtual ~SIPClient();

private:
	LIVE555_EXPORT SIPClient(UsageEnvironment& env,
	    unsigned char desiredAudioRTPPayloadFormat,
	    char const* mimeSubtype,
	    int verbosityLevel,
	    char const* applicationName);
      // called only by createNew();

	LIVE555_EXPORT void reset();

  // Routines used to implement invite*():
  LIVE555_EXPORT char* invite1(Authenticator* authenticator);
  LIVE555_EXPORT Boolean processURL(char const* url);
  LIVE555_EXPORT Boolean sendINVITE();
  LIVE555_EXPORT static void inviteResponseHandler(void* clientData, int mask);
  LIVE555_EXPORT void doInviteStateMachine(unsigned responseCode);
  LIVE555_EXPORT void doInviteStateTerminated(unsigned responseCode);
  TaskToken fTimerA, fTimerB, fTimerD;
  LIVE555_EXPORT static void timerAHandler(void* clientData);
  LIVE555_EXPORT static void timerBHandler(void* clientData);
  LIVE555_EXPORT static void timerDHandler(void* clientData);
  unsigned const fT1; // in microseconds
  unsigned fTimerALen; // in microseconds; initially fT1, then doubles
  unsigned fTimerACount;

  // Routines used to implement all commands:
  LIVE555_EXPORT char* createAuthenticatorString(Authenticator const* authenticator,
				  char const* cmd, char const* url);
  LIVE555_EXPORT Boolean sendRequest(char const* requestString, unsigned requestLength);
  LIVE555_EXPORT unsigned getResponseCode();
  LIVE555_EXPORT unsigned getResponse(char*& responseBuffer, unsigned responseBufferSize);
  LIVE555_EXPORT Boolean parseResponseCode(char const* line, unsigned& responseCode);

private:
  // Set for all calls:
  unsigned char fDesiredAudioRTPPayloadFormat;
  char* fMIMESubtype;
  unsigned fMIMESubtypeSize;
  int fVerbosityLevel;
  unsigned fCSeq; // sequence number, used in consecutive requests
  char const* fApplicationName;
  unsigned fApplicationNameSize;
  char const* fOurAddressStr;
  unsigned fOurAddressStrSize;
  portNumBits fOurPortNum;
  Groupsock* fOurSocket;
  char* fUserAgentHeaderStr;
  unsigned fUserAgentHeaderStrLen;

  // Set for each call:
  char const* fURL;
  unsigned fURLSize;
  struct sockaddr_storage fServerAddress;
  Boolean fServerAddressIsSet;
  portNumBits fServerPortNum; // in host order
  portNumBits fClientStartPortNum; // in host order
  unsigned fCallId, fFromTag; // set by us
  char const* fToTagStr; // set by the responder
  unsigned fToTagStrSize;
  Authenticator fValidAuthenticator;
  char const* fUserName; // 'user' name used in "From:" & "Contact:" lines
  unsigned fUserNameSize;

  char* fInviteSDPDescription;
  char* fInviteSDPDescriptionReturned;
  char* fInviteCmd;
  unsigned fInviteCmdSize;
  Authenticator* fWorkingAuthenticator;
  inviteClientState fInviteClientState;
  char fEventLoopStopFlag;
};

#endif
