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
// RTP source for a common kind of payload format: Those which pack multiple,
// complete codec frames (as many as possible) into each RTP packet.
// C++ header

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#define _MULTI_FRAMED_RTP_SOURCE_HH

#ifndef _RTP_SOURCE_HH
#include "RTPSource.hh"
#endif

class BufferedPacket; // forward
class BufferedPacketFactory; // forward

class MultiFramedRTPSource: public RTPSource {
protected:
  LIVE555_EXPORT MultiFramedRTPSource(UsageEnvironment& env, Groupsock* RTPgs,
		       unsigned char rtpPayloadFormat,
		       unsigned rtpTimestampFrequency,
		       BufferedPacketFactory* packetFactory = NULL);
      // virtual base class
  LIVE555_EXPORT virtual ~MultiFramedRTPSource();

  LIVE555_EXPORT virtual Boolean processSpecialHeader(BufferedPacket* packet,
				       unsigned& resultSpecialHeaderSize);
      // Subclasses redefine this to handle any special, payload format
      // specific header that follows the RTP header.

  LIVE555_EXPORT virtual Boolean packetIsUsableInJitterCalculation(unsigned char* packet,
						    unsigned packetSize);
      // The default implementation returns True, but this can be redefined

protected:
  Boolean fCurrentPacketBeginsFrame;
  Boolean fCurrentPacketCompletesFrame;

protected:
  // redefined virtual functions:
  LIVE555_EXPORT virtual void doGetNextFrame();
  LIVE555_EXPORT virtual void doStopGettingFrames();

private:
  // redefined virtual functions:
  LIVE555_EXPORT virtual void setPacketReorderingThresholdTime(unsigned uSeconds);

private:
  LIVE555_EXPORT void reset();
  LIVE555_EXPORT void doGetNextFrame1();

  LIVE555_EXPORT static void networkReadHandler(MultiFramedRTPSource* source, int /*mask*/);
  LIVE555_EXPORT void networkReadHandler1();

  Boolean fAreDoingNetworkReads;
  BufferedPacket* fPacketReadInProgress;
  Boolean fNeedDelivery;
  Boolean fPacketLossInFragmentedFrame;
  unsigned char* fSavedTo;
  unsigned fSavedMaxSize;

  // A buffer to (optionally) hold incoming pkts that have been reorderered
  class ReorderingPacketBuffer* fReorderingBuffer;
};


// A 'packet data' class that's used to implement the above.
// Note that this can be subclassed - if desired - to redefine
// "nextEnclosedFrameParameters()".

class BufferedPacket {
public:
  LIVE555_EXPORT BufferedPacket();
  LIVE555_EXPORT virtual ~BufferedPacket();

  Boolean hasUsableData() const { return fTail > fHead; }
  unsigned useCount() const { return fUseCount; }

  LIVE555_EXPORT Boolean fillInData(RTPInterface& rtpInterface, struct sockaddr_storage& fromAddress, Boolean& packetReadWasIncomplete);
  LIVE555_EXPORT void assignMiscParams(unsigned short rtpSeqNo, unsigned rtpTimestamp,
			struct timeval presentationTime,
			Boolean hasBeenSyncedUsingRTCP,
			Boolean rtpMarkerBit, struct timeval timeReceived);
  LIVE555_EXPORT void skip(unsigned numBytes); // used to skip over an initial header
  LIVE555_EXPORT void removePadding(unsigned numBytes); // used to remove trailing bytes
  LIVE555_EXPORT void appendData(unsigned char* newData, unsigned numBytes);
  LIVE555_EXPORT void use(unsigned char* to, unsigned toSize,
	   unsigned& bytesUsed, unsigned& bytesTruncated,
	   unsigned short& rtpSeqNo, unsigned& rtpTimestamp,
	   struct timeval& presentationTime,
	   Boolean& hasBeenSyncedUsingRTCP, Boolean& rtpMarkerBit);

  BufferedPacket*& nextPacket() { return fNextPacket; }

  unsigned short rtpSeqNo() const { return fRTPSeqNo; }
  struct timeval const& timeReceived() const { return fTimeReceived; }

  unsigned char* data() const { return &fBuf[fHead]; }
  unsigned dataSize() const { return fTail-fHead; }
  Boolean rtpMarkerBit() const { return fRTPMarkerBit; }
  Boolean& isFirstPacket() { return fIsFirstPacket; }
  unsigned bytesAvailable() const { return fPacketSize - fTail; }

protected:
  LIVE555_EXPORT virtual void reset();
  LIVE555_EXPORT virtual unsigned nextEnclosedFrameSize(unsigned char*& framePtr,
					 unsigned dataSize);
      // The above function has been deprecated.  Instead, new subclasses should use:
  LIVE555_EXPORT virtual void getNextEnclosedFrameParameters(unsigned char*& framePtr,
					      unsigned dataSize,
					      unsigned& frameSize,
					      unsigned& frameDurationInMicroseconds);

  unsigned fPacketSize;
  unsigned char* fBuf;
  unsigned fHead;
  unsigned fTail;

private:
  BufferedPacket* fNextPacket; // used to link together packets

  unsigned fUseCount;
  unsigned short fRTPSeqNo;
  unsigned fRTPTimestamp;
  struct timeval fPresentationTime; // corresponding to "fRTPTimestamp"
  Boolean fHasBeenSyncedUsingRTCP;
  Boolean fRTPMarkerBit;
  Boolean fIsFirstPacket;
  struct timeval fTimeReceived;
};

// A 'factory' class for creating "BufferedPacket" objects.
// If you want to subclass "BufferedPacket", then you'll also
// want to subclass this, to redefine createNewPacket()

class BufferedPacketFactory {
public:
  LIVE555_EXPORT BufferedPacketFactory();
  LIVE555_EXPORT virtual ~BufferedPacketFactory();

  LIVE555_EXPORT virtual BufferedPacket* createNewPacket(MultiFramedRTPSource* ourSource);
};

#endif
