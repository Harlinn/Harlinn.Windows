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
// A RTSP server
// C++ header

#ifndef _RTSP_SERVER_HH
#define _RTSP_SERVER_HH

#ifndef _GENERIC_MEDIA_SERVER_HH
#include "GenericMediaServer.hh"
#endif
#ifndef _DIGEST_AUTHENTICATION_HH
#include "DigestAuthentication.hh"
#endif

class RTSPServer: public GenericMediaServer {
public:
  LIVE555_EXPORT static RTSPServer* createNew(UsageEnvironment& env, Port ourPort = 554,
			       UserAuthenticationDatabase* authDatabase = NULL,
			       unsigned reclamationSeconds = 65);
      // If ourPort.num() == 0, we'll choose the port number
      // Note: The caller is responsible for reclaiming "authDatabase"
      // If "reclamationSeconds" > 0, then the "RTSPClientSession" state for
      //     each client will get reclaimed (and the corresponding RTP stream(s)
      //     torn down) if no RTSP commands - or RTCP "RR" packets - from the
      //     client are received in at least "reclamationSeconds" seconds.

  LIVE555_EXPORT static Boolean lookupByName(UsageEnvironment& env, char const* name,
			      RTSPServer*& resultServer);

  typedef void (__cdecl responseHandlerForREGISTER)(RTSPServer* rtspServer, unsigned requestId, int resultCode, char* resultString);
  LIVE555_EXPORT unsigned registerStream(ServerMediaSession* serverMediaSession,
			  char const* remoteClientNameOrAddress, portNumBits remoteClientPortNum,
			  responseHandlerForREGISTER* responseHandler,
			  char const* username = NULL, char const* password = NULL,
			  Boolean receiveOurStreamViaTCP = False,
			  char const* proxyURLSuffix = NULL);
  // 'Register' the stream represented by "serverMediaSession" with the given remote client (specifed by name and port number).
  // This is done using our custom "REGISTER" RTSP command.
  // The function returns a unique number that can be used to identify the request; this number is also passed to "responseHandler".
  // When a response is received from the remote client (or the "REGISTER" request fails), the specified response handler
  //   (if non-NULL) is called.  (Note that the "resultString" passed to the handler was dynamically allocated,
  //   and should be delete[]d by the handler after use.)
  // If "receiveOurStreamViaTCP" is True, then we're requesting that the remote client access our stream using RTP/RTCP-over-TCP.
  //   (Otherwise, the remote client may choose regular RTP/RTCP-over-UDP streaming.)
  // "proxyURLSuffix" (optional) is used only when the remote client is also a proxy server.
  //   It tells the proxy server the suffix that it should use in its "rtsp://" URL (when front-end clients access the stream)

  typedef void (__cdecl responseHandlerForDEREGISTER)(RTSPServer* rtspServer, unsigned requestId, int resultCode, char* resultString);
  LIVE555_EXPORT unsigned deregisterStream(ServerMediaSession* serverMediaSession,
			    char const* remoteClientNameOrAddress, portNumBits remoteClientPortNum,
			    responseHandlerForDEREGISTER* responseHandler,
			    char const* username = NULL, char const* password = NULL,
			    char const* proxyURLSuffix = NULL);
  // Used to turn off a previous "registerStream()" - using our custom "DEREGISTER" RTSP command.
  
  LIVE555_EXPORT char* rtspURL(ServerMediaSession const* serverMediaSession,
		int clientSocket = -1, Boolean useIPv6 = False) const;
      // returns a "rtsp://" URL that could be used to access the
      // specified session (which must already have been added to
      // us using "addServerMediaSession()".
      // This string is dynamically allocated; caller should delete[]
      // (If "clientSocket" is non-negative, then it is used (by calling "getsockname()") to determine
      //  the IP address to be used in the URL.)
  // Shortcuts:
  char* ipv4rtspURL(ServerMediaSession const* serverMediaSession, int clientSocket = -1) {
    return rtspURL(serverMediaSession, clientSocket, False);
  }
  char* ipv6rtspURL(ServerMediaSession const* serverMediaSession, int clientSocket = -1) {
    return rtspURL(serverMediaSession, clientSocket, True);
  }

