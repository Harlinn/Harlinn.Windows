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
// A generic RTSP client - for a single "rtsp://" URL
// C++ header

#ifndef _RTSP_CLIENT_HH
#define _RTSP_CLIENT_HH

#ifndef _MEDIA_SESSION_HH
#include "MediaSession.hh"
#endif
#ifndef _NET_ADDRESS_HH
#include "NetAddress.hh"
#endif
#ifndef _DIGEST_AUTHENTICATION_HH
#include "DigestAuthentication.hh"
#endif
#ifndef _TLS_STATE_HH
#include "TLSState.hh"
#endif
#ifndef OMIT_REGISTER_HANDLING
#ifndef _RTSP_SERVER_HH
#include "RTSPServer.hh" // For the optional "HandlerForREGISTERCommand" mini-server
#endif
#endif

class RTSPClient: public Medium {
public:
  LIVE555_EXPORT static RTSPClient* createNew(UsageEnvironment& env, char const* rtspURL,
			       int verbosityLevel = 0,
			       char const* applicationName = NULL,
			       portNumBits tunnelOverHTTPPortNum = 0,
			       int socketNumToServer = -1);
  // If "tunnelOverHTTPPortNum" is non-zero, we tunnel RTSP (and RTP)
  //     over a HTTP connection with the given port number, using the technique
  //     described in Apple's document <http://developer.apple.com/documentation/QuickTime/QTSS/Concepts/chapter_2_section_14.html>
  // If "socketNumToServer" is >= 0, then it is the socket number of an already-existing TCP connection to the server.
  //     (In this case, "rtspURL" must point to the socket's endpoint, so that it can be accessed via the socket.)

  typedef void (__cdecl responseHandler)(RTSPClient* rtspClient,
				 int resultCode, char* resultString);
      // A function that is called in response to a RTSP command.  The parameters are as follows:
      //     "rtspClient": The "RTSPClient" object on which the original command was issued.
      //     "resultCode": If zero, then the command completed successfully.  If non-zero, then the command did not complete
      //         successfully, and "resultCode" indicates the error, as follows:
      //             A positive "resultCode" is a RTSP error code (for example, 404 means "not found")
      //             A negative "resultCode" indicates a socket/network error; 0-"resultCode" is the standard "errno" code.
      //     "resultString": A ('\0'-terminated) string returned along with the response, or else NULL.
      //         In particular:
      //             "resultString" for a successful "DESCRIBE" command will be the media session's SDP description.
      //             "resultString" for a successful "OPTIONS" command will be a list of allowed commands.
      //         Note that this string can be present (i.e., not NULL) even if "resultCode" is non-zero - i.e., an error message.
      //         Also, "resultString" can be NULL, even if "resultCode" is zero (e.g., if the RTSP command succeeded, but without
      //             including an appropriate result header).
      //         Note also that this string is dynamically allocated, and must be freed by the handler (or the caller)
      //             - using "delete[]".

  LIVE555_EXPORT unsigned sendDescribeCommand(responseHandler* responseHandler, Authenticator* authenticator = NULL);
      // Issues a RTSP "DESCRIBE" command, then returns the "CSeq" sequence number that was used in the command.
      // The (programmer-supplied) "responseHandler" function is called later to handle the response
      //     (or is called immediately - with an error code - if the command cannot be sent).
      // "authenticator" (optional) is used for access control.  If you have username and password strings, you can use this by
      //     passing an actual parameter that you created by creating an "Authenticator(username, password) object".
      //     (Note that if you supply a non-NULL "authenticator" parameter, you need do this only for the first command you send.)

  LIVE555_EXPORT unsigned sendOptionsCommand(responseHandler* responseHandler, Authenticator* authenticator = NULL);
      // Issues a RTSP "OPTIONS" command, then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)

  LIVE555_EXPORT unsigned sendAnnounceCommand(char const* sdpDescription, responseHandler* responseHandler, Authenticator* authenticator = NULL);
      // Issues a RTSP "ANNOUNCE" command (with "sdpDescription" as parameter),
      //     then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)

