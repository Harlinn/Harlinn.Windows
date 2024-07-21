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
// Copyright (c) 1996-2024 Live Networks, Inc.  All rights reserved.
// A simple UDP sink (i.e., without RTP or other headers added); one frame per packet
// C++ header

#ifndef _BASIC_UDP_SINK_HH
#define _BASIC_UDP_SINK_HH

#ifndef _MEDIA_SINK_HH
#include "MediaSink.hh"
#endif
#ifndef _GROUPSOCK_HH
#include <Groupsock.hh>
#endif

class BasicUDPSink: public MediaSink {
public:
  LIVE555_EXPORT 
  static BasicUDPSink* createNew(UsageEnvironment& env, Groupsock* gs,
				  unsigned maxPayloadSize = 1450);
protected:
  LIVE555_EXPORT 
  BasicUDPSink(UsageEnvironment& env, Groupsock* gs, unsigned maxPayloadSize);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~BasicUDPSink();

private: // redefined virtual functions:
  LIVE555_EXPORT 
  virtual Boolean continuePlaying();

private:
  LIVE555_EXPORT 
  void continuePlaying1();

  LIVE555_EXPORT
  static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  LIVE555_EXPORT
  void afterGettingFrame1(unsigned frameSize, unsigned numTruncatedBytes,
			  unsigned durationInMicroseconds);
  LIVE555_EXPORT
  static void sendNext(void* firstArg);

private:
  Groupsock* fGS;
  unsigned fMaxPayloadSize;
  unsigned char* fOutputBuffer;
  struct timeval fNextSendTime;
};

#endif
