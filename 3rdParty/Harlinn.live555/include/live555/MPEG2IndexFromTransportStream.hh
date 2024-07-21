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
// A filter that produces a sequence of I-frame indices from a MPEG-2 Transport Stream
// C++ header

#ifndef _MPEG2_IFRAME_INDEX_FROM_TRANSPORT_STREAM_HH
#define _MPEG2_IFRAME_INDEX_FROM_TRANSPORT_STREAM_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

#ifndef TRANSPORT_PACKET_SIZE
#define TRANSPORT_PACKET_SIZE 188
#endif

#ifndef MAX_PES_PACKET_SIZE
#define MAX_PES_PACKET_SIZE 65536
#endif

class IndexRecord; // forward

class MPEG2IFrameIndexFromTransportStream: public FramedFilter {
public:
  LIVE555_EXPORT
  static MPEG2IFrameIndexFromTransportStream*
  createNew(UsageEnvironment& env, FramedSource* inputSource);

protected:
  LIVE555_EXPORT
  MPEG2IFrameIndexFromTransportStream(UsageEnvironment& env,
				      FramedSource* inputSource);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~MPEG2IFrameIndexFromTransportStream();

private:
  // Redefined virtual functions:
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

  LIVE555_EXPORT
  static void handleInputClosure(void* clientData);
  LIVE555_EXPORT
  void handleInputClosure1();

  LIVE555_EXPORT
  void analyzePAT(unsigned char* pkt, unsigned size);
  LIVE555_EXPORT
  void analyzePMT(unsigned char* pkt, unsigned size);

  LIVE555_EXPORT
  Boolean deliverIndexRecord();
  LIVE555_EXPORT
  Boolean parseFrame();
  LIVE555_EXPORT
  Boolean parseToNextCode(unsigned char& nextCode);
  LIVE555_EXPORT
  void compactParseBuffer();
  LIVE555_EXPORT
  void addToTail(IndexRecord* newIndexRecord);

private:
  Boolean fIsH264; // True iff the video is H.264 (encapsulated in a Transport Stream)
  Boolean fIsH265; // True iff the video is H.265 (encapsulated in a Transport Stream)
  unsigned long fInputTransportPacketCounter;
  unsigned fClosureNumber;
  u_int8_t fLastContinuityCounter;
  float fFirstPCR, fLastPCR;
  Boolean fHaveSeenFirstPCR;
  u_int16_t fPMT_PID, fVideo_PID;
      // Note: We assume: 1 program per Transport Stream; 1 video stream per program
  unsigned char fInputBuffer[TRANSPORT_PACKET_SIZE];
  unsigned char* fParseBuffer;
  unsigned fParseBufferSize;
  unsigned fParseBufferFrameStart;
  unsigned fParseBufferParseEnd;
  unsigned fParseBufferDataEnd;
  IndexRecord* fHeadIndexRecord;
  IndexRecord* fTailIndexRecord;
};

#endif
