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

#ifndef _BASIC_USAGE_ENVIRONMENT_HH
#define _BASIC_USAGE_ENVIRONMENT_HH

#ifndef _BASIC_USAGE_ENVIRONMENT0_HH
#include "BasicUsageEnvironment0.hh"
#endif

class BasicUsageEnvironment: public BasicUsageEnvironment0 {
public:
  LIVE555_EXPORT 
  static BasicUsageEnvironment* createNew(TaskScheduler& taskScheduler);

  // redefined virtual functions:
  LIVE555_EXPORT
  virtual int getErrno() const;

  LIVE555_EXPORT
  virtual UsageEnvironment& operator<<(char const* str);
  LIVE555_EXPORT
  virtual UsageEnvironment& operator<<(int i);
  LIVE555_EXPORT
  virtual UsageEnvironment& operator<<(unsigned u);
  LIVE555_EXPORT
  virtual UsageEnvironment& operator<<(double d);
  LIVE555_EXPORT
  virtual UsageEnvironment& operator<<(void* p);

protected:
  LIVE555_EXPORT 
  BasicUsageEnvironment(TaskScheduler& taskScheduler);
      // called only by "createNew()" (or subclass constructors)
  LIVE555_EXPORT
  virtual ~BasicUsageEnvironment();
};


class BasicTaskScheduler: public BasicTaskScheduler0 {
public:
  LIVE555_EXPORT 
  static BasicTaskScheduler* createNew(unsigned maxSchedulerGranularity = 10000/*microseconds*/);
    // "maxSchedulerGranularity" (default value: 10 ms) specifies the maximum time that we wait (in "select()") before
    // returning to the event loop to handle non-socket or non-timer-based events, such as 'triggered events'.
    // You can change this is you wish (but only if you know what you're doing!), or set it to 0, to specify no such maximum time.
    // (You should set it to 0 only if you know that you will not be using 'event triggers'.)
  LIVE555_EXPORT
  virtual ~BasicTaskScheduler();

protected:
  LIVE555_EXPORT 
  BasicTaskScheduler(unsigned maxSchedulerGranularity);
      // called only by "createNew()"
  LIVE555_EXPORT
  static void schedulerTickTask(void* clientData);
  LIVE555_EXPORT
  void schedulerTickTask();

protected:
  // Redefined virtual functions:
  LIVE555_EXPORT 
  virtual void SingleStep(unsigned maxDelayTime);

  LIVE555_EXPORT
  virtual void setBackgroundHandling(int socketNum, int conditionSet, BackgroundHandlerProc* handlerProc, void* clientData);
  LIVE555_EXPORT
  virtual void moveSocketHandling(int oldSocketNum, int newSocketNum);

protected:
  unsigned fMaxSchedulerGranularity;

  // To implement background operations:
  int fMaxNumSockets;
  fd_set fReadSet;
  fd_set fWriteSet;
  fd_set fExceptionSet;

private:
#if defined(__WIN32__) || defined(_WIN32)
  // Hack to work around a bug in Windows' "select()" implementation:
  int fDummySocketNum;
#endif
};

#endif