  LIVE555_EXPORT unsigned sendSetupCommand(MediaSubsession& subsession, responseHandler* responseHandler,
			    Boolean streamOutgoing = False,
			    Boolean streamUsingTCP = False,
			    Boolean forceMulticastOnUnspecified = False,
			    Authenticator* authenticator = NULL);
      // Issues a RTSP "SETUP" command, then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)

  LIVE555_EXPORT unsigned sendPlayCommand(MediaSession& session, responseHandler* responseHandler,
			   double start = 0.0f, double end = -1.0f, float scale = 1.0f,
			   Authenticator* authenticator = NULL);
      // Issues an aggregate RTSP "PLAY" command on "session", then returns the "CSeq" sequence number that was used in the command.
      // (Note: start=-1 means 'resume'; end=-1 means 'play to end')
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)
  LIVE555_EXPORT unsigned sendPlayCommand(MediaSubsession& subsession, responseHandler* responseHandler,
			   double start = 0.0f, double end = -1.0f, float scale = 1.0f,
			   Authenticator* authenticator = NULL);
      // Issues a RTSP "PLAY" command on "subsession", then returns the "CSeq" sequence number that was used in the command.
      // (Note: start=-1 means 'resume'; end=-1 means 'play to end')
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)

  // Alternative forms of "sendPlayCommand()", used to send "PLAY" commands that include an 'absolute' time range:
  // (The "absStartTime" string (and "absEndTime" string, if present) *must* be of the form
  //  "YYYYMMDDTHHMMSSZ" or "YYYYMMDDTHHMMSS.<frac>Z")
  LIVE555_EXPORT unsigned sendPlayCommand(MediaSession& session, responseHandler* responseHandler,
			   char const* absStartTime, char const* absEndTime = NULL, float scale = 1.0f,
			   Authenticator* authenticator = NULL);
  LIVE555_EXPORT unsigned sendPlayCommand(MediaSubsession& subsession, responseHandler* responseHandler,
			   char const* absStartTime, char const* absEndTime = NULL, float scale = 1.0f,
			   Authenticator* authenticator = NULL);

  LIVE555_EXPORT unsigned sendPauseCommand(MediaSession& session, responseHandler* responseHandler, Authenticator* authenticator = NULL);
      // Issues an aggregate RTSP "PAUSE" command on "session", then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)
  LIVE555_EXPORT unsigned sendPauseCommand(MediaSubsession& subsession, responseHandler* responseHandler, Authenticator* authenticator = NULL);
      // Issues a RTSP "PAUSE" command on "subsession", then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)

  LIVE555_EXPORT unsigned sendRecordCommand(MediaSession& session, responseHandler* responseHandler, Authenticator* authenticator = NULL);
      // Issues an aggregate RTSP "RECORD" command on "session", then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)
  LIVE555_EXPORT unsigned sendRecordCommand(MediaSubsession& subsession, responseHandler* responseHandler, Authenticator* authenticator = NULL);
      // Issues a RTSP "RECORD" command on "subsession", then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)

  LIVE555_EXPORT unsigned sendTeardownCommand(MediaSession& session, responseHandler* responseHandler, Authenticator* authenticator = NULL);
      // Issues an aggregate RTSP "TEARDOWN" command on "session", then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)
  LIVE555_EXPORT unsigned sendTeardownCommand(MediaSubsession& subsession, responseHandler* responseHandler, Authenticator* authenticator = NULL);
      // Issues a RTSP "TEARDOWN" command on "subsession", then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)

  LIVE555_EXPORT unsigned sendSetParameterCommand(MediaSession& session, responseHandler* responseHandler,
				   char const* parameterName, char const* parameterValue,
				   Authenticator* authenticator = NULL);
      // Issues an aggregate RTSP "SET_PARAMETER" command on "session", then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)

  LIVE555_EXPORT unsigned sendGetParameterCommand(MediaSession& session, responseHandler* responseHandler, char const* parameterName,
				   Authenticator* authenticator = NULL);
      // Issues an aggregate RTSP "GET_PARAMETER" command on "session", then returns the "CSeq" sequence number that was used in the command.
      // (The "responseHandler" and "authenticator" parameters are as described for "sendDescribeCommand".)

  LIVE555_EXPORT void setRequireValue(char const* requireValue = NULL);
      // Sets a string to be used as the value of a "Require:" header to be included in
      // subsequent RTSP commands.  Call "setRequireValue()" again (i.e., with no parameter)
      // to clear this (and so stop "Require:" headers from being included in subsequent cmds).

  LIVE555_EXPORT void sendDummyUDPPackets(MediaSession& session, unsigned numDummyPackets = 2);
  LIVE555_EXPORT void sendDummyUDPPackets(MediaSubsession& subsession, unsigned numDummyPackets = 2);
      // Sends short 'dummy' (i.e., non-RTP or RTCP) UDP packets towards the server, to increase
      // the likelihood of RTP/RTCP packets from the server reaching us if we're behind a NAT.
      // (If we requested RTP-over-TCP streaming, then these functions have no effect.)
      // Our implementation automatically does this just prior to sending each "PLAY" command;
      // You should not call these functions yourself unless you know what you're doing.

  LIVE555_EXPORT void setSpeed(MediaSession& session, float speed = 1.0f);
      // Set (recorded) media download speed to given value to support faster download using 'Speed:'
      // option on 'PLAY' command.

  LIVE555_EXPORT Boolean changeResponseHandler(unsigned cseq, responseHandler* newResponseHandler);
      // Changes the response handler for the previously-performed command (whose operation returned "cseq").
      // (To turn off any response handling for the command, use a "newResponseHandler" value of NULL.  This might be done as part
      //  of an implementation of a 'timeout handler' on the command, for example.)
      // This function returns True iff "cseq" was for a valid previously-performed command (whose response is still unhandled).

  int socketNum() const { return fInputSocketNum; }

  LIVE555_EXPORT static Boolean lookupByName(UsageEnvironment& env,
			      char const* sourceName,
			      RTSPClient*& resultClient);

  LIVE555_EXPORT Boolean parseRTSPURL(char const* url,
		       char*& username, char*& password, NetAddress& address, portNumBits& portNum, char const** urlSuffix = NULL);
      // Parses "url" as "rtsp://[<username>[:<password>]@]<server-address-or-name>[:<port>][/<stream-name>]"
      // (Note that the returned "username" and "password" are either NULL, or heap-allocated strings that the caller must later delete[].)

  LIVE555_EXPORT void setUserAgentString(char const* userAgentName);
      // sets an alternative string to be used in RTSP "User-Agent:" headers

  void disallowBasicAuthentication() { fAllowBasicAuthentication = False; }
      // call this if you don't want the server to request 'Basic' authentication
      // (which would cause the client to send usernames and passwords over the net).

  unsigned sessionTimeoutParameter() const { return fSessionTimeoutParameter; }

  char const* url() const { return fBaseURL; }

  LIVE555_EXPORT static unsigned responseBufferSize;

