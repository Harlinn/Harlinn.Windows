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
// Helper routines to implement 'group sockets'
// C++ header

#ifndef _GROUPSOCK_HELPER_HH
#define _GROUPSOCK_HELPER_HH

#ifndef _NET_ADDRESS_HH
#include "NetAddress.hh"
#endif

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

LIVE555_EXPORT int setupDatagramSocket(UsageEnvironment& env, Port port, int domain);
LIVE555_EXPORT int setupStreamSocket(UsageEnvironment& env, Port port, int domain,
		      Boolean makeNonBlocking = True, Boolean setKeepAlive = False);

LIVE555_EXPORT int readSocket(UsageEnvironment& env,
	       int socket, unsigned char* buffer, unsigned bufferSize,
	       struct sockaddr_storage& fromAddress /*set only if we're a datagram socket*/);

LIVE555_EXPORT Boolean writeSocket(UsageEnvironment& env,
		    int socket, struct sockaddr_storage const& addressAndPort,
		    u_int8_t ttlArg,
		    unsigned char* buffer, unsigned bufferSize);

LIVE555_EXPORT Boolean writeSocket(UsageEnvironment& env,
		    int socket, struct sockaddr_storage const& addressAndPort,
		    unsigned char* buffer, unsigned bufferSize);
    // An optimized version of "writeSocket" that omits the "setsockopt()" call to set the TTL.

LIVE555_EXPORT void ignoreSigPipeOnSocket(int socketNum);

LIVE555_EXPORT unsigned getSendBufferSize(UsageEnvironment& env, int socket);
LIVE555_EXPORT unsigned getReceiveBufferSize(UsageEnvironment& env, int socket);
LIVE555_EXPORT unsigned setSendBufferTo(UsageEnvironment& env,
			 int socket, unsigned requestedSize);
LIVE555_EXPORT unsigned setReceiveBufferTo(UsageEnvironment& env,
			    int socket, unsigned requestedSize);
LIVE555_EXPORT unsigned increaseSendBufferTo(UsageEnvironment& env,
			      int socket, unsigned requestedSize);
LIVE555_EXPORT unsigned increaseReceiveBufferTo(UsageEnvironment& env,
				 int socket, unsigned requestedSize);

LIVE555_EXPORT Boolean makeSocketNonBlocking(int sock);
LIVE555_EXPORT Boolean makeSocketBlocking(int sock, unsigned writeTimeoutInMilliseconds = 0);
  // A "writeTimeoutInMilliseconds" value of 0 means: Don't timeout
LIVE555_EXPORT Boolean setSocketKeepAlive(int sock);

LIVE555_EXPORT Boolean socketJoinGroup(UsageEnvironment& env, int socket,
			struct sockaddr_storage const& groupAddress);
LIVE555_EXPORT Boolean socketLeaveGroup(UsageEnvironment&, int socket,
			 struct sockaddr_storage const& groupAddress);

// source-specific multicast join/leave
LIVE555_EXPORT Boolean socketJoinGroupSSM(UsageEnvironment& env, int socket,
			   struct sockaddr_storage const& groupAddress,
			   struct sockaddr_storage const& sourceFilterAddr);
LIVE555_EXPORT Boolean socketLeaveGroupSSM(UsageEnvironment&, int socket,
			    struct sockaddr_storage const& groupAddress,
			    struct sockaddr_storage const& sourceFilterAddr);

LIVE555_EXPORT Boolean getSourcePort(UsageEnvironment& env, int socket, int domain, Port& port);

LIVE555_EXPORT ipv4AddressBits ourIPv4Address(UsageEnvironment& env); // in network order
LIVE555_EXPORT ipv6AddressBits const& ourIPv6Address(UsageEnvironment& env);

LIVE555_EXPORT Boolean weHaveAnIPv4Address(UsageEnvironment& env);
LIVE555_EXPORT Boolean weHaveAnIPv6Address(UsageEnvironment& env);
LIVE555_EXPORT Boolean weHaveAnIPAddress(UsageEnvironment& env);
  // returns True if we have either an IPv4 or an IPv6 address

// IPv4 addresses of our sending and receiving interfaces.  (By default, these
// are INADDR_ANY (i.e., 0), specifying the default interface.)
LIVE555_EXPORT extern ipv4AddressBits SendingInterfaceAddr;
LIVE555_EXPORT extern ipv4AddressBits ReceivingInterfaceAddr;
LIVE555_EXPORT extern in6_addr ReceivingInterfaceAddr6;

// Allocates a randomly-chosen IPv4 SSM (multicast) address:
LIVE555_EXPORT ipv4AddressBits chooseRandomIPv4SSMAddress(UsageEnvironment& env);

// Returns a simple "hh:mm:ss" string, for use in debugging output (e.g.)
LIVE555_EXPORT char const* timestampString();


#ifdef HAVE_SOCKADDR_LEN
#define SET_SOCKADDR_SIN_LEN(var) var.sin_len = sizeof var
#define SET_SOCKADDR_SIN6_LEN(var) var.sin6_len = sizeof var
#else
#define SET_SOCKADDR_SIN_LEN(var)
#define SET_SOCKADDR_SIN6_LEN(var)
#endif

#define MAKE_SOCKADDR_IN(var,adr,prt) /*adr,prt must be in network order*/\
    struct sockaddr_in var;\
    var.sin_family = AF_INET;\
    var.sin_addr.s_addr = (adr);\
    var.sin_port = (prt);\
    SET_SOCKADDR_SIN_LEN(var);
#define MAKE_SOCKADDR_IN6(var,adr,prt) /*adr,prt must be in network order*/\
    struct sockaddr_in6 var;\
    memset(&var, 0, sizeof var);\
    var.sin6_family = AF_INET6;\
    var.sin6_addr=adr;\
    var.sin6_port = (prt);\
    SET_SOCKADDR_SIN6_LEN(var);


// By default, we create sockets with the SO_REUSE_* flag set.
// If, instead, you want to create sockets without the SO_REUSE_* flags,
// Then enclose the creation code with:
//          {
//            NoReuse dummy;
//            ...
//          }
class NoReuse {
public:
  LIVE555_EXPORT NoReuse(UsageEnvironment& env);
  LIVE555_EXPORT ~NoReuse();

private:
  UsageEnvironment& fEnv;
};


// Define the "UsageEnvironment"-specific "groupsockPriv" structure:

struct _groupsockPriv { // There should be only one of these allocated
  HashTable* socketTable;
  int reuseFlag;
};
LIVE555_EXPORT _groupsockPriv* groupsockPriv(UsageEnvironment& env); // allocates it if necessary
LIVE555_EXPORT void reclaimGroupsockPriv(UsageEnvironment& env);


#if (defined(__WIN32__) || defined(_WIN32)) && !defined(__MINGW32__)
// For Windoze, we need to implement our own gettimeofday()
LIVE555_EXPORT extern int gettimeofday(struct timeval*, int*);
#else
#include <sys/time.h>
#endif

// The following are implemented in inet.c:
extern "C" LIVE555_EXPORT void our_srandom(int x);
extern "C" LIVE555_EXPORT long our_random();
extern "C" LIVE555_EXPORT u_int32_t our_random32(); // because "our_random()" returns a 31-bit number

#endif