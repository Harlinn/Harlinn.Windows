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
// VP8 Video RTP Sources
// C++ header

#ifndef _VP8_VIDEO_RTP_SOURCE_HH
#define _VP8_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class VP8VideoRTPSource: public MultiFramedRTPSource {
public:
  LIVE555_EXPORT 
  static VP8VideoRTPSource*
  createNew(UsageEnvironment& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat,
	    unsigned rtpTimestampFrequency = 90000);

protected:
  LIVE555_EXPORT 
  VP8VideoRTPSource(UsageEnvironment& env, Groupsock* RTPgs,
		    unsigned char rtpPayloadFormat,
		    unsigned rtpTimestampFrequency);
      // called only by createNew()

  LIVE555_EXPORT
  virtual ~VP8VideoRTPSource();

protected:
  // redefined virtual functions:
  LIVE555_EXPORT 
  virtual Boolean processSpecialHeader(BufferedPacket* packet,
                                       unsigned& resultSpecialHeaderSize);
  LIVE555_EXPORT 
  virtual char const* MIMEtype() const;
};

#endif
