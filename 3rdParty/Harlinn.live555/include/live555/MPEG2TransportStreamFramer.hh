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
// A filter that passes through (unchanged) chunks that contain an integral number
// of MPEG-2 Transport Stream packets, but returning (in "fDurationInMicroseconds")
// an updated estimate of the time gap between chunks.
// C++ header

#ifndef _MPEG2_TRANSPORT_STREAM_FRAMER_HH
#define _MPEG2_TRANSPORT_STREAM_FRAMER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

#ifndef _HASH_TABLE_HH
#include "HashTable.hh"
#endif

class MPEG2TransportStreamFramer: public FramedFilter {
public:
  LIVE555_EXPORT static MPEG2TransportStreamFramer*
  createNew(UsageEnvironment& env, FramedSource* inputSource);

  u_int64_t tsPacketCount() const { return fTSPacketCount; }

  void changeInputSource(FramedSource* newInputSource) { fInputSource = newInputSource; }

  LIVE555_EXPORT void clearPIDStatusTable();
  LIVE555_EXPORT void setNumTSPacketsToStream(unsigned long numTSRecordsToStream);
  LIVE555_EXPORT void setPCRLimit(float pcrLimit);

protected:
  LIVE555_EXPORT MPEG2TransportStreamFramer(UsageEnvironment& env, FramedSource* inputSource);
      // called only by createNew()
  LIVE555_EXPORT virtual ~MPEG2TransportStreamFramer();

private:
  // Redefined virtual functions:
  LIVE555_EXPORT virtual void doGetNextFrame();
  LIVE555_EXPORT virtual void doStopGettingFrames();

private:
  LIVE555_EXPORT static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  LIVE555_EXPORT void afterGettingFrame1(unsigned frameSize,
			  struct timeval presentationTime);

  LIVE555_EXPORT Boolean updateTSPacketDurationEstimate(unsigned char* pkt, double timeNow);

private:
  u_int64_t fTSPacketCount;
  double fTSPacketDurationEstimate;
  HashTable* fPIDStatusTable;
  u_int64_t fTSPCRCount;
  Boolean fLimitNumTSPacketsToStream;
  unsigned long fNumTSPacketsToStream; // used iff "fLimitNumTSPacketsToStream" is True
  Boolean fLimitTSPacketsToStreamByPCR;
  float fPCRLimit; // used iff "fLimitTSPacketsToStreamByPCR" is True
};

#endif
