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
// Copyright (c) 1996-2024 Live Networks, Inc.  All rights reserved.// A filter that converts a MPEG Transport Stream file - with corresponding index file
// - to a corresponding Video Elementary Stream.  It also uses a "scale" parameter
// to implement 'trick mode' (fast forward or reverse play, using I-frames) on
// the video stream.
// C++ header

#ifndef _MPEG2_TRANSPORT_STREAM_TRICK_MODE_FILTER_HH
#define _MPEG2_TRANSPORT_STREAM_TRICK_MODE_FILTER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

#ifndef _MPEG2_TRANSPORT_STREAM_INDEX_FILE_HH
#include "MPEG2TransportStreamIndexFile.hh"
#endif

#ifndef TRANSPORT_PACKET_SIZE
#define TRANSPORT_PACKET_SIZE 188
#endif

class MPEG2TransportStreamTrickModeFilter: public FramedFilter {
public:
  LIVE555_EXPORT 
  static MPEG2TransportStreamTrickModeFilter*
  createNew(UsageEnvironment& env, FramedSource* inputSource,
	    MPEG2TransportStreamIndexFile* indexFile, int scale);

  LIVE555_EXPORT
  Boolean seekTo(unsigned long tsPacketNumber, unsigned long indexRecordNumber);

  unsigned long nextIndexRecordNum() const { return fNextIndexRecordNum; }

  void forgetInputSource() { fInputSource = NULL; }
      // this lets us delete this without also deleting the input Transport Stream

protected:
  LIVE555_EXPORT 
  MPEG2TransportStreamTrickModeFilter(UsageEnvironment& env, FramedSource* inputSource,
				      MPEG2TransportStreamIndexFile* indexFile, int scale);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~MPEG2TransportStreamTrickModeFilter();

private:
  // Redefined virtual functions:
  LIVE555_EXPORT 
  virtual void doGetNextFrame();
  LIVE555_EXPORT
  virtual void doStopGettingFrames();

private:
  LIVE555_EXPORT 
  void attemptDeliveryToClient();
  LIVE555_EXPORT
  void seekToTransportPacket(unsigned long tsPacketNum);
  LIVE555_EXPORT
  void readTransportPacket(unsigned long tsPacketNum); // asynchronously

  LIVE555_EXPORT
  static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  LIVE555_EXPORT
  void afterGettingFrame1(unsigned frameSize);

  LIVE555_EXPORT
  static void onSourceClosure(void* clientData);
  LIVE555_EXPORT
  void onSourceClosure1();

private:
  Boolean fHaveStarted;
  MPEG2TransportStreamIndexFile* fIndexFile;
  int fScale; // absolute value
  int fDirection; // 1 => forward; -1 => reverse
  enum {
    SKIPPING_FRAME,
    DELIVERING_SAVED_FRAME,
    SAVING_AND_DELIVERING_FRAME
  } fState;
  unsigned fFrameCount;
  unsigned long fNextIndexRecordNum; // next to be read from the index file
  unsigned long fNextTSPacketNum; // next to be read from the transport stream file
  unsigned char fInputBuffer[TRANSPORT_PACKET_SIZE];
  unsigned long fCurrentTSPacketNum; // corresponding to data currently in the buffer
  unsigned long fDesiredTSPacketNum;
  u_int8_t fDesiredDataOffset, fDesiredDataSize;
  float fDesiredDataPCR, fFirstPCR;
  unsigned long fSavedFrameIndexRecordStart;
  unsigned long fSavedSequentialIndexRecordNum;
  Boolean fUseSavedFrameNextTime;
};

#endif
