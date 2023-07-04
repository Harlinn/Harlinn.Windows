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
// A server demultiplexor for a Matroska file
// C++ header

#ifndef _MATROSKA_FILE_SERVER_DEMUX_HH
#define _MATROSKA_FILE_SERVER_DEMUX_HH

#ifndef _SERVER_MEDIA_SESSION_HH
#include "ServerMediaSession.hh"
#endif

#ifndef _MATROSKA_FILE_HH
#include "MatroskaFile.hh"
#endif

class MatroskaFileServerDemux: public Medium {
public:
  typedef void (__cdecl onCreationFunc)(MatroskaFileServerDemux* newDemux, void* clientData);
  LIVE555_EXPORT static void createNew(UsageEnvironment& env, char const* fileName,
			onCreationFunc* onCreation, void* onCreationClientData,
			char const* preferredLanguage = "eng");
    // Note: Unlike most "createNew()" functions, this one doesn't return a new object immediately.  Instead, because this class
    // requires file reading (to parse the Matroska 'Track' headers) before a new object can be initialized, the creation of a new
    // object is signalled by calling - from the event loop - an 'onCreationFunc' that is passed as a parameter to "createNew()". 

  LIVE555_EXPORT ServerMediaSubsession* newServerMediaSubsession();
  LIVE555_EXPORT ServerMediaSubsession* newServerMediaSubsession(unsigned& resultTrackNumber);
    // Returns a new "ServerMediaSubsession" object that represents the next preferred media track
    // (video, audio, subtitle - in that order) from the file. (Preferred media tracks are based on the file's language preference.)
    // This function returns NULL when no more media tracks exist.

  LIVE555_EXPORT ServerMediaSubsession* newServerMediaSubsessionByTrackNumber(unsigned trackNumber);
    // As above, but creates a new "ServerMediaSubsession" object for a specific track number within the Matroska file.
    // (You should not call this function more than once with the same track number.)

  // The following public: member functions are called only by the "ServerMediaSubsession" objects:

  MatroskaFile* ourMatroskaFile() { return fOurMatroskaFile; }
  char const* fileName() const { return fFileName; }
  float fileDuration() const { return fOurMatroskaFile->fileDuration(); }

  LIVE555_EXPORT FramedSource* newDemuxedTrack(unsigned clientSessionId, unsigned trackNumber);
    // Used by the "ServerMediaSubsession" objects to implement their "createNewStreamSource()" virtual function.

private:
  LIVE555_EXPORT MatroskaFileServerDemux(UsageEnvironment& env, char const* fileName,
			  onCreationFunc* onCreation, void* onCreationClientData,
			  char const* preferredLanguage);
      // called only by createNew()
  LIVE555_EXPORT virtual ~MatroskaFileServerDemux();

  LIVE555_EXPORT static void onMatroskaFileCreation(MatroskaFile* newFile, void* clientData);
  LIVE555_EXPORT void onMatroskaFileCreation(MatroskaFile* newFile);

  LIVE555_EXPORT static void onDemuxDeletion(void* clientData, MatroskaDemux* demuxBeingDeleted);
  LIVE555_EXPORT void onDemuxDeletion(MatroskaDemux* demuxBeingDeleted);

private:
  char const* fFileName; 
  onCreationFunc* fOnCreation;
  void* fOnCreationClientData;
  MatroskaFile* fOurMatroskaFile;

  // Used to implement "newServerMediaSubsession()":
  u_int8_t fNextTrackTypeToCheck;

  // Used to set up demuxing, to implement "newDemuxedTrack()":
  unsigned fLastClientSessionId;
  MatroskaDemux* fLastCreatedDemux;
};

#endif