  LIVE555_EXPORT char* rtspURLPrefix(int clientSocket = -1, Boolean useIPv6 = False) const;
      // like "rtspURL()", except that it returns just the common prefix used by
      // each session's "rtsp://" URL.
      // This string is dynamically allocated; caller should delete[]
  // Shortcuts:
  char* ipv4rtspURLPrefix(int clientSocket = -1) { return rtspURLPrefix(clientSocket, False); }
  char* ipv6rtspURLPrefix(int clientSocket = -1) { return rtspURLPrefix(clientSocket, True); }

  UserAuthenticationDatabase* setAuthenticationDatabase(UserAuthenticationDatabase* newDB);
      // Changes the server's authentication database to "newDB", returning a pointer to the old database (if there was one).
      // "newDB" may be NULL (you can use this to disable authentication at runtime, if desired).

  void disableStreamingRTPOverTCP() {
    fAllowStreamingRTPOverTCP = False;
  }

  LIVE555_EXPORT Boolean setUpTunnelingOverHTTP(Port httpPort);
      // (Attempts to) enable RTSP-over-HTTP tunneling on the specified port.
      // Returns True iff the specified port can be used in this way (i.e., it's not already being used for a separate HTTP server).
      // Note: RTSP-over-HTTP tunneling is described in
      //  http://mirror.informatimago.com/next/developer.apple.com/quicktime/icefloe/dispatch028.html
      //  and http://images.apple.com/br/quicktime/pdf/QTSS_Modules.pdf
  LIVE555_EXPORT portNumBits httpServerPortNum() const; // in host byte order.  (Returns 0 if not present.)

  LIVE555_EXPORT void setTLSState(char const* certFileName, char const* privKeyFileName,
		   Boolean weServeSRTP = True, Boolean weEncryptSRTP = True);

protected:
  LIVE555_EXPORT RTSPServer(UsageEnvironment& env,
	     int ourSocketIPv4, int ourSocketIPv6, Port ourPort,
	     UserAuthenticationDatabase* authDatabase,
	     unsigned reclamationSeconds);
      // called only by createNew();
  LIVE555_EXPORT virtual ~RTSPServer();

  LIVE555_EXPORT virtual char const* allowedCommandNames(); // used to implement "RTSPClientConnection::handleCmd_OPTIONS()"
  LIVE555_EXPORT virtual Boolean weImplementREGISTER(char const* cmd/*"REGISTER" or "DEREGISTER"*/,
				      char const* proxyURLSuffix, char*& responseStr);
      // used to implement "RTSPClientConnection::handleCmd_REGISTER()"
      // Note: "responseStr" is dynamically allocated (or NULL), and should be delete[]d after the call
  LIVE555_EXPORT virtual void implementCmd_REGISTER(char const* cmd/*"REGISTER" or "DEREGISTER"*/,
				     char const* url, char const* urlSuffix, int socketToRemoteServer,
				     Boolean deliverViaTCP, char const* proxyURLSuffix);
      // used to implement "RTSPClientConnection::handleCmd_REGISTER()"

