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
// Common routines used by both RTSP clients and servers
// C++ header

#ifndef _RTSP_COMMON_HH
#define _RTSP_COMMON_HH

#ifndef _BOOLEAN_HH
#include "Boolean.hh"
#endif

#ifndef _MEDIA_HH
#include <Media.hh> // includes some definitions perhaps needed for Borland compilers?
#endif

#if defined(__WIN32__) || defined(_WIN32) || defined(_QNX4)
#define _strncasecmp _strnicmp
#define snprintf _snprintf
#else
#define _strncasecmp strncasecmp
#endif

#define RTSP_PARAM_STRING_MAX 200

LIVE555_EXPORT Boolean parseRTSPRequestString(char const *reqStr, unsigned reqStrSize, // in
			       char *resultCmdName, // out
			       unsigned resultCmdNameMaxSize, // in
			       char* resultURLPreSuffix, // out
			       unsigned resultURLPreSuffixMaxSize, // in
			       char* resultURLSuffix, // out
			       unsigned resultURLSuffixMaxSize, // in
			       char* resultCSeq, // out
			       unsigned resultCSeqMaxSize, // in
			       char* resultSessionId, // out
			       unsigned resultSessionIdMaxSize, // in
			       unsigned& contentLength, Boolean& urlIsRTSPS); // out

LIVE555_EXPORT Boolean parseRangeParam(char const* paramStr, double& rangeStart, double& rangeEnd, char*& absStartTime, char*& absEndTime, Boolean& startTimeIsNow);
LIVE555_EXPORT Boolean parseRangeHeader(char const* buf, double& rangeStart, double& rangeEnd, char*& absStartTime, char*& absEndTime, Boolean& startTimeIsNow);

LIVE555_EXPORT Boolean parseScaleHeader(char const* buf, float& scale);

LIVE555_EXPORT Boolean RTSPOptionIsSupported(char const* commandName, char const* optionsResponseString);
    // Returns True iff the RTSP command "commandName" is mentioned as one of the commands supported in "optionsResponseString"
    // (which should be the 'resultString' from a previous RTSP "OPTIONS" request).

LIVE555_EXPORT char const* dateHeader(); // A "Date:" header that can be used in a RTSP (or HTTP) response 

#endif