public: // Some compilers complain if this is "private:"
  // The state of a request-in-progress:
  class RequestRecord {
  public:
    LIVE555_EXPORT RequestRecord(unsigned cseq, char const* commandName, responseHandler* handler,
		  MediaSession* session = NULL, MediaSubsession* subsession = NULL, u_int32_t booleanFlags = 0,
		  double start = 0.0f, double end = -1.0f, float scale = 1.0f, char const* contentStr = NULL);
    LIVE555_EXPORT RequestRecord(unsigned cseq, responseHandler* handler,
		  char const* absStartTime, char const* absEndTime = NULL, float scale = 1.0f,
		  MediaSession* session = NULL, MediaSubsession* subsession = NULL);
        // alternative constructor for creating "PLAY" requests that include 'absolute' time values
    LIVE555_EXPORT virtual ~RequestRecord();

    RequestRecord*& next() { return fNext; }
    unsigned& cseq() { return fCSeq; }
    char const* commandName() const { return fCommandName; }
    MediaSession* session() const { return fSession; }
    MediaSubsession* subsession() const { return fSubsession; }
    u_int32_t booleanFlags() const { return fBooleanFlags; }
    double start() const { return fStart; }
    double end() const { return fEnd; }
    char const* absStartTime() const { return fAbsStartTime; }
    char const* absEndTime() const { return fAbsEndTime; }
    float scale() const { return fScale; }
    char* contentStr() const { return fContentStr; }
    responseHandler*& handler() { return fHandler; }

  private:
    RequestRecord* fNext;
    unsigned fCSeq;
    char const* fCommandName;
    MediaSession* fSession;
    MediaSubsession* fSubsession;
    u_int32_t fBooleanFlags;
    double fStart, fEnd;
    char *fAbsStartTime, *fAbsEndTime; // used for optional 'absolute' (i.e., "time=") range specifications
    float fScale;
    char* fContentStr;
    responseHandler* fHandler;
  };

