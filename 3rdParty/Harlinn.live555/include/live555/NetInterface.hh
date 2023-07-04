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
// "groupsock"
// Copyright (c) 1996-2023 Live Networks, Inc.  All rights reserved.
// Network Interfaces
// C++ header

#ifndef _NET_INTERFACE_HH
#define _NET_INTERFACE_HH

#ifndef _NET_ADDRESS_HH
#include "NetAddress.hh"
#endif

class NetInterface {
public:
  LIVE555_EXPORT virtual ~NetInterface();

  LIVE555_EXPORT static UsageEnvironment* DefaultUsageEnvironment;
      // if non-NULL, used for each new interface

protected:
  LIVE555_EXPORT NetInterface(); // virtual base class
};

class Socket: public NetInterface {
public:
  LIVE555_EXPORT virtual ~Socket();
  LIVE555_EXPORT void reset(); // closes the socket, and sets "fSocketNum" to -1

  LIVE555_EXPORT virtual Boolean handleRead(unsigned char* buffer, unsigned bufferMaxSize,
			     unsigned& bytesRead,
			     struct sockaddr_storage& fromAddress) = 0;
      // Returns False on error; resultData == NULL if data ignored

  int socketNum() const { return fSocketNum; }

  Port port() const {
    return fPort;
  }

  UsageEnvironment& env() const { return fEnv; }

  LIVE555_EXPORT static int DebugLevel;

protected:
  LIVE555_EXPORT Socket(UsageEnvironment& env, Port port, int family); // virtual base class

  LIVE555_EXPORT Boolean changePort(Port newPort); // will also cause socketNum() to change

private:
  int fSocketNum;
  UsageEnvironment& fEnv;
  Port fPort;
  int fFamily;
};

LIVE555_EXPORT UsageEnvironment& operator<<(UsageEnvironment& s, const Socket& sock);

// A data structure for looking up a Socket by port:

class SocketLookupTable {
public:
  LIVE555_EXPORT virtual ~SocketLookupTable();

  LIVE555_EXPORT Socket* Fetch(UsageEnvironment& env, Port port, Boolean& isNew);
  // Creates a new Socket if none already exists
  LIVE555_EXPORT Boolean Remove(Socket const* sock);

protected:
  LIVE555_EXPORT SocketLookupTable(); // abstract base class
  LIVE555_EXPORT virtual Socket* CreateNew(UsageEnvironment& env, Port port) = 0;

private:
  HashTable* fTable;
};

// A data structure for counting traffic:

class NetInterfaceTrafficStats {
public:
  LIVE555_EXPORT NetInterfaceTrafficStats();

  LIVE555_EXPORT void countPacket(unsigned packetSize);

  float totNumPackets() const {return fTotNumPackets;}
  float totNumBytes() const {return fTotNumBytes;}

  LIVE555_EXPORT Boolean haveSeenTraffic() const;

private:
  float fTotNumPackets;
  float fTotNumBytes;
};

#endif
