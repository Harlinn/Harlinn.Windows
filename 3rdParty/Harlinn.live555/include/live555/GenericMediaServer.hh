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
// A generic media server class, used to implement a RTSP server, and any other server that uses
//  "ServerMediaSession" objects to describe media to be served.
// C++ header

#ifndef _GENERIC_MEDIA_SERVER_HH
#define _GENERIC_MEDIA_SERVER_HH

#ifndef _MEDIA_HH
#include "Media.hh"
#endif
#ifndef _SERVER_MEDIA_SESSION_HH
#include "ServerMediaSession.hh"
#endif

#ifndef REQUEST_BUFFER_SIZE
#define REQUEST_BUFFER_SIZE 20000 // for incoming requests
#endif
#ifndef RESPONSE_BUFFER_SIZE
#define RESPONSE_BUFFER_SIZE 20000
#endif

// Typedef for a handler function that gets called when "lookupServerMediaSession()"
// (defined below) completes:
typedef void __cdecl lookupServerMediaSessionCompletionFunc(void* clientData,
						    ServerMediaSession* sessionLookedUp);

class GenericMediaServer: public Medium {
public:
  LIVE555_EXPORT virtual void addServerMediaSession(ServerMediaSession* serverMediaSession);

  LIVE555_EXPORT virtual void lookupServerMediaSession(char const* streamName,
					lookupServerMediaSessionCompletionFunc* completionFunc,
					void* completionClientData,
					Boolean isFirstLookupInSession = True);
      // Note: This is a virtual function, so can be reimplemented by subclasses.
  LIVE555_EXPORT void lookupServerMediaSession(char const* streamName,
				void (GenericMediaServer::*memberFunc)(ServerMediaSession*));
      // Special case of "lookupServerMediaSession()" where the 'completion function' is a
      // member function of "GenericMediaServer" (and the 'completion client data' is "this".)

  LIVE555_EXPORT void removeServerMediaSession(ServerMediaSession* serverMediaSession);
      // Removes the "ServerMediaSession" object from our lookup table, so it will no longer be accessible by new clients.
      // (However, any *existing* client sessions that use this "ServerMediaSession" object will continue streaming.
      //  The "ServerMediaSession" object will not get deleted until all of these client sessions have closed.)
      // (To both delete the "ServerMediaSession" object *and* close all client sessions that use it,
      //  call "deleteServerMediaSession(serverMediaSession)" instead.)
  LIVE555_EXPORT virtual void removeServerMediaSession(char const* streamName);
     // ditto

  LIVE555_EXPORT void closeAllClientSessionsForServerMediaSession(ServerMediaSession* serverMediaSession);
      // Closes (from the server) all client sessions that are currently using this "ServerMediaSession" object.
      // Note, however, that the "ServerMediaSession" object remains accessible by new clients.
  LIVE555_EXPORT virtual void closeAllClientSessionsForServerMediaSession(char const* streamName);
     // ditto

  LIVE555_EXPORT void deleteServerMediaSession(ServerMediaSession* serverMediaSession);
      // Equivalent to:
      //     "closeAllClientSessionsForServerMediaSession(serverMediaSession); removeServerMediaSession(serverMediaSession);"
  LIVE555_EXPORT virtual void deleteServerMediaSession(char const* streamName);
      // Equivalent to:
      //     "closeAllClientSessionsForServerMediaSession(streamName); removeServerMediaSession(streamName);

  unsigned numClientSessions() const { return fClientSessions->numEntries(); }

protected:
  LIVE555_EXPORT GenericMediaServer(UsageEnvironment& env, int ourSocketIPv4, int ourSocketIPv6, Port ourPort,
		     unsigned reclamationSeconds);
      // If "reclamationSeconds" > 0, then the "ClientSession" state for each client will get
      // reclaimed if no activity from the client is detected in at least "reclamationSeconds".
  // we're an abstract base class
  LIVE555_EXPORT virtual ~GenericMediaServer();
  LIVE555_EXPORT void cleanup(); // MUST be called in the destructor of any subclass of us

  LIVE555_EXPORT static int setUpOurSocket(UsageEnvironment& env, Port& ourPort, int domain);

  LIVE555_EXPORT static void incomingConnectionHandlerIPv4(void*, int /*mask*/);
  LIVE555_EXPORT static void incomingConnectionHandlerIPv6(void*, int /*mask*/);
  LIVE555_EXPORT void incomingConnectionHandlerIPv4();
  LIVE555_EXPORT void incomingConnectionHandlerIPv6();
  LIVE555_EXPORT void incomingConnectionHandlerOnSocket(int serverSocket);

  LIVE555_EXPORT void setTLSFileNames(char const* certFileName, char const* privKeyFileName);

public: // should be protected, but some old compilers complain otherwise
  // The state of a TCP connection used by a client:
  class ClientConnection {
  protected:
    LIVE555_EXPORT ClientConnection(GenericMediaServer& ourServer,
		     int clientSocket, struct sockaddr_storage const& clientAddr,
		     Boolean useTLS);
    LIVE555_EXPORT virtual ~ClientConnection();