  LIVE555_EXPORT virtual UserAuthenticationDatabase* getAuthenticationDatabaseForCommand(char const* cmdName);
  LIVE555_EXPORT virtual Boolean specialClientAccessCheck(int clientSocket,
					   struct sockaddr_storage const& clientAddr,
					   char const* urlSuffix);
      // a hook that allows subclassed servers to do server-specific access checking
      // on each client (e.g., based on client IP address), without using digest authentication.
  LIVE555_EXPORT virtual Boolean specialClientUserAccessCheck(int clientSocket,
					       struct sockaddr_storage const& clientAddr,
					       char const* urlSuffix, char const *username);
      // another hook that allows subclassed servers to do server-specific access checking
      // - this time after normal digest authentication has already taken place (and would otherwise allow access).
      // (This test can only be used to further restrict access, not to grant additional access.)
  LIVE555_EXPORT virtual void specialHandlingOfAuthenticationFailure(int clientSocket,
						      struct sockaddr_storage const& clientAddr,
						      char const* urlSuffix);
      // a hook that allows subclassed servers to take extra action whenevever an authentication failure occurs

public: // redefined virtual functions
  LIVE555_EXPORT virtual Boolean isRTSPServer() const;
  LIVE555_EXPORT virtual void addServerMediaSession(ServerMediaSession* serverMediaSession);

public: // should be protected, but some old compilers complain otherwise
  // The state of a TCP connection used by a RTSP client:
  class RTSPClientSession; // forward
  class RTSPClientConnection: public GenericMediaServer::ClientConnection {
  public:
    // A data structure that's used to implement the "REGISTER" command:
    class ParamsForREGISTER {
    public:
      LIVE555_EXPORT ParamsForREGISTER(char const* cmd/*"REGISTER" or "DEREGISTER"*/,
			RTSPClientConnection* ourConnection, char const* url, char const* urlSuffix,
			Boolean reuseConnection, Boolean deliverViaTCP, char const* proxyURLSuffix);
      LIVE555_EXPORT virtual ~ParamsForREGISTER();
    private:
      friend class RTSPClientConnection;
      char const* fCmd;
      RTSPClientConnection* fOurConnection;
      char* fURL;
      char* fURLSuffix;
      Boolean fReuseConnection, fDeliverViaTCP;
      char* fProxyURLSuffix;
    };
  protected: // redefined virtual functions:
    LIVE555_EXPORT virtual void handleRequestBytes(int newBytesRead);

  protected:
    LIVE555_EXPORT RTSPClientConnection(RTSPServer& ourServer,
			 int clientSocket, struct sockaddr_storage const& clientAddr,
			 Boolean useTLS = False);
    LIVE555_EXPORT virtual ~RTSPClientConnection();

    friend class RTSPServer;
    friend class RTSPClientSession;

    // Make the handler functions for each command virtual, to allow subclasses to reimplement them, if necessary:
    LIVE555_EXPORT virtual void handleCmd_OPTIONS();
        // You probably won't need to subclass/reimplement this function; reimplement "RTSPServer::allowedCommandNames()" instead.
    LIVE555_EXPORT virtual void handleCmd_GET_PARAMETER(char const* fullRequestStr); // when operating on the entire server
    LIVE555_EXPORT virtual void handleCmd_SET_PARAMETER(char const* fullRequestStr); // when operating on the entire server
    LIVE555_EXPORT virtual void handleCmd_DESCRIBE(char const* urlPreSuffix, char const* urlSuffix, char const* fullRequestStr);
    LIVE555_EXPORT static void DESCRIBELookupCompletionFunction(void* clientData, ServerMediaSession* sessionLookedUp);
    LIVE555_EXPORT virtual void handleCmd_DESCRIBE_afterLookup(ServerMediaSession* session);
    LIVE555_EXPORT virtual void handleCmd_REGISTER(char const* cmd/*"REGISTER" or "DEREGISTER"*/,
				    char const* url, char const* urlSuffix, char const* fullRequestStr,
				    Boolean reuseConnection, Boolean deliverViaTCP, char const* proxyURLSuffix);
        // You probably won't need to subclass/reimplement this function;
        //     reimplement "RTSPServer::weImplementREGISTER()" and "RTSPServer::implementCmd_REGISTER()" instead.
    LIVE555_EXPORT virtual void handleCmd_bad();
    LIVE555_EXPORT virtual void handleCmd_notSupported();
    LIVE555_EXPORT virtual void handleCmd_redirect(char const* urlSuffix);
    LIVE555_EXPORT virtual void handleCmd_notFound();
    LIVE555_EXPORT virtual void handleCmd_sessionNotFound();
    LIVE555_EXPORT virtual void handleCmd_unsupportedTransport();
    // Support for optional RTSP-over-HTTP tunneling:
    LIVE555_EXPORT virtual Boolean parseHTTPRequestString(char* resultCmdName, unsigned resultCmdNameMaxSize,
					   char* urlSuffix, unsigned urlSuffixMaxSize,
					   char* sessionCookie, unsigned sessionCookieMaxSize,
					   char* acceptStr, unsigned acceptStrMaxSize);
    LIVE555_EXPORT virtual void handleHTTPCmd_notSupported();
    LIVE555_EXPORT virtual void handleHTTPCmd_notFound();
    LIVE555_EXPORT virtual void handleHTTPCmd_OPTIONS();
    LIVE555_EXPORT virtual void handleHTTPCmd_TunnelingGET(char const* sessionCookie);
    LIVE555_EXPORT virtual Boolean handleHTTPCmd_TunnelingPOST(char const* sessionCookie, unsigned char const* extraData, unsigned extraDataSize);
    LIVE555_EXPORT virtual void handleHTTPCmd_StreamingGET(char const* urlSuffix, char const* fullRequestStr);
  protected:
    LIVE555_EXPORT void resetRequestBuffer();
    LIVE555_EXPORT void closeSocketsRTSP();
    LIVE555_EXPORT static void handleAlternativeRequestByte(void*, u_int8_t requestByte);
    LIVE555_EXPORT void handleAlternativeRequestByte1(u_int8_t requestByte);
    LIVE555_EXPORT Boolean authenticationOK(char const* cmdName, char const* urlSuffix, char const* fullRequestStr);
    LIVE555_EXPORT void changeClientInputSocket(int newSocketNum, ServerTLSState const* newTLSState,
				 unsigned char const* extraData, unsigned extraDataSize);
      // used to implement RTSP-over-HTTP tunneling
    LIVE555_EXPORT static void continueHandlingREGISTER(ParamsForREGISTER* params);
    LIVE555_EXPORT virtual void continueHandlingREGISTER1(ParamsForREGISTER* params);

