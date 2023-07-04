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
// Media Sources
// C++ header

#ifndef _MEDIA_SOURCE_HH
#define _MEDIA_SOURCE_HH

#ifndef _MEDIA_HH
#include "Media.hh"
#endif

class MediaSource: public Medium {
public:
  LIVE555_EXPORT static Boolean lookupByName(UsageEnvironment& env, char const* sourceName,
			      MediaSource*& resultSource);
  LIVE555_EXPORT virtual void getAttributes() const;
      // attributes are returned in "env's" 'result message'

  // The MIME type of this source:
  LIVE555_EXPORT virtual char const* MIMEtype() const;

  // Test for specific types of source:
  LIVE555_EXPORT virtual Boolean isFramedSource() const;
  LIVE555_EXPORT virtual Boolean isRTPSource() const;
  LIVE555_EXPORT virtual Boolean isMPEG1or2VideoStreamFramer() const;
  LIVE555_EXPORT virtual Boolean isMPEG4VideoStreamFramer() const;
  LIVE555_EXPORT virtual Boolean isH264VideoStreamFramer() const;
  LIVE555_EXPORT virtual Boolean isH265VideoStreamFramer() const;
  LIVE555_EXPORT virtual Boolean isDVVideoStreamFramer() const;
  LIVE555_EXPORT virtual Boolean isJPEGVideoSource() const;
  LIVE555_EXPORT virtual Boolean isAMRAudioSource() const;
  LIVE555_EXPORT virtual Boolean isMPEG2TransportStreamMultiplexor() const;

protected:
  LIVE555_EXPORT MediaSource(UsageEnvironment& env); // abstract base class
  LIVE555_EXPORT virtual ~MediaSource();

private:
  // redefined virtual functions:
  LIVE555_EXPORT virtual Boolean isSource() const;
};

#endif
