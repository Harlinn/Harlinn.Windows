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
// Interleaving of MP3 ADUs
// C++ header

#ifndef _MP3_ADU_INTERLEAVING_HH
#define _MP3_ADU_INTERLEAVING_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

// A data structure used to represent an interleaving
#define MAX_CYCLE_SIZE 256
class Interleaving {
public:
  LIVE555_EXPORT 
  Interleaving(unsigned cycleSize, unsigned char const* cycleArray);
  LIVE555_EXPORT
  virtual ~Interleaving();

  unsigned cycleSize() const {return fCycleSize;}
  unsigned char lookupInverseCycle(unsigned char index) const {
    return fInverseCycle[index];
  }

private:
  unsigned fCycleSize;
  unsigned char fInverseCycle[MAX_CYCLE_SIZE];
};

// This class is used only as a base for the following two:

class MP3ADUinterleaverBase: public FramedFilter {
protected:
  LIVE555_EXPORT 
  MP3ADUinterleaverBase(UsageEnvironment& env,
			FramedSource* inputSource);
      // abstract base class
  LIVE555_EXPORT
  virtual ~MP3ADUinterleaverBase();

  LIVE555_EXPORT
  static FramedSource* getInputSource(UsageEnvironment& env,
				      char const* inputSourceName);
  LIVE555_EXPORT
  static void afterGettingFrame(void* clientData,
				unsigned numBytesRead,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  LIVE555_EXPORT
  virtual void afterGettingFrame(unsigned numBytesRead,
				 struct timeval presentationTime,
				 unsigned durationInMicroseconds) = 0;
};

// This class is used to convert an ADU sequence from non-interleaved
// to interleaved form:

class MP3ADUinterleaver: public MP3ADUinterleaverBase {
public:
  LIVE555_EXPORT 
  static MP3ADUinterleaver* createNew(UsageEnvironment& env,
				      Interleaving const& interleaving,
				      FramedSource* inputSource);

protected:
  LIVE555_EXPORT 
  MP3ADUinterleaver(UsageEnvironment& env,
		    Interleaving const& interleaving,
		    FramedSource* inputSource);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~MP3ADUinterleaver();

private:
  // redefined virtual functions:
  LIVE555_EXPORT 
  virtual void doGetNextFrame();
  LIVE555_EXPORT
  virtual void afterGettingFrame(unsigned numBytesRead,
				 struct timeval presentationTime,
				 unsigned durationInMicroseconds);

private:
  LIVE555_EXPORT 
  void releaseOutgoingFrame();

private:
  Interleaving const fInterleaving;
  class InterleavingFrames* fFrames;
  unsigned char fPositionOfNextIncomingFrame;
  unsigned fII, fICC;
};

// This class is used to convert an ADU sequence from interleaved
// to non-interleaved form:

class MP3ADUdeinterleaver: public MP3ADUinterleaverBase {
public:
  LIVE555_EXPORT 
  static MP3ADUdeinterleaver* createNew(UsageEnvironment& env,
					FramedSource* inputSource);

protected:
  LIVE555_EXPORT 
  MP3ADUdeinterleaver(UsageEnvironment& env,
		      FramedSource* inputSource);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~MP3ADUdeinterleaver();

private:
  // redefined virtual functions:
  LIVE555_EXPORT 
  virtual void doGetNextFrame();
  LIVE555_EXPORT
  virtual void afterGettingFrame(unsigned numBytesRead,
				 struct timeval presentationTime,
				 unsigned durationInMicroseconds);

private:
  LIVE555_EXPORT 
  void releaseOutgoingFrame();

private:
  class DeinterleavingFrames* fFrames;
  unsigned fIIlastSeen, fICClastSeen;
};

#endif

