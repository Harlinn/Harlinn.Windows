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
// on demand, from an WAV audio file.
// C++ header

#ifndef _WAV_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _WAV_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class WAVAudioFileServerMediaSubsession: public FileServerMediaSubsession{
public:
  LIVE555_EXPORT 
  static WAVAudioFileServerMediaSubsession*
  createNew(UsageEnvironment& env, char const* fileName, Boolean reuseFirstSource,
	    Boolean convertToULaw = False);
      // If "convertToULaw" is True, 16-bit audio streams are converted to
      // 8-bit u-law audio prior to streaming.

protected:
  LIVE555_EXPORT 
  WAVAudioFileServerMediaSubsession(UsageEnvironment& env, char const* fileName,
				    Boolean reuseFirstSource, Boolean convertToULaw);
      // called only by createNew();
  LIVE555_EXPORT
  virtual ~WAVAudioFileServerMediaSubsession();

protected: // redefined virtual functions
  LIVE555_EXPORT 
  virtual void seekStreamSource(FramedSource* inputSource, double& seekNPT, double streamDuration, u_int64_t& numBytes);
  LIVE555_EXPORT
  virtual void setStreamSourceScale(FramedSource* inputSource, float scale);
  LIVE555_EXPORT
  virtual void setStreamSourceDuration(FramedSource* inputSource, double streamDuration, u_int64_t& numBytes);

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
  Boolean fConvertToULaw;

  // The following parameters of the input stream are set after
  // "createNewStreamSource" is called:
  unsigned char fAudioFormat;
  unsigned char fBitsPerSample;
  unsigned fSamplingFrequency;
  unsigned fNumChannels;
  float fFileDuration;
};

#endif