protected:
  LIVE555_EXPORT RTSPClient(UsageEnvironment& env, char const* rtspURL,
	     int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum, int socketNumToServer);
      // called only by createNew();
  LIVE555_EXPORT virtual ~RTSPClient();

  LIVE555_EXPORT void reset();
  LIVE555_EXPORT void setBaseURL(char const* url);
  LIVE555_EXPORT int grabSocket(); // allows a subclass to reuse our input socket, so that it won't get closed when we're deleted
  LIVE555_EXPORT virtual unsigned sendRequest(RequestRecord* request);
  LIVE555_EXPORT virtual Boolean setRequestFields(RequestRecord* request,
				   char*& cmdURL, Boolean& cmdURLWasAllocated,
				   char const*& protocolStr,
				   char*& extraHeaders, Boolean& extraHeadersWereAllocated);
      // used to implement "sendRequest()"; subclasses may reimplement this (e.g., when implementing a new command name)
  LIVE555_EXPORT virtual int connectToServer(int socketNum, portNumBits remotePortNum); // used to implement "openConnection()"; result values: -1: failure; 0: pending; 1: success

private: // redefined virtual functions
  LIVE555_EXPORT virtual Boolean isRTSPClient() const;

private:
  class RequestQueue {
  public:
    LIVE555_EXPORT RequestQueue();
    LIVE555_EXPORT RequestQueue(RequestQueue& origQueue); // moves the queue contents to the new queue
    LIVE555_EXPORT virtual ~RequestQueue();

    LIVE555_EXPORT void enqueue(RequestRecord* request); // "request" must not be NULL
    LIVE555_EXPORT RequestRecord* dequeue();
    LIVE555_EXPORT void putAtHead(RequestRecord* request); // "request" must not be NULL
    LIVE555_EXPORT RequestRecord* findByCSeq(unsigned cseq);
    Boolean isEmpty() const { return fHead == NULL; }
    LIVE555_EXPORT void reset();

  private:
    RequestRecord* fHead;
    RequestRecord* fTail;
  };

  LIVE555_EXPORT void resetTCPSockets();
  LIVE555_EXPORT void resetResponseBuffer();
  LIVE555_EXPORT int openConnection(); // result values: -1: failure; 0: pending; 1: success
  LIVE555_EXPORT char* createAuthenticatorString(char const* cmd, char const* url);
  LIVE555_EXPORT char* createBlocksizeString(Boolean streamUsingTCP);
  LIVE555_EXPORT char* createKeyMgmtString(char const* url, MediaSubsession const& subsession);
  LIVE555_EXPORT void handleRequestError(RequestRecord* request);
  LIVE555_EXPORT Boolean parseResponseCode(char const* line, unsigned& responseCode, char const*& responseString);
  LIVE555_EXPORT void handleIncomingRequest();
  LIVE555_EXPORT static Boolean checkForHeader(char const* line, char const* headerName, unsigned headerNameLength, char const*& headerParams);
  LIVE555_EXPORT Boolean parseTransportParams(char const* paramsStr,
			       char*& serverAddressStr, portNumBits& serverPortNum,
			       unsigned char& rtpChannelId, unsigned char& rtcpChannelId);
  LIVE555_EXPORT Boolean parseScaleParam(char const* paramStr, float& scale);
  LIVE555_EXPORT Boolean parseSpeedParam(char const* paramStr, float& speed);
  LIVE555_EXPORT Boolean parseRTPInfoParams(char const*& paramStr, u_int16_t& seqNum, u_int32_t& timestamp);
  LIVE555_EXPORT Boolean handleSETUPResponse(MediaSubsession& subsession, char const* sessionParamsStr, char const* transportParamsStr,
			      Boolean streamUsingTCP);
  LIVE555_EXPORT Boolean handlePLAYResponse(MediaSession* session, MediaSubsession* subsession,
                             char const* scaleParamsStr, const char* speedParamsStr,
			     char const* rangeParamsStr, char const* rtpInfoParamsStr);
  LIVE555_EXPORT Boolean handleTEARDOWNResponse(MediaSession& session, MediaSubsession& subsession);
  LIVE555_EXPORT Boolean handleGET_PARAMETERResponse(char const* parameterName, char*& resultValueString, char* resultValueStringEnd);
  LIVE555_EXPORT Boolean handleAuthenticationFailure(char const* wwwAuthenticateParamsStr);
  LIVE555_EXPORT Boolean resendCommand(RequestRecord* request);
  LIVE555_EXPORT char const* sessionURL(MediaSession const& session) const;
  LIVE555_EXPORT static void handleAlternativeRequestByte(void*, u_int8_t requestByte);
  LIVE555_EXPORT void handleAlternativeRequestByte1(u_int8_t requestByte);
  LIVE555_EXPORT void constructSubsessionURL(MediaSubsession const& subsession,
			      char const*& prefix,
			      char const*& separator,
			      char const*& suffix);

  // Support for tunneling RTSP-over-HTTP:
  LIVE555_EXPORT Boolean setupHTTPTunneling1(); // send the HTTP "GET"
  LIVE555_EXPORT static void responseHandlerForHTTP_GET(RTSPClient* rtspClient, int responseCode, char* responseString);
  LIVE555_EXPORT void responseHandlerForHTTP_GET1(int responseCode, char* responseString);
  LIVE555_EXPORT Boolean setupHTTPTunneling2(); // send the HTTP "POST"

  // Support for asynchronous connections to the server:
  LIVE555_EXPORT static void connectionHandler(void*, int /*mask*/);
  LIVE555_EXPORT void connectionHandler1();

  // Support for handling data sent back by a server:
  LIVE555_EXPORT static void incomingDataHandler(void*, int /*mask*/);
  LIVE555_EXPORT void incomingDataHandler1();
  LIVE555_EXPORT void handleResponseBytes(int newBytesRead);

  // Writing/reading data over a (already set-up) connection:
  LIVE555_EXPORT int write(const char* data, unsigned count);
  LIVE555_EXPORT int read(u_int8_t* buffer, unsigned bufferSize);