    // Shortcuts for setting up a RTSP response (prior to sending it):
    LIVE555_EXPORT void setRTSPResponse(char const* responseStr);
    LIVE555_EXPORT void setRTSPResponse(char const* responseStr, u_int32_t sessionId);
    LIVE555_EXPORT void setRTSPResponse(char const* responseStr, char const* contentStr);
    LIVE555_EXPORT void setRTSPResponse(char const* responseStr, u_int32_t sessionId, char const* contentStr);

    RTSPServer& fOurRTSPServer; // same as ::fOurServer
    int& fClientInputSocket; // aliased to ::fOurSocket
    int fClientOutputSocket;
    ServerTLSState fPOSTSocketTLS; // used only for RTSP-over-HTTPS
    int fAddressFamily;
    Boolean fIsActive;
    unsigned char* fLastCRLF;
    unsigned fRecursionCount;
    char const* fCurrentCSeq;
    Authenticator fCurrentAuthenticator; // used if access control is needed
    char* fOurSessionCookie; // used for optional RTSP-over-HTTP tunneling
    unsigned fBase64RemainderCount; // used for optional RTSP-over-HTTP tunneling (possible values: 0,1,2,3)
    unsigned fScheduledDelayedTask;
  };

  // The state of an individual client session (using one or more sequential TCP connections) handled by a RTSP server:
  class RTSPClientSession: public GenericMediaServer::ClientSession {
  protected:
    LIVE555_EXPORT RTSPClientSession(RTSPServer& ourServer, u_int32_t sessionId);
    LIVE555_EXPORT virtual ~RTSPClientSession();

