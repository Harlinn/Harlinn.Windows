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
// Network Addresses
// C++ header

#ifndef _NET_ADDRESS_HH
#define _NET_ADDRESS_HH

#ifndef _HASH_TABLE_HH
#include "HashTable.hh"
#endif

#ifndef _NET_COMMON_H
#include "NetCommon.h"
#endif

#ifndef _USAGE_ENVIRONMENT_HH
#include "UsageEnvironment.hh"
#endif

// Definition of a type representing a low-level network address.
    // Note that the type "netAddressBits" is no longer defined; use "ipv4AddressBits" instead.
typedef u_int32_t ipv4AddressBits;
typedef u_int8_t ipv6AddressBits[16]; // 128 bits

class NetAddress {
public:
  LIVE555_EXPORT NetAddress(u_int8_t const* data,
	     unsigned length = 4 /* default: 32 bits (for IPv4); use 16 (128 bits) for IPv6 */);
  LIVE555_EXPORT NetAddress(unsigned length = 4); // sets address data to all-zeros
  LIVE555_EXPORT NetAddress(NetAddress const& orig);
  LIVE555_EXPORT NetAddress& operator=(NetAddress const& rightSide);
  LIVE555_EXPORT virtual ~NetAddress();
  
  unsigned length() const { return fLength; }
  u_int8_t const* data() const // always in network byte order
  { return fData; }
  
private:
  LIVE555_EXPORT void assign(u_int8_t const* data, unsigned length);
  LIVE555_EXPORT void clean();
  
  unsigned fLength;
  u_int8_t* fData;
};

LIVE555_EXPORT struct sockaddr_storage const& nullAddress(int addressFamily = AF_INET);
LIVE555_EXPORT Boolean addressIsNull(sockaddr_storage const& address);

LIVE555_EXPORT SOCKLEN_T addressSize(sockaddr_storage const& address);

LIVE555_EXPORT void copyAddress(struct sockaddr_storage& to, NetAddress const* from);

LIVE555_EXPORT Boolean operator==(struct sockaddr_storage const& left, struct sockaddr_storage const& right);
    // compares the family and address parts only; not the port number or anything else

class NetAddressList {
public:
  LIVE555_EXPORT NetAddressList(char const* hostname, int addressFamily = AF_UNSPEC);
  LIVE555_EXPORT NetAddressList(NetAddressList const& orig);
  LIVE555_EXPORT NetAddressList& operator=(NetAddressList const& rightSide);
  LIVE555_EXPORT virtual ~NetAddressList();
  
  unsigned numAddresses() const { return fNumAddresses; }
  
  LIVE555_EXPORT NetAddress const* firstAddress() const;
  
  // Used to iterate through the addresses in a list:
  class Iterator {
  public:
    LIVE555_EXPORT Iterator(NetAddressList const& addressList);
    LIVE555_EXPORT NetAddress const* nextAddress(); // NULL iff none
  private:
    NetAddressList const& fAddressList;
    unsigned fNextIndex;
  };
  
private:
  LIVE555_EXPORT void assign(unsigned numAddresses, NetAddress** addressArray);
  LIVE555_EXPORT void clean();
  
  friend class Iterator;
  unsigned fNumAddresses;
  NetAddress** fAddressArray;
};

typedef u_int16_t portNumBits;

class Port {
public:
  LIVE555_EXPORT Port(portNumBits num /* in host byte order */);
  
  portNumBits num() const { return fPortNum; } // in network byte order
  
private:
  portNumBits fPortNum; // stored in network byte order
#ifdef IRIX
  portNumBits filler; // hack to overcome a bug in IRIX C++ compiler
#endif
};

LIVE555_EXPORT UsageEnvironment& operator<<(UsageEnvironment& s, const Port& p);


// A generic table for looking up objects by (address1, address2, port)
class AddressPortLookupTable {
public:
  LIVE555_EXPORT AddressPortLookupTable();
  LIVE555_EXPORT virtual ~AddressPortLookupTable();
  
  LIVE555_EXPORT void* Add(struct sockaddr_storage const& address1,
	    struct sockaddr_storage const& address2,
	    Port port,
	    void* value);
      // Returns the old value if different, otherwise 0
  void* Add(struct sockaddr_storage const& address1,
	    Port port,
	    void* value) {
    return Add(address1, nullAddress(), port, value);
  }

  LIVE555_EXPORT Boolean Remove(struct sockaddr_storage const& address1,
		 struct sockaddr_storage const& address2,
		 Port port);
  Boolean Remove(struct sockaddr_storage const& address1,
		 Port port) {
    return Remove(address1, nullAddress(), port);
  }

  LIVE555_EXPORT void* Lookup(struct sockaddr_storage const& address1,
	       struct sockaddr_storage const& address2,
	       Port port);
      // Returns 0 if not found
  void* Lookup(struct sockaddr_storage const& address1,
	       Port port) {
    return Lookup(address1, nullAddress(), port);
  }

  void* RemoveNext() { return fTable->RemoveNext(); }

  // Used to iterate through the entries in the table
  class Iterator {
  public:
    LIVE555_EXPORT Iterator(AddressPortLookupTable& table);
    LIVE555_EXPORT virtual ~Iterator();
    
    LIVE555_EXPORT void* next(); // NULL iff none
    
  private:
    HashTable::Iterator* fIter;
  };
  
private:
  friend class Iterator;
  HashTable* fTable;
};


LIVE555_EXPORT Boolean IsMulticastAddress(struct sockaddr_storage const& address);


// A mechanism for displaying an IP (v4 or v6) address in ASCII.
// (This encapsulates the "inet_ntop()" function.)
class AddressString {
public:
  // IPv4 input:
  LIVE555_EXPORT AddressString(struct sockaddr_in const& addr);
  LIVE555_EXPORT AddressString(struct in_addr const& addr);
  LIVE555_EXPORT AddressString(ipv4AddressBits const& addr); // "addr" is assumed to be in network byte order

  // IPv6 input:
  LIVE555_EXPORT AddressString(struct sockaddr_in6 const& addr);
  LIVE555_EXPORT AddressString(struct in6_addr const& addr);
  LIVE555_EXPORT AddressString(ipv6AddressBits const& addr);

  // IPv4 or IPv6 input:
  LIVE555_EXPORT AddressString(struct sockaddr_storage const& addr);

  LIVE555_EXPORT virtual ~AddressString();

  char const* val() const { return fVal; }

private:
  LIVE555_EXPORT void init(ipv4AddressBits const& addr); // used to implement the IPv4 constructors
  LIVE555_EXPORT void init(ipv6AddressBits const& addr); // used to implement the IPv6 constructors

private:
  char* fVal; // The result ASCII string: allocated by the constructor; deleted by the destructor
};

LIVE555_EXPORT portNumBits portNum(struct sockaddr_storage const& address);
LIVE555_EXPORT void setPortNum(struct sockaddr_storage& address, portNumBits portNum/*in network order*/);

#endif
