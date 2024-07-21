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
// A filter that breaks up an MPEG video elementary stream into
//   headers and frames
// C++ header

#ifndef _MPEG_VIDEO_STREAM_FRAMER_HH
#define _MPEG_VIDEO_STREAM_FRAMER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

class TimeCode {
public:
  LIVE555_EXPORT 
  TimeCode();
  LIVE555_EXPORT
  virtual ~TimeCode();

  LIVE555_EXPORT
  int operator==(TimeCode const& arg2) const;
  unsigned days, hours, minutes, seconds, pictures;
};

class MPEGVideoStreamFramer: public FramedFilter {
public:
  Boolean& pictureEndMarker() { return fPictureEndMarker; }
      // a hack for implementing the RTP 'M' bit

  LIVE555_EXPORT
  void flushInput(); // called if there is a discontinuity (seeking) in the input

protected:
  LIVE555_EXPORT 
  MPEGVideoStreamFramer(UsageEnvironment& env, FramedSource* inputSource);
      // we're an abstract base class
  LIVE555_EXPORT
  virtual ~MPEGVideoStreamFramer();

  LIVE555_EXPORT
  void computePresentationTime(unsigned numAdditionalPictures);
      // sets "fPresentationTime"
  LIVE555_EXPORT
  void setTimeCode(unsigned hours, unsigned minutes, unsigned seconds,
		   unsigned pictures, unsigned picturesSinceLastGOP);

protected: // redefined virtual functions
  LIVE555_EXPORT 
  virtual void doGetNextFrame();
  LIVE555_EXPORT
  virtual void doStopGettingFrames();

private:
  LIVE555_EXPORT 
  void reset();

  LIVE555_EXPORT
  static void continueReadProcessing(void* clientData,
				     unsigned char* ptr, unsigned size,
				     struct timeval presentationTime);
  LIVE555_EXPORT
  void continueReadProcessing();

protected:
  double fFrameRate; // Note: For MPEG-4, this is really a 'tick rate'
  unsigned fPictureCount; // hack used to implement doGetNextFrame()
  Boolean fPictureEndMarker;
  struct timeval fPresentationTimeBase;

  // parsing state
  class MPEGVideoStreamParser* fParser;
  friend class MPEGVideoStreamParser; // hack

private:
  TimeCode fCurGOPTimeCode, fPrevGOPTimeCode;
  unsigned fPicturesAdjustment;
  double fPictureTimeBase;
  unsigned fTcSecsBase;
  Boolean fHaveSeenFirstTimeCode;
};

#endif
