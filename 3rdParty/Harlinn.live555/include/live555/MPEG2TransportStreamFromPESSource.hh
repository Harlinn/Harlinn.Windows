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
// A filter for converting a stream of MPEG PES packets to a MPEG-2 Transport Stream
// C++ header

#ifndef _MPEG2_TRANSPORT_STREAM_FROM_PES_SOURCE_HH
#define _MPEG2_TRANSPORT_STREAM_FROM_PES_SOURCE_HH

#ifndef _MPEG2_TRANSPORT_STREAM_MULTIPLEXOR_HH
#include "MPEG2TransportStreamMultiplexor.hh"
#endif
#ifndef _MPEG_1OR2_DEMUXED_ELEMENTARY_STREAM_HH
#include "MPEG1or2DemuxedElementaryStream.hh"
#endif

class MPEG2TransportStreamFromPESSource: public MPEG2TransportStreamMultiplexor {
public:
  LIVE555_EXPORT 
  static MPEG2TransportStreamFromPESSource*
  createNew(UsageEnvironment& env, MPEG1or2DemuxedElementaryStream* inputSource);

protected:
  LIVE555_EXPORT 
  MPEG2TransportStreamFromPESSource(UsageEnvironment& env,
				    MPEG1or2DemuxedElementaryStream* inputSource);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~MPEG2TransportStreamFromPESSource();

private:
  // Redefined virtual functions:
  LIVE555_EXPORT 
  virtual void doStopGettingFrames();
  LIVE555_EXPORT
  virtual void awaitNewBuffer(unsigned char* oldBuffer);

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
  MPEG1or2DemuxedElementaryStream* fInputSource;
  unsigned char* fInputBuffer;
};

#endif
