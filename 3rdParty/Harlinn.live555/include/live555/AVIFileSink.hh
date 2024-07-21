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
// A sink that generates an AVI file from a composite media session
// C++ header

#ifndef _AVI_FILE_SINK_HH
#define _AVI_FILE_SINK_HH

#ifndef _MEDIA_SESSION_HH
#include "MediaSession.hh"
#endif

class AVIFileSink: public Medium {
public:
  LIVE555_EXPORT
  static AVIFileSink* createNew(UsageEnvironment& env,
				MediaSession& inputSession,
				char const* outputFileName,
				unsigned bufferSize = 20000,
				unsigned short movieWidth = 240,
				unsigned short movieHeight = 180,
				unsigned movieFPS = 15,
				Boolean packetLossCompensate = False);

  typedef void (afterPlayingFunc)(void* clientData);
  LIVE555_EXPORT
  Boolean startPlaying(afterPlayingFunc* afterFunc,
                       void* afterClientData);

  unsigned numActiveSubsessions() const { return fNumSubsessions; }

private:
  LIVE555_EXPORT
  AVIFileSink(UsageEnvironment& env, MediaSession& inputSession,
	      char const* outputFileName, unsigned bufferSize,
	      unsigned short movieWidth, unsigned short movieHeight,
	      unsigned movieFPS, Boolean packetLossCompensate);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~AVIFileSink();

  LIVE555_EXPORT
  Boolean continuePlaying();
  LIVE555_EXPORT
  static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  LIVE555_EXPORT
  static void onSourceClosure(void* clientData);
  LIVE555_EXPORT
  void onSourceClosure1();
  LIVE555_EXPORT
  static void onRTCPBye(void* clientData);
  LIVE555_EXPORT
  void addIndexRecord(class AVIIndexRecord* newIndexRecord);
  LIVE555_EXPORT
  void completeOutputFile();

private:
  friend class AVISubsessionIOState;
  MediaSession& fInputSession;
  FILE* fOutFid;
  class AVIIndexRecord *fIndexRecordsHead, *fIndexRecordsTail;
  unsigned fNumIndexRecords;
  unsigned fBufferSize;
  Boolean fPacketLossCompensate;
  Boolean fAreCurrentlyBeingPlayed;
  afterPlayingFunc* fAfterFunc;
  void* fAfterClientData;
  unsigned fNumSubsessions;
  unsigned fNumBytesWritten;
  struct timeval fStartTime;
  Boolean fHaveCompletedOutputFile;

private:
  ///// Definitions specific to the AVI file format:
  LIVE555_EXPORT
  unsigned addWord(unsigned word); // outputs "word" in little-endian order
  LIVE555_EXPORT
  unsigned addHalfWord(unsigned short halfWord);
  unsigned addByte(unsigned char byte) {
    putc(byte, fOutFid);
    return 1;
  }
  LIVE555_EXPORT
  unsigned addZeroWords(unsigned numWords);
  LIVE555_EXPORT
  unsigned add4ByteString(char const* str);
  LIVE555_EXPORT
  void setWord(unsigned filePosn, unsigned size);

  // Define member functions for outputting various types of file header:
#define _header(name) unsigned addFileHeader_##name()
  _header(AVI);
      _header(hdrl);
          _header(avih);
          _header(strl);
              _header(strh);
              _header(strf);
              _header(JUNK);
//        _header(JUNK);
      _header(movi);
private:
  unsigned short fMovieWidth, fMovieHeight;
  unsigned fMovieFPS;
  unsigned fRIFFSizePosition, fRIFFSizeValue;
  unsigned fAVIHMaxBytesPerSecondPosition;
  unsigned fAVIHFrameCountPosition;
  unsigned fMoviSizePosition, fMoviSizeValue;
  class AVISubsessionIOState* fCurrentIOState;
  unsigned fJunkNumber;
};

#endif
