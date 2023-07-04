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
// RTP sink for a common kind of payload format: Those which pack multiple,
// complete codec frames (as many as possible) into each RTP packet.
// C++ header

#ifndef _MULTI_FRAMED_RTP_SINK_HH
#define _MULTI_FRAMED_RTP_SINK_HH

#ifndef _RTP_SINK_HH
#include "RTPSink.hh"
#endif

class MultiFramedRTPSink: public RTPSink {
public:
  LIVE555_EXPORT void setPacketSizes(unsigned preferredPacketSize, unsigned maxPacketSize);

  typedef void (__cdecl onSendErrorFunc)(void* clientData);
  void setOnSendErrorFunc(onSendErrorFunc* onSendErrorFunc, void* onSendErrorFuncData) {
    // Can be used to set a callback function to be called if there's an error sending RTP packets on our socket.
    fOnSendErrorFunc = onSendErrorFunc;
    fOnSendErrorData = onSendErrorFuncData;
  }

protected:
  LIVE555_EXPORT MultiFramedRTPSink(UsageEnvironment& env,
		     Groupsock* rtpgs, unsigned char rtpPayloadType,
		     unsigned rtpTimestampFrequency,
		     char const* rtpPayloadFormatName,
		     unsigned numChannels = 1);
	// we're a virtual base class

  LIVE555_EXPORT virtual ~MultiFramedRTPSink();

  LIVE555_EXPORT virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
				      unsigned char* frameStart,
				      unsigned numBytesInFrame,
				      struct timeval framePresentationTime,
				      unsigned numRemainingBytes);
      // perform any processing specific to the particular payload format
  LIVE555_EXPORT virtual Boolean allowFragmentationAfterStart() const;
      // whether a frame can be fragmented if other frame(s) appear earlier
      // in the packet (by default: False)
  LIVE555_EXPORT virtual Boolean allowOtherFramesAfterLastFragment() const;
      // whether other frames can be packed into a packet following the
      // final fragment of a previous, fragmented frame (by default: False)
  LIVE555_EXPORT virtual Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart,
						 unsigned numBytesInFrame) const;
      // whether this frame can appear in position >1 in a pkt (default: True)
  LIVE555_EXPORT virtual unsigned specialHeaderSize() const;
      // returns the size of any special header used (following the RTP header) (default: 0)
  LIVE555_EXPORT virtual unsigned frameSpecificHeaderSize() const;
      // returns the size of any frame-specific header used (before each frame
      // within the packet) (default: 0)
  LIVE555_EXPORT virtual unsigned computeOverflowForNewFrame(unsigned newFrameSize) const;
      // returns the number of overflow bytes that would be produced by adding a new
      // frame of size "newFrameSize" to the current RTP packet.
      // (By default, this just calls "numOverflowBytes()", but subclasses can redefine
      // this to (e.g.) impose a granularity upon RTP payload fragments.)

  // Functions that might be called by doSpecialFrameHandling(), or other subclass virtual functions:
  Boolean isFirstPacket() const { return fIsFirstPacket; }
  Boolean isFirstFrameInPacket() const { return fNumFramesUsedSoFar == 0; }
  unsigned curFragmentationOffset() const { return fCurFragmentationOffset; }
  LIVE555_EXPORT void setMarkerBit();
  LIVE555_EXPORT void setTimestamp(struct timeval framePresentationTime);
  LIVE555_EXPORT void setSpecialHeaderWord(unsigned word, /* 32 bits, in host order */
			    unsigned wordPosition = 0);
  LIVE555_EXPORT void setSpecialHeaderBytes(unsigned char const* bytes, unsigned numBytes,
			     unsigned bytePosition = 0);
  LIVE555_EXPORT void setFrameSpecificHeaderWord(unsigned word, /* 32 bits, in host order */
				  unsigned wordPosition = 0);
  LIVE555_EXPORT void setFrameSpecificHeaderBytes(unsigned char const* bytes, unsigned numBytes,
				   unsigned bytePosition = 0);
  LIVE555_EXPORT void setFramePadding(unsigned numPaddingBytes);
  unsigned numFramesUsedSoFar() const { return fNumFramesUsedSoFar; }
  unsigned ourMaxPacketSize() const { return fOurMaxPacketSize; }

public: // redefined virtual functions:
  LIVE555_EXPORT virtual void stopPlaying();

protected: // redefined virtual functions:
  LIVE555_EXPORT virtual Boolean continuePlaying();

private:
  LIVE555_EXPORT void buildAndSendPacket(Boolean isFirstPacket);
  LIVE555_EXPORT void packFrame();
  LIVE555_EXPORT void sendPacketIfNecessary();
  LIVE555_EXPORT static void sendNext(void* firstArg);
  LIVE555_EXPORT friend void sendNext(void*);

  LIVE555_EXPORT static void afterGettingFrame(void* clientData,
				unsigned numBytesRead, unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  LIVE555_EXPORT void afterGettingFrame1(unsigned numBytesRead, unsigned numTruncatedBytes,
			  struct timeval presentationTime,
			  unsigned durationInMicroseconds);
  LIVE555_EXPORT Boolean isTooBigForAPacket(unsigned numBytes) const;

  LIVE555_EXPORT static void ourHandleClosure(void* clientData);

private:
  OutPacketBuffer* fOutBuf;

  Boolean fNoFramesLeft;
  unsigned fNumFramesUsedSoFar;
  unsigned fCurFragmentationOffset;
  Boolean fPreviousFrameEndedFragmentation;

  Boolean fIsFirstPacket;
  struct timeval fNextSendTime;
  unsigned fTimestampPosition;
  unsigned fSpecialHeaderPosition;
  unsigned fSpecialHeaderSize; // size in bytes of any special header used
  unsigned fCurFrameSpecificHeaderPosition;
  unsigned fCurFrameSpecificHeaderSize; // size in bytes of cur frame-specific header
  unsigned fTotalFrameSpecificHeaderSizes; // size of all frame-specific hdrs in pkt
  unsigned fOurMaxPacketSize;

  onSendErrorFunc* fOnSendErrorFunc;
  void* fOnSendErrorData;
};

#endif