public:
  u_int16_t desiredMaxIncomingPacketSize;
    // If set to a value >0, then a "Blocksize:" header with this value (minus an allowance for
    // IP, UDP, and RTP headers) will be sent with each "SETUP" request.

protected:
  int fVerbosityLevel;
  unsigned fCSeq; // sequence number, used in consecutive requests
  Authenticator fCurrentAuthenticator;
  Boolean fAllowBasicAuthentication;
  struct sockaddr_storage fServerAddress;

private:
  portNumBits fTunnelOverHTTPPortNum;
  char* fUserAgentHeaderStr;
  unsigned fUserAgentHeaderStrLen;
  int fInputSocketNum, fOutputSocketNum;
  char* fBaseURL;
  unsigned char fTCPStreamIdCount; // used for (optional) RTP/TCP
  char* fLastSessionId;
  unsigned fSessionTimeoutParameter; // optionally set in response "Session:" headers
  char* fResponseBuffer;
  unsigned fResponseBytesAlreadySeen, fResponseBufferBytesLeft;
  RequestQueue fRequestsAwaitingConnection, fRequestsAwaitingHTTPTunneling, fRequestsAwaitingResponse;
  char* fRequireStr;

  // Support for tunneling RTSP-over-HTTP:
  char fSessionCookie[33];
  unsigned fSessionCookieCounter;
  Boolean fHTTPTunnelingConnectionIsPending;

  // Optional support for TLS:
  ClientTLSState fTLS;
  ClientTLSState fPOSTSocketTLS; // used only for RTSP-over-HTTPS
  ClientTLSState* fInputTLS;
  ClientTLSState* fOutputTLS;
  friend class ClientTLSState;
};


