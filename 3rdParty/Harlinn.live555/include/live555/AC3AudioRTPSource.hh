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
// AC3 Audio RTP Sources
// C++ header

#ifndef _AC3_AUDIO_RTP_SOURCE_HH
#define _AC3_AUDIO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class AC3AudioRTPSource: public MultiFramedRTPSource {
public:
  LIVE555_EXPORT 
  static AC3AudioRTPSource*
  createNew(UsageEnvironment& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat,
	    unsigned rtpTimestampFrequency);

protected:
  LIVE555_EXPORT 
  virtual ~AC3AudioRTPSource();

private:
  LIVE555_EXPORT 
  AC3AudioRTPSource(UsageEnvironment& env, Groupsock* RTPgs,
		     unsigned char rtpPayloadFormat,
		     unsigned rtpTimestampFrequency);
      // called only by createNew()

private:
  // redefined virtual functions:
  LIVE555_EXPORT 
  virtual Boolean processSpecialHeader(BufferedPacket* packet,
                                       unsigned& resultSpecialHeaderSize);
  LIVE555_EXPORT
  virtual char const* MIMEtype() const;
};

#endif
