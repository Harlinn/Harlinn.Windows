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
// Transcoder for ADUized MP3 frames
// C++ header

#ifndef _MP3_ADU_TRANSCODER_HH
#define _MP3_ADU_TRANSCODER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

class MP3ADUTranscoder: public FramedFilter {
public:
  LIVE555_EXPORT 
  static MP3ADUTranscoder* createNew(UsageEnvironment& env,
				  unsigned outBitrate /* in kbps */,
				  FramedSource* inputSource);

  unsigned outBitrate() const { return fOutBitrate; }
protected:
  LIVE555_EXPORT 
  MP3ADUTranscoder(UsageEnvironment& env,
		unsigned outBitrate /* in kbps */,
		FramedSource* inputSource);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~MP3ADUTranscoder();

private:
  // redefined virtual functions:
  LIVE555_EXPORT 
  virtual void doGetNextFrame();
  LIVE555_EXPORT
  virtual void getAttributes() const;

private:
  LIVE555_EXPORT 
  static void afterGettingFrame(void* clientData,
				unsigned numBytesRead, unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  LIVE555_EXPORT
  void afterGettingFrame1(unsigned numBytesRead, unsigned numTruncatedBytes,
			  struct timeval presentationTime,
			  unsigned durationInMicroseconds);

private:
  unsigned fOutBitrate; // in kbps
  unsigned fAvailableBytesForBackpointer;

  unsigned char* fOrigADU;
      // used to store incoming ADU prior to transcoding
};

#endif