    friend class RTSPServer;
    friend class RTSPClientConnection;
    // Make the handler functions for each command virtual, to allow subclasses to redefine them:
    LIVE555_EXPORT virtual void handleCmd_SETUP(RTSPClientConnection* ourClientConnection,
				 char const* urlPreSuffix, char const* urlSuffix, char const* fullRequestStr);
    LIVE555_EXPORT static void SETUPLookupCompletionFunction1(void* clientData, ServerMediaSession* sessionLookedUp);
    LIVE555_EXPORT virtual void handleCmd_SETUP_afterLookup1(ServerMediaSession* sms);
    LIVE555_EXPORT static void SETUPLookupCompletionFunction2(void* clientData, ServerMediaSession* sessionLookedUp);
    LIVE555_EXPORT virtual void handleCmd_SETUP_afterLookup2(ServerMediaSession* sms);
    LIVE555_EXPORT virtual void handleCmd_withinSession(RTSPClientConnection* ourClientConnection,
					 char const* cmdName,
					 char const* urlPreSuffix, char const* urlSuffix,
					 char const* fullRequestStr);
    LIVE555_EXPORT virtual void handleCmd_TEARDOWN(RTSPClientConnection* ourClientConnection,
				    ServerMediaSubsession* subsession);
    LIVE555_EXPORT virtual void handleCmd_PLAY(RTSPClientConnection* ourClientConnection,
				ServerMediaSubsession* subsession, char const* fullRequestStr);
    LIVE555_EXPORT virtual void handleCmd_PAUSE(RTSPClientConnection* ourClientConnection,
				 ServerMediaSubsession* subsession);
    LIVE555_EXPORT virtual void handleCmd_GET_PARAMETER(RTSPClientConnection* ourClientConnection,
					 ServerMediaSubsession* subsession, char const* fullRequestStr);
    LIVE555_EXPORT virtual void handleCmd_SET_PARAMETER(RTSPClientConnection* ourClientConnection,
					 ServerMediaSubsession* subsession, char const* fullRequestStr);
  protected:
    LIVE555_EXPORT void deleteStreamByTrack(unsigned trackNum);
    LIVE555_EXPORT void reclaimStreamStates();
    Boolean isMulticast() const { return fIsMulticast; }

    // Shortcuts for setting up a RTSP response (prior to sending it):
    void setRTSPResponse(RTSPClientConnection* ourClientConnection, char const* responseStr) { ourClientConnection->setRTSPResponse(responseStr); }
    void setRTSPResponse(RTSPClientConnection* ourClientConnection, char const* responseStr, u_int32_t sessionId) { ourClientConnection->setRTSPResponse(responseStr, sessionId); }
    void setRTSPResponse(RTSPClientConnection* ourClientConnection, char const* responseStr, char const* contentStr) { ourClientConnection->setRTSPResponse(responseStr, contentStr); }
    void setRTSPResponse(RTSPClientConnection* ourClientConnection, char const* responseStr, u_int32_t sessionId, char const* contentStr) { ourClientConnection->setRTSPResponse(responseStr, sessionId, contentStr); }

  protected:
    RTSPServer& fOurRTSPServer; // same as ::fOurServer
    Boolean fIsMulticast, fStreamAfterSETUP;
    unsigned char fTCPStreamIdCount; // used for (optional) RTP/TCP
    Boolean usesTCPTransport() const { return fTCPStreamIdCount > 0; }
    unsigned fNumStreamStates;
    struct streamState {
      ServerMediaSubsession* subsession;
      int tcpSocketNum;
      void* streamToken;
    } * fStreamStates;

    // Member variables used to implement "handleCmd_SETUP()":
    RTSPServer::RTSPClientConnection* fOurClientConnection;
    char const* fURLPreSuffix; char const* fURLSuffix; char const* fFullRequestStr; char const* fTrackId;
  };

protected: // redefined virtual functions
  // If you subclass "RTSPClientConnection", then you must also redefine this virtual function in order
  // to create new objects of your subclass:
  LIVE555_EXPORT virtual ClientConnection* createNewClientConnection(int clientSocket, struct sockaddr_storage const& clientAddr);

protected:
  // If you subclass "RTSPClientSession", then you must also redefine this virtual function in order
  // to create new objects of your subclass:
  LIVE555_EXPORT virtual ClientSession* createNewClientSession(u_int32_t sessionId);

private:
  LIVE555_EXPORT static void incomingConnectionHandlerHTTPIPv4(void*, int /*mask*/);
  LIVE555_EXPORT void incomingConnectionHandlerHTTPIPv4();
  LIVE555_EXPORT static void incomingConnectionHandlerHTTPIPv6(void*, int /*mask*/);
  LIVE555_EXPORT void incomingConnectionHandlerHTTPIPv6();

