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
// An class that can be used to create (possibly multiple) 'replicas' of an incoming stream.
// C++ header

#ifndef _STREAM_REPLICATOR_HH
#define _STREAM_REPLICATOR_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

class StreamReplica; // forward

class StreamReplicator: public Medium {
public:
  LIVE555_EXPORT 
  static StreamReplicator* createNew(UsageEnvironment& env, FramedSource* inputSource, Boolean deleteWhenLastReplicaDies = True);
    // If "deleteWhenLastReplicaDies" is True (the default), then the "StreamReplicator" object is deleted when (and only when)
    //   all replicas have been deleted.  (In this case, you must *not* call "Medium::close()" on the "StreamReplicator" object,
    //   unless you never created any replicas from it to begin with.)
    // If "deleteWhenLastReplicaDies" is False, then the "StreamReplicator" object remains in existence, even when all replicas
    //   have been deleted.  (This allows you to create new replicas later, if you wish.)  In this case, you delete the
    //   "StreamReplicator" object by calling "Medium::close()" on it - but you must do so only when "numReplicas()" returns 0.

  LIVE555_EXPORT
  FramedSource* createStreamReplica();

  unsigned numReplicas() const { return fNumReplicas; }

  FramedSource* inputSource() const { return fInputSource; }

  // Call before destruction if you want to prevent the destructor from closing the input source
  void detachInputSource() { fInputSource = NULL; }

protected:
  LIVE555_EXPORT 
  StreamReplicator(UsageEnvironment& env, FramedSource* inputSource, Boolean deleteWhenLastReplicaDies);
    // called only by "createNew()"
  LIVE555_EXPORT
  virtual ~StreamReplicator();

private:
  // Routines called by replicas to implement frame delivery, and the stopping/restarting/deletion of replicas:
  friend class StreamReplica;
  LIVE555_EXPORT
  void getNextFrame(StreamReplica* replica);
  LIVE555_EXPORT
  void deactivateStreamReplica(StreamReplica* replica);
  LIVE555_EXPORT
  void removeStreamReplica(StreamReplica* replica);

private:
  LIVE555_EXPORT 
  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
                                struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  LIVE555_EXPORT
  void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
			 struct timeval presentationTime, unsigned durationInMicroseconds);

  LIVE555_EXPORT
  static void onSourceClosure(void* clientData);
  LIVE555_EXPORT
  void onSourceClosure();

  LIVE555_EXPORT
  void deliverReceivedFrame();

private:
  FramedSource* fInputSource;
  Boolean fDeleteWhenLastReplicaDies, fInputSourceHasClosed; 
  unsigned fNumReplicas, fNumActiveReplicas, fNumDeliveriesMadeSoFar;
  int fFrameIndex; // 0 or 1; used to figure out if a replica is requesting the current frame, or the next frame

  StreamReplica* fPrimaryReplica; // the first replica that requests each frame.  We use its buffer when copying to the others.
  StreamReplica* fReplicasAwaitingCurrentFrame; // other than the 'primary' replica
  StreamReplica* fReplicasAwaitingNextFrame; // replicas that have already received the current frame, and have asked for the next
};
#endif
