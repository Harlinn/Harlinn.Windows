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
// State encapsulating a TLS connection
// C++ header

#ifndef _TLS_STATE_HH
#define _TLS_STATE_HH

#ifndef _NET_COMMON_H
#include "NetCommon.h"
#endif
#ifndef _BOOLEAN_HH
#include "Boolean.hh"
#endif
#ifndef _USAGE_ENVIRONMENT_HH
#include "UsageEnvironment.hh"
#endif
#ifndef NO_OPENSSL
#include <openssl/ssl.h>
#endif

class TLSState {
public:
  Boolean isNeeded;

  LIVE555_EXPORT int write(const char* data, unsigned count);
  LIVE555_EXPORT int read(u_int8_t* buffer, unsigned bufferSize);

  LIVE555_EXPORT void nullify(); // clear the state so that the destructor will have no effect

protected: // we're an abstract base class
  LIVE555_EXPORT TLSState();
  LIVE555_EXPORT virtual ~TLSState();

#ifndef NO_OPENSSL
  LIVE555_EXPORT void initLibrary();
  LIVE555_EXPORT void reset();

protected:
  Boolean fHasBeenSetup;
  SSL_CTX* fCtx;
  SSL* fCon;
#endif
};

class ClientTLSState: public TLSState {
public:
  LIVE555_EXPORT ClientTLSState(class RTSPClient& client);
  LIVE555_EXPORT virtual ~ClientTLSState();

  LIVE555_EXPORT int connect(int socketNum); // returns: <0 (error), 0 (pending), >0 (success)

#ifndef NO_OPENSSL
private:
  Boolean setup(int socketNum);

private:
  class RTSPClient& fClient;
#endif
};

class ServerTLSState: public TLSState {
public:
  LIVE555_EXPORT ServerTLSState(UsageEnvironment& env);
  LIVE555_EXPORT virtual ~ServerTLSState();

  LIVE555_EXPORT void setCertificateAndPrivateKeyFileNames(char const* certFileName, char const* privKeyFileName);
  LIVE555_EXPORT void assignStateFrom(ServerTLSState const& from);

  LIVE555_EXPORT int accept(int socketNum); // returns: <0 (error), 0 (pending), >0 (success)

  Boolean tlsAcceptIsNeeded;

#ifndef NO_OPENSSL
private:
  LIVE555_EXPORT Boolean setup(int socketNum);

private:
  UsageEnvironment& fEnv;
  char const* fCertificateFileName;
  char const* fPrivateKeyFileName;
#endif
};

#endif