  LIVE555_EXPORT void noteTCPStreamingOnSocket(int socketNum, RTSPClientSession* clientSession, unsigned trackNum);
  LIVE555_EXPORT void unnoteTCPStreamingOnSocket(int socketNum, RTSPClientSession* clientSession, unsigned trackNum);
  LIVE555_EXPORT void stopTCPStreamingOnSocket(int socketNum);

private:
  friend class RTSPClientConnection;
  friend class RTSPClientSession;
  friend class RegisterRequestRecord;
  friend class DeregisterRequestRecord;
  int fHTTPServerSocketIPv4, fHTTPServerSocketIPv6; // for optional RTSP-over-HTTP tunneling
  Port fHTTPServerPort; // ditto
  HashTable* fClientConnectionsForHTTPTunneling; // maps client-supplied 'session cookie' strings to "RTSPClientConnection"s
    // (used only for optional RTSP-over-HTTP tunneling)
  HashTable* fTCPStreamingDatabase;
    // maps TCP socket numbers to ids of sessions that are streaming over it (RTP/RTCP-over-TCP)
  HashTable* fPendingRegisterOrDeregisterRequests;
  unsigned fRegisterOrDeregisterRequestCounter;
  UserAuthenticationDatabase* fAuthDB;
  Boolean fAllowStreamingRTPOverTCP; // by default, True
  Boolean fOurConnectionsUseTLS; // by default, False
  Boolean fWeServeSRTP; // used only if "fOurConnectionsUseTLS" is True
  Boolean fWeEncryptSRTP; // used only if "fWeServeSRTP" is True
};


////////// A subclass of "RTSPServer" that implements the "REGISTER" command to set up proxying on the specified URL //////////

class RTSPServerWithREGISTERProxying: public RTSPServer {
public:
  LIVE555_EXPORT static RTSPServerWithREGISTERProxying* createNew(UsageEnvironment& env, Port ourPort = 554,
						   UserAuthenticationDatabase* authDatabase = NULL,
						   UserAuthenticationDatabase* authDatabaseForREGISTER = NULL,
						   unsigned reclamationSeconds = 65,
						   Boolean streamRTPOverTCP = False,
						   int verbosityLevelForProxying = 0,
						   char const* backEndUsername = NULL,
						   char const* backEndPassword = NULL);

protected:
  LIVE555_EXPORT RTSPServerWithREGISTERProxying(UsageEnvironment& env, int ourSocketIPv4, int ourSocketIPv6, Port ourPort,
				 UserAuthenticationDatabase* authDatabase, UserAuthenticationDatabase* authDatabaseForREGISTER,
				 unsigned reclamationSeconds,
				 Boolean streamRTPOverTCP, int verbosityLevelForProxying,
				 char const* backEndUsername, char const* backEndPassword);
  // called only by createNew();
  LIVE555_EXPORT virtual ~RTSPServerWithREGISTERProxying();

protected: // redefined virtual functions
  LIVE555_EXPORT virtual char const* allowedCommandNames();
  LIVE555_EXPORT virtual Boolean weImplementREGISTER(char const* cmd/*"REGISTER" or "DEREGISTER"*/,
				      char const* proxyURLSuffix, char*& responseStr);
  LIVE555_EXPORT virtual void implementCmd_REGISTER(char const* cmd/*"REGISTER" or "DEREGISTER"*/,
				     char const* url, char const* urlSuffix, int socketToRemoteServer,
				     Boolean deliverViaTCP, char const* proxyURLSuffix);
  LIVE555_EXPORT virtual UserAuthenticationDatabase* getAuthenticationDatabaseForCommand(char const* cmdName);

private:
  Boolean fStreamRTPOverTCP;
  int fVerbosityLevelForProxying;
  unsigned fRegisteredProxyCounter;
  char* fAllowedCommandNames;
  UserAuthenticationDatabase* fAuthDBForREGISTER;
  char* fBackEndUsername;
  char* fBackEndPassword;
}; 


// A special version of "parseTransportHeader()", used just for parsing the "Transport:" header
// in an incoming "REGISTER" command:
LIVE555_EXPORT void parseTransportHeaderForREGISTER(char const* buf, // in
				     Boolean &reuseConnection, // out
				     Boolean& deliverViaTCP, // out
				     char*& proxyURLSuffix); // out

#endif
