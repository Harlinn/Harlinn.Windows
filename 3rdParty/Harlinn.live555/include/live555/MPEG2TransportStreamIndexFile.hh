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
// A class that encapsulates MPEG-2 Transport Stream 'index files'/
// These index files are used to implement 'trick play' operations
// (seek-by-time, fast forward, reverse play) on Transport Stream files.
//
// C++ header

#ifndef _MPEG2_TRANSPORT_STREAM_INDEX_FILE_HH
#define _MPEG2_TRANSPORT_STREAM_INDEX_FILE_HH

#ifndef _MEDIA_HH
#include "Media.hh"
#endif

#define INDEX_RECORD_SIZE 11

class MPEG2TransportStreamIndexFile: public Medium {
public:
  LIVE555_EXPORT 
  static MPEG2TransportStreamIndexFile* createNew(UsageEnvironment& env,
						  char const* indexFileName);

  LIVE555_EXPORT
  virtual ~MPEG2TransportStreamIndexFile();

  // Functions that map between a playing time and a Transport packet number
  // in the original Transport Stream file:

  LIVE555_EXPORT
  void lookupTSPacketNumFromNPT(float& npt, unsigned long& tsPacketNumber,
			    unsigned long& indexRecordNumber);
    // Looks up the Transport Stream Packet number corresponding to "npt".
	// (This may modify "npt" to a more exact value.)
        // (We also return the index record number that we looked up.)

  LIVE555_EXPORT
  void lookupPCRFromTSPacketNum(unsigned long& tsPacketNumber, Boolean reverseToPreviousCleanPoint,
				float& pcr, unsigned long& indexRecordNumber);
    // Looks up the PCR timestamp for the transport packet "tsPacketNumber".
	// (Adjust "tsPacketNumber" only if "reverseToPreviousCleanPoint" is True.)
        // (We also return the index record number that we looked up.)

  // Miscellaneous functions used to implement 'trick play':
  LIVE555_EXPORT
  Boolean readIndexRecordValues(unsigned long indexRecordNum,
				unsigned long& transportPacketNum, u_int8_t& offset,
				u_int8_t& size, float& pcr, u_int8_t& recordType);
  LIVE555_EXPORT
  float getPlayingDuration();
  void stopReading() { closeFid(); }

  LIVE555_EXPORT
  int mpegVersion();
      // returns the best guess for the version of MPEG being used for data within the underlying Transport Stream file.
      // (1,2,4, or 5 (representing H.264).  0 means 'don't know' (usually because the index file is empty))

private:
  LIVE555_EXPORT 
  MPEG2TransportStreamIndexFile(UsageEnvironment& env, char const* indexFileName);

  LIVE555_EXPORT
  Boolean openFid();
  LIVE555_EXPORT
  Boolean seekToIndexRecord(unsigned long indexRecordNumber);
  LIVE555_EXPORT
  Boolean readIndexRecord(unsigned long indexRecordNum); // into "fBuf"
  LIVE555_EXPORT
  Boolean readOneIndexRecord(unsigned long indexRecordNum); // closes "fFid" at end
  LIVE555_EXPORT
  void closeFid();

  u_int8_t recordTypeFromBuf() { return fBuf[0]; }
  u_int8_t offsetFromBuf() { return fBuf[1]; }
  u_int8_t sizeFromBuf() { return fBuf[2]; }
  LIVE555_EXPORT
  float pcrFromBuf(); // after "fBuf" has been read
  LIVE555_EXPORT
  unsigned long tsPacketNumFromBuf();
  LIVE555_EXPORT
  void setMPEGVersionFromRecordType(u_int8_t recordType);

  LIVE555_EXPORT
  Boolean rewindToCleanPoint(unsigned long&ixFound);
      // used to implement "lookupTSPacketNumber()"

private:
  char* fFileName;
  FILE* fFid; // used internally when reading from the file
  int fMPEGVersion;
  unsigned long fCurrentIndexRecordNum; // within "fFid"
  float fCachedPCR;
  unsigned long fCachedTSPacketNumber, fCachedIndexRecordNumber;
  unsigned long fNumIndexRecords;
  unsigned char fBuf[INDEX_RECORD_SIZE]; // used for reading index records from file
};

#endif
