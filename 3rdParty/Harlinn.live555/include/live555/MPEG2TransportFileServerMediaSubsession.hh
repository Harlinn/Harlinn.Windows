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
// A 'ServerMediaSubsession' object that creates new, unicast, "RTPSink"s
// on demand, from a MPEG-2 Transport Stream file.
// C++ header

#ifndef _MPEG2_TRANSPORT_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _MPEG2_TRANSPORT_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif
#ifndef _MPEG2_TRANSPORT_STREAM_FRAMER_HH
#include "MPEG2TransportStreamFramer.hh"
#endif
#ifndef _BYTE_STREAM_FILE_SOURCE_HH
#include "ByteStreamFileSource.hh"
#endif
#ifndef _MPEG2_TRANSPORT_STREAM_TRICK_MODE_FILTER_HH
#include "MPEG2TransportStreamTrickModeFilter.hh"
#endif
#ifndef _MPEG2_TRANSPORT_STREAM_FROM_ES_SOURCE_HH
#include "MPEG2TransportStreamFromESSource.hh"
#endif

class ClientTrickPlayState; // forward

class MPEG2TransportFileServerMediaSubsession: public FileServerMediaSubsession {
public:
  LIVE555_EXPORT
  static MPEG2TransportFileServerMediaSubsession*
  createNew(UsageEnvironment& env,
	    char const* dataFileName, char const* indexFileName,
	    Boolean reuseFirstSource);

protected:
  LIVE555_EXPORT
  MPEG2TransportFileServerMediaSubsession(UsageEnvironment& env,
					  char const* fileName,
					  MPEG2TransportStreamIndexFile* indexFile,
					  Boolean reuseFirstSource);
      // called only by createNew();
  LIVE555_EXPORT
  virtual ~MPEG2TransportFileServerMediaSubsession();

  LIVE555_EXPORT
  virtual ClientTrickPlayState* newClientTrickPlayState();

private: // redefined virtual functions
  // Note that because - to implement 'trick play' operations - we're operating on
  // more than just the input source, we reimplement some functions that are
  // already implemented in "OnDemandServerMediaSubsession", rather than
  // reimplementing "seekStreamSource()" and "setStreamSourceScale()":
  LIVE555_EXPORT
  virtual void startStream(unsigned clientSessionId, void* streamToken,
                           TaskFunc* rtcpRRHandler,
                           void* rtcpRRHandlerClientData,
                           unsigned short& rtpSeqNum,
                           unsigned& rtpTimestamp,
			   ServerRequestAlternativeByteHandler* serverRequestAlternativeByteHandler,
                           void* serverRequestAlternativeByteHandlerClientData);
  LIVE555_EXPORT
  virtual void pauseStream(unsigned clientSessionId, void* streamToken);
  LIVE555_EXPORT
  virtual void seekStream(unsigned clientSessionId, void* streamToken, double& seekNPT, double streamDuration, u_int64_t& numBytes);
  LIVE555_EXPORT
  virtual void setStreamScale(unsigned clientSessionId, void* streamToken, float scale);
  LIVE555_EXPORT
  virtual void deleteStream(unsigned clientSessionId, void*& streamToken);

  // The virtual functions that are usually implemented by "ServerMediaSubsession"s:
  LIVE555_EXPORT
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate);
  LIVE555_EXPORT
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource);

  LIVE555_EXPORT
  virtual void testScaleFactor(float& scale);
  LIVE555_EXPORT
  virtual float duration() const;

private:
  LIVE555_EXPORT
  ClientTrickPlayState* lookupClient(unsigned clientSessionId);

private:
  MPEG2TransportStreamIndexFile* fIndexFile;
  float fDuration;
  HashTable* fClientSessionHashTable; // indexed by client session id
};


// This class encapsulates the 'trick play' state for each current client (for
// a given "MPEG2TransportFileServerMediaSubsession" - i.e., Transport Stream file).
// It is used only within the implementation of "MPEG2TransportFileServerMediaSubsession", but is included here,
// in case subclasses of "MPEG2TransportFileServerMediaSubsession" want to use it.

class ClientTrickPlayState {
public:
  LIVE555_EXPORT
  ClientTrickPlayState(MPEG2TransportStreamIndexFile* indexFile);

  // Functions to bring "fNPT", "fTSRecordNum" and "fIxRecordNum" in sync:
  LIVE555_EXPORT
  unsigned long updateStateFromNPT(double npt, double seekDuration);
  LIVE555_EXPORT
  void updateStateOnScaleChange();
  LIVE555_EXPORT
  void updateStateOnPlayChange(Boolean reverseToPreviousVSH);

  LIVE555_EXPORT
  void handleStreamDeletion();
  LIVE555_EXPORT
  void setSource(MPEG2TransportStreamFramer* framer);

  void setNextScale(float nextScale) { fNextScale = nextScale; }
  Boolean areChangingScale() const { return fNextScale != fScale; }

protected:
  LIVE555_EXPORT
  void updateTSRecordNum();
  LIVE555_EXPORT
  void reseekOriginalTransportStreamSource();

protected:
  MPEG2TransportStreamIndexFile* fIndexFile;
  ByteStreamFileSource* fOriginalTransportStreamSource;
  MPEG2TransportStreamTrickModeFilter* fTrickModeFilter;
  MPEG2TransportStreamFromESSource* fTrickPlaySource;
  MPEG2TransportStreamFramer* fFramer;
  float fScale, fNextScale, fNPT;
  unsigned long fTSRecordNum, fIxRecordNum;
};

#endif
