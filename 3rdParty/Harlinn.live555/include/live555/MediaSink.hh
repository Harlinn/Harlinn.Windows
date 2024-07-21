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
// Media Sinks
// C++ header

#ifndef _MEDIA_SINK_HH
#define _MEDIA_SINK_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

class MediaSink: public Medium {
public:
    LIVE555_EXPORT
  static Boolean lookupByName(UsageEnvironment& env, char const* sinkName,
			      MediaSink*& resultSink);

  typedef void (afterPlayingFunc)(void* clientData);
  LIVE555_EXPORT
  Boolean startPlaying(MediaSource& source,
		       afterPlayingFunc* afterFunc,
		       void* afterClientData);
  LIVE555_EXPORT
  virtual void stopPlaying();

  // Test for specific types of sink:
  LIVE555_EXPORT
  virtual Boolean isRTPSink() const;

  FramedSource* source() const {return fSource;}

protected:
  LIVE555_EXPORT 
  MediaSink(UsageEnvironment& env); // abstract base class
  LIVE555_EXPORT
  virtual ~MediaSink();

  LIVE555_EXPORT
  virtual Boolean sourceIsCompatibleWithUs(MediaSource& source);
      // called by startPlaying()
  virtual Boolean continuePlaying() = 0;
      // called by startPlaying()

  LIVE555_EXPORT
  static void onSourceClosure(void* clientData); // can be used in "getNextFrame()" calls
  LIVE555_EXPORT
  void onSourceClosure();
      // should be called (on ourselves) by continuePlaying() when it
      // discovers that the source we're playing from has closed.

  FramedSource* fSource;

private:
  // redefined virtual functions:
  LIVE555_EXPORT 
  virtual Boolean isSink() const;

private:
  // The following fields are used when we're being played:
  afterPlayingFunc* fAfterFunc;
  void* fAfterClientData;
};

// A data structure that a sink may use for an output packet:
class OutPacketBuffer {
public:
  LIVE555_EXPORT 
  OutPacketBuffer(unsigned preferredPacketSize, unsigned maxPacketSize,
		  unsigned maxBufferSize = 0);
      // if "maxBufferSize" is >0, use it - instead of "maxSize" to compute the buffer size
  LIVE555_EXPORT
  ~OutPacketBuffer();

  LIVE555_EXPORT static unsigned maxSize;
  static void increaseMaxSizeTo(unsigned newMaxSize) { if (newMaxSize > OutPacketBuffer::maxSize) OutPacketBuffer::maxSize = newMaxSize; }

  unsigned char* curPtr() const {return &fBuf[fPacketStart + fCurOffset];}
  unsigned totalBytesAvailable() const {
    return fLimit - (fPacketStart + fCurOffset);
  }
  unsigned totalBufferSize() const { return fLimit; }
  unsigned char* packet() const {return &fBuf[fPacketStart];}
  unsigned curPacketSize() const {return fCurOffset;}

  void increment(unsigned numBytes) {fCurOffset += numBytes;}

  LIVE555_EXPORT
  void enqueue(unsigned char const* from, unsigned numBytes);
  LIVE555_EXPORT
  void enqueueWord(u_int32_t word);
  LIVE555_EXPORT
  void insert(unsigned char const* from, unsigned numBytes, unsigned toPosition);
  LIVE555_EXPORT
  void insertWord(u_int32_t word, unsigned toPosition);
  LIVE555_EXPORT
  void extract(unsigned char* to, unsigned numBytes, unsigned fromPosition);
  LIVE555_EXPORT
  u_int32_t extractWord(unsigned fromPosition);

  LIVE555_EXPORT
  void skipBytes(unsigned numBytes);

  Boolean isPreferredSize() const {return fCurOffset >= fPreferred;}
  Boolean wouldOverflow(unsigned numBytes) const {
    return (fCurOffset+numBytes) > fMax;
  }
  unsigned numOverflowBytes(unsigned numBytes) const {
    return (fCurOffset+numBytes) - fMax;
  }
  Boolean isTooBigForAPacket(unsigned numBytes) const {
    return numBytes > fMax;
  }

  LIVE555_EXPORT
  void setOverflowData(unsigned overflowDataOffset,
		       unsigned overflowDataSize,
		       struct timeval const& presentationTime,
		       unsigned durationInMicroseconds);
  unsigned overflowDataSize() const {return fOverflowDataSize;}
  struct timeval overflowPresentationTime() const {return fOverflowPresentationTime;}
  unsigned overflowDurationInMicroseconds() const {return fOverflowDurationInMicroseconds;}
  Boolean haveOverflowData() const {return fOverflowDataSize > 0;}
  LIVE555_EXPORT
  void useOverflowData();

  LIVE555_EXPORT
  void adjustPacketStart(unsigned numBytes);
  LIVE555_EXPORT
  void resetPacketStart();
  void resetOffset() { fCurOffset = 0; }
  void resetOverflowData() { fOverflowDataOffset = fOverflowDataSize = 0; }

private:
  unsigned fPacketStart, fCurOffset, fPreferred, fMax, fLimit;
  unsigned char* fBuf;

  unsigned fOverflowDataOffset, fOverflowDataSize;
  struct timeval fOverflowPresentationTime;
  unsigned fOverflowDurationInMicroseconds;
};

#endif
