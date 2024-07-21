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
// H.264 Video RTP Sources
// C++ header

#ifndef _H264_VIDEO_RTP_SOURCE_HH
#define _H264_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class H264VideoRTPSource: public MultiFramedRTPSource {
public:
  LIVE555_EXPORT 
  static H264VideoRTPSource*
  createNew(UsageEnvironment& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat,
	    unsigned rtpTimestampFrequency = 90000);

protected:
  LIVE555_EXPORT 
  H264VideoRTPSource(UsageEnvironment& env, Groupsock* RTPgs,
			 unsigned char rtpPayloadFormat,
			 unsigned rtpTimestampFrequency);
      // called only by createNew()
  LIVE555_EXPORT
  virtual ~H264VideoRTPSource();

protected:
  // redefined virtual functions:
  LIVE555_EXPORT 
  virtual Boolean processSpecialHeader(BufferedPacket* packet,
                                       unsigned& resultSpecialHeaderSize);
  LIVE555_EXPORT
  virtual char const* MIMEtype() const;

private:
  friend class H264BufferedPacket;
  unsigned char fCurPacketNALUnitType;
};

class SPropRecord {
public:
  ~SPropRecord() { delete[] sPropBytes; }

  unsigned sPropLength; // in bytes
  unsigned char* sPropBytes;
};

LIVE555_EXPORT
SPropRecord* parseSPropParameterSets(char const* sPropParameterSetsStr,
				     // result parameter:
				     unsigned& numSPropRecords);
    // Returns the binary value of each 'parameter set' specified in a
    // "sprop-parameter-sets" string (in the SDP description for a H.264/RTP stream).
    // The value is returned as an array (length "numSPropRecords") of "SPropRecord"s.
    // This array is dynamically allocated by this routine, and must be delete[]d by the caller.

#endif
