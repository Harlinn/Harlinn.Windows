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
// A server demultiplexor for an Ogg file
// C++ header

#ifndef _OGG_FILE_SERVER_DEMUX_HH
#define _OGG_FILE_SERVER_DEMUX_HH

#ifndef _SERVER_MEDIA_SESSION_HH
#include "ServerMediaSession.hh"
#endif

#ifndef _OGG_FILE_HH
#include "OggFile.hh"
#endif

class OggFileServerDemux: public Medium {
public:
  typedef void (__cdecl onCreationFunc)(OggFileServerDemux* newDemux, void* clientData);
  LIVE555_EXPORT static void createNew(UsageEnvironment& env, char const* fileName,
			onCreationFunc* onCreation, void* onCreationClientData);
    // Note: Unlike most "createNew()" functions, this one doesn't return a new object immediately.  Instead, because this class
    // requires file reading (to parse the Ogg 'Track' headers) before a new object can be initialized, the creation of a new
    // object is signalled by calling - from the event loop - an 'onCreationFunc' that is passed as a parameter to "createNew()". 

  LIVE555_EXPORT ServerMediaSubsession* newServerMediaSubsession();
  LIVE555_EXPORT ServerMediaSubsession* newServerMediaSubsession(u_int32_t& resultTrackNumber);
    // Returns a new "ServerMediaSubsession" object that represents the next media track
    // from the file.  This function returns NULL when no more media tracks exist.

  LIVE555_EXPORT ServerMediaSubsession* newServerMediaSubsessionByTrackNumber(u_int32_t trackNumber);
  // As above, but creates a new "ServerMediaSubsession" object for a specific track number
  // within the Ogg file.
  // (You should not call this function more than once with the same track number.)

  // The following public: member functions are called only by the "ServerMediaSubsession" objects:

  OggFile* ourOggFile() { return fOurOggFile; }
  char const* fileName() const { return fFileName; }

  LIVE555_EXPORT FramedSource* newDemuxedTrack(unsigned clientSessionId, u_int32_t trackNumber);
    // Used by the "ServerMediaSubsession" objects to implement their "createNewStreamSource()" virtual function.

private:
  LIVE555_EXPORT OggFileServerDemux(UsageEnvironment& env, char const* fileName,
		     onCreationFunc* onCreation, void* onCreationClientData);
      // called only by createNew()
  LIVE555_EXPORT virtual ~OggFileServerDemux();

  LIVE555_EXPORT static void onOggFileCreation(OggFile* newFile, void* clientData);
  LIVE555_EXPORT void onOggFileCreation(OggFile* newFile);

  LIVE555_EXPORT static void onDemuxDeletion(void* clientData, OggDemux* demuxBeingDeleted);
  LIVE555_EXPORT void onDemuxDeletion(OggDemux* demuxBeingDeleted);
  
private:
  char const* fFileName; 
  onCreationFunc* fOnCreation;
  void* fOnCreationClientData;
  OggFile* fOurOggFile;

  // Used to implement "newServerMediaSubsession()":
  OggTrackTableIterator* fIter;

  // Used to set up demuxing, to implement "newDemuxedTrack()":
  unsigned fLastClientSessionId;
  OggDemux* fLastCreatedDemux;
};

#endif
