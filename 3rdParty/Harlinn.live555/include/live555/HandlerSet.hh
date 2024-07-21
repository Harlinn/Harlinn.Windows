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
// Copyright (c) 1996-2024 Live Networks, Inc.  All rights reserved.
// Basic Usage Environment: for a simple, non-scripted, console application
// C++ header

#ifndef _HANDLER_SET_HH
#define _HANDLER_SET_HH

#ifndef _BOOLEAN_HH
#include "Boolean.hh"
#endif

////////// HandlerSet (etc.) definition //////////

class HandlerDescriptor {
  LIVE555_EXPORT 
  HandlerDescriptor(HandlerDescriptor* nextHandler);
  LIVE555_EXPORT
  virtual ~HandlerDescriptor();

public:
  int socketNum;
  int conditionSet;
  TaskScheduler::BackgroundHandlerProc* handlerProc;
  void* clientData;

private:
  // Descriptors are linked together in a doubly-linked list:
  friend class HandlerSet;
  friend class HandlerIterator;
  HandlerDescriptor* fNextHandler;
  HandlerDescriptor* fPrevHandler;
};

class HandlerSet {
public:
  LIVE555_EXPORT 
  HandlerSet();
  LIVE555_EXPORT
  virtual ~HandlerSet();

  LIVE555_EXPORT
  void assignHandler(int socketNum, int conditionSet, TaskScheduler::BackgroundHandlerProc* handlerProc, void* clientData);
  LIVE555_EXPORT
  void clearHandler(int socketNum);
  LIVE555_EXPORT
  void moveHandler(int oldSocketNum, int newSocketNum);

private:
  LIVE555_EXPORT 
  HandlerDescriptor* lookupHandler(int socketNum);

private:
  friend class HandlerIterator;
  HandlerDescriptor fHandlers;
};

class HandlerIterator {
public:
  LIVE555_EXPORT 
  HandlerIterator(HandlerSet& handlerSet);
  LIVE555_EXPORT
  virtual ~HandlerIterator();

  LIVE555_EXPORT
  HandlerDescriptor* next(); // returns NULL if none
  LIVE555_EXPORT
  void reset();

private:
  HandlerSet& fOurSet;
  HandlerDescriptor* fNextPtr;
};

#endif