#ifndef OMIT_REGISTER_HANDLING
////////// HandlerServerForREGISTERCommand /////////

// A simple server that creates a new "RTSPClient" object whenever a "REGISTER" request arrives (specifying the "rtsp://" URL
// of a stream).  The new "RTSPClient" object will be created with the specified URL, and passed to the provided handler function.

typedef void __cdecl onRTSPClientCreationFunc(RTSPClient* newRTSPClient, Boolean requestStreamingOverTCP);

class HandlerServerForREGISTERCommand: public RTSPServer {
public:
  LIVE555_EXPORT static HandlerServerForREGISTERCommand* createNew(UsageEnvironment& env, onRTSPClientCreationFunc* creationFunc,
						    Port ourPort = 0, UserAuthenticationDatabase* authDatabase = NULL,
						    int verbosityLevel = 0, char const* applicationName = NULL);
      // If ourPort.num() == 0, we'll choose the port number ourself.  (Use the following function to get it.)
  portNumBits serverPortNum() const { return ntohs(fServerPort.num()); }

protected:
  LIVE555_EXPORT HandlerServerForREGISTERCommand(UsageEnvironment& env, onRTSPClientCreationFunc* creationFunc, int ourSocketIPv4, int ourSocketIPv6, Port ourPort,
				  UserAuthenticationDatabase* authDatabase, int verbosityLevel, char const* applicationName);
      // called only by createNew();
  LIVE555_EXPORT virtual ~HandlerServerForREGISTERCommand();

  LIVE555_EXPORT virtual RTSPClient* createNewRTSPClient(char const* rtspURL, int verbosityLevel, char const* applicationName,
					  int socketNumToServer);
      // This function - by default - creates a (base) "RTSPClient" object.  If you want to create a subclass
      // of "RTSPClient" instead, then subclass this class, and redefine this virtual function.

protected: // redefined virtual functions
  LIVE555_EXPORT virtual char const* allowedCommandNames(); // "OPTIONS", "REGISTER", and (perhaps) "DEREGISTER" only
  LIVE555_EXPORT virtual Boolean weImplementREGISTER(char const* cmd/*"REGISTER" or "DEREGISTER"*/,
				      char const* proxyURLSuffix, char*& responseStr);
      // redefined to return True (for cmd=="REGISTER")
  LIVE555_EXPORT virtual void implementCmd_REGISTER(char const* cmd/*"REGISTER" or "DEREGISTER"*/,
				     char const* url, char const* urlSuffix, int socketToRemoteServer,
				     Boolean deliverViaTCP, char const* proxyURLSuffix);

private:
  onRTSPClientCreationFunc* fCreationFunc;
  int fVerbosityLevel;
  char* fApplicationName;
};
#endif

#endif
