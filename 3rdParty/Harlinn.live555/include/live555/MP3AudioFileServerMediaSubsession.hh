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
// on demand, from an MP3 audio file.
// (Actually, any MPEG-1 or MPEG-2 audio file should work.)
// C++ header

#ifndef _MP3_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _MP3_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif
#ifndef _MP3_ADU_INTERLEAVING_HH
#include "MP3ADUinterleaving.hh"
#endif
#ifndef _MP3_ADU_HH
#include "MP3ADU.hh"
#endif

class MP3AudioFileServerMediaSubsession: public FileServerMediaSubsession{
public:
  LIVE555_EXPORT 
  static MP3AudioFileServerMediaSubsession*
  createNew(UsageEnvironment& env, char const* fileName, Boolean reuseFirstSource,
	    Boolean generateADUs, Interleaving* interleaving);
      // Note: "interleaving" is used only if "generateADUs" is True,
      // (and a value of NULL means 'no interleaving')

protected:
  LIVE555_EXPORT 
  MP3AudioFileServerMediaSubsession(UsageEnvironment& env,
				    char const* fileName, Boolean reuseFirstSource,
				    Boolean generateADUs,
				    Interleaving* interleaving);
      // called only by createNew();
  LIVE555_EXPORT
  virtual ~MP3AudioFileServerMediaSubsession();

  LIVE555_EXPORT
  FramedSource* createNewStreamSourceCommon(FramedSource* baseMP3Source, unsigned mp3NumBytes, unsigned& estBitrate);
  LIVE555_EXPORT
  void getBaseStreams(FramedSource* frontStream,
		      FramedSource*& sourceMP3Stream, ADUFromMP3Source*& aduStream/*if any*/);

protected: // redefined virtual functions
  LIVE555_EXPORT 
  virtual void seekStreamSource(FramedSource* inputSource, double& seekNPT, double streamDuration, u_int64_t& numBytes);
  LIVE555_EXPORT
  virtual void setStreamSourceScale(FramedSource* inputSource, float scale);
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

protected:
  Boolean fGenerateADUs;
  Interleaving* fInterleaving;
  float fFileDuration;
};

#endif
