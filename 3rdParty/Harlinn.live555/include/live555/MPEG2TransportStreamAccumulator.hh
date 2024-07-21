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
// Collects a stream of incoming MPEG Transport Stream packets into
//  a chunk sufficiently large to send in a single outgoing (RTP or UDP) packet.
// C++ header

#ifndef _MPEG2_TRANSPORT_STREAM_ACCUMULATOR_HH
#define _MPEG2_TRANSPORT_STREAM_ACCUMULATOR_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

class MPEG2TransportStreamAccumulator: public FramedFilter {
public:
  LIVE555_EXPORT
  static MPEG2TransportStreamAccumulator* createNew(UsageEnvironment& env,
						    FramedSource* inputSource,
						    unsigned maxPacketSize = 1456);

protected:
  LIVE555_EXPORT
  MPEG2TransportStreamAccumulator(UsageEnvironment& env,
				  FramedSource* inputSource, unsigned maxPacketSize);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~MPEG2TransportStreamAccumulator();

private:
  // redefined virtual functions:
  LIVE555_EXPORT
  virtual void doGetNextFrame();

private:
  LIVE555_EXPORT
  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
                                struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  LIVE555_EXPORT
  void afterGettingFrame1(unsigned frameSize,
                          unsigned numTruncatedBytes,
                          struct timeval presentationTime,
                          unsigned durationInMicroseconds);

private:
  unsigned const fDesiredPacketSize;
  unsigned fNumBytesGathered;
};

#endif
