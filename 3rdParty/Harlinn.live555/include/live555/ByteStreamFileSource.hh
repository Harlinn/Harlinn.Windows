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
// A file source that is a plain byte stream (rather than frames)
// C++ header

#ifndef _BYTE_STREAM_FILE_SOURCE_HH
#define _BYTE_STREAM_FILE_SOURCE_HH

#ifndef _FRAMED_FILE_SOURCE_HH
#include "FramedFileSource.hh"
#endif

class ByteStreamFileSource: public FramedFileSource {
public:
  LIVE555_EXPORT static ByteStreamFileSource* createNew(UsageEnvironment& env,
					 char const* fileName,
					 unsigned preferredFrameSize = 0,
					 unsigned playTimePerFrame = 0);
  // "preferredFrameSize" == 0 means 'no preference'
  // "playTimePerFrame" is in microseconds

  LIVE555_EXPORT static ByteStreamFileSource* createNew(UsageEnvironment& env,
					 FILE* fid,
					 unsigned preferredFrameSize = 0,
					 unsigned playTimePerFrame = 0);
      // an alternative version of "createNew()" that's used if you already have
      // an open file.

  LIVE555_EXPORT u_int64_t fileSize() const { return fFileSize; }
      // 0 means zero-length, unbounded, or unknown

  LIVE555_EXPORT void seekToByteAbsolute(u_int64_t byteNumber, u_int64_t numBytesToStream = 0);
    // if "numBytesToStream" is >0, then we limit the stream to that number of bytes, before treating it as EOF
  LIVE555_EXPORT void seekToByteRelative(int64_t offset, u_int64_t numBytesToStream = 0);
  LIVE555_EXPORT void seekToEnd(); // to force EOF handling on the next read

protected:
  LIVE555_EXPORT ByteStreamFileSource(UsageEnvironment& env,
		       FILE* fid,
		       unsigned preferredFrameSize,
		       unsigned playTimePerFrame);
	// called only by createNew()

  LIVE555_EXPORT virtual ~ByteStreamFileSource();

  LIVE555_EXPORT static void fileReadableHandler(ByteStreamFileSource* source, int mask);
  LIVE555_EXPORT void doReadFromFile();

private:
  // redefined virtual functions:
  LIVE555_EXPORT virtual void doGetNextFrame();
  LIVE555_EXPORT virtual void doStopGettingFrames();

protected:
  u_int64_t fFileSize;

private:
  unsigned fPreferredFrameSize;
  unsigned fPlayTimePerFrame;
  Boolean fFidIsSeekable;
  unsigned fLastPlayTime;
  Boolean fHaveStartedReading;
  Boolean fLimitNumBytesToStream;
  u_int64_t fNumBytesToStream; // used iff "fLimitNumBytesToStream" is True
};

#endif