    UsageEnvironment& envir() { return fOurServer.envir(); }
    LIVE555_EXPORT void closeSockets();

    LIVE555_EXPORT static void incomingRequestHandler(void*, int /*mask*/);
    LIVE555_EXPORT void incomingRequestHandler();
    LIVE555_EXPORT virtual void handleRequestBytes(int newBytesRead) = 0;
    LIVE555_EXPORT void resetRequestBuffer();

  protected:
    friend class GenericMediaServer;
    friend class ClientSession;
    friend class RTSPServer; // needed to make some broken Windows compilers work; remove this in the future when we end support for Windows
    GenericMediaServer& fOurServer;
    int fOurSocket;
    struct sockaddr_storage fClientAddr;
    unsigned char fRequestBuffer[REQUEST_BUFFER_SIZE];
    unsigned char fResponseBuffer[RESPONSE_BUFFER_SIZE];
    unsigned fRequestBytesAlreadySeen, fRequestBufferBytesLeft;

    // Optional support for TLS:
    ServerTLSState fTLS;
    ServerTLSState* fInputTLS; // by default, just points to "fTLS", but subclasses may change
    ServerTLSState* fOutputTLS; // ditto
  };

  // The state of an individual client session (using one or more sequential TCP connections) handled by a server:
  class ClientSession {
  protected:
    LIVE555_EXPORT ClientSession(GenericMediaServer& ourServer, u_int32_t sessionId);
    LIVE555_EXPORT virtual ~ClientSession();

    UsageEnvironment& envir() { return fOurServer.envir(); }
    LIVE555_EXPORT void noteLiveness();
    LIVE555_EXPORT static void noteClientLiveness(ClientSession* clientSession);
    LIVE555_EXPORT static void livenessTimeoutTask(ClientSession* clientSession);

  protected:
    friend class GenericMediaServer;
    friend class ClientConnection;
    GenericMediaServer& fOurServer;
    u_int32_t fOurSessionId;
    ServerMediaSession* fOurServerMediaSession;
    TaskToken fLivenessCheckTask;
  };

protected:
  virtual ClientConnection* createNewClientConnection(int clientSocket, struct sockaddr_storage const& clientAddr) = 0;
  virtual ClientSession* createNewClientSession(u_int32_t sessionId) = 0;

  LIVE555_EXPORT ClientSession* createNewClientSessionWithId();
      // Generates a new (unused) random session id, and calls the "createNewClientSession()"
      // virtual function with this session id as parameter.

  // Lookup a "ClientSession" object by sessionId (integer, and string):
  LIVE555_EXPORT ClientSession* lookupClientSession(u_int32_t sessionId);
  LIVE555_EXPORT ClientSession* lookupClientSession(char const* sessionIdStr);

  // An iterator over our "ServerMediaSession" objects:
  class ServerMediaSessionIterator {
  public:
    LIVE555_EXPORT ServerMediaSessionIterator(GenericMediaServer& server);
    LIVE555_EXPORT virtual ~ServerMediaSessionIterator();
    LIVE555_EXPORT ServerMediaSession* next();
  private:
    HashTable::Iterator* fOurIterator;
  };

  // The basic, synchronous "ServerMediaSession" lookup operation; only for subclasses:
  LIVE555_EXPORT ServerMediaSession* getServerMediaSession(char const* streamName);
  
protected:
  friend class ClientConnection;
  friend class ClientSession;	
  friend class ServerMediaSessionIterator;
  int fServerSocketIPv4, fServerSocketIPv6;
  Port fServerPort;
  unsigned fReclamationSeconds;

private:
  HashTable* fServerMediaSessions; // maps 'stream name' strings to "ServerMediaSession" objects
  HashTable* fClientConnections; // the "ClientConnection" objects that we're using
  HashTable* fClientSessions; // maps 'session id' strings to "ClientSession" objects
  u_int32_t fPreviousClientSessionId;

  char const* fTLSCertificateFileName;
  char const* fTLSPrivateKeyFileName;
};

// A data structure used for optional user/password authentication:

class UserAuthenticationDatabase {
public:
  LIVE555_EXPORT UserAuthenticationDatabase(char const* realm = NULL,
			     Boolean passwordsAreMD5 = False);
    // If "passwordsAreMD5" is True, then each password stored into, or removed from,
    // the database is actually the value computed
    // by md5(<username>:<realm>:<actual-password>)
  LIVE555_EXPORT virtual ~UserAuthenticationDatabase();

  LIVE555_EXPORT virtual void addUserRecord(char const* username, char const* password);
  LIVE555_EXPORT virtual void removeUserRecord(char const* username);

  LIVE555_EXPORT virtual char const* lookupPassword(char const* username);
      // returns NULL if the user name was not present

  char const* realm() { return fRealm; }
  Boolean passwordsAreMD5() { return fPasswordsAreMD5; }

protected:
  HashTable* fTable;
  char* fRealm;
  Boolean fPasswordsAreMD5;
};

#endif
