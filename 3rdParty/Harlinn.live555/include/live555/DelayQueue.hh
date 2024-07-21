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
 // Copyright (c) 1996-2024, Live Networks, Inc.  All rights reserved
// Delay queue
// C++ header

#ifndef _DELAY_QUEUE_HH
#define _DELAY_QUEUE_HH

#ifndef _NET_COMMON_H
#include "NetCommon.h"
#endif

#ifdef TIME_BASE
typedef TIME_BASE time_base_seconds;
#else
typedef long time_base_seconds;
#endif

///// A "Timeval" can be either an absolute time, or a time interval /////

class Timeval {
public:
  time_base_seconds seconds() const {
    return fTv.tv_sec;
  }
  time_base_seconds seconds() {
    return fTv.tv_sec;
  }
  time_base_seconds useconds() const {
    return fTv.tv_usec;
  }
  time_base_seconds useconds() {
    return fTv.tv_usec;
  }

  LIVE555_EXPORT int operator>=(Timeval const& arg2) const;
  int operator<=(Timeval const& arg2) const {
    return arg2 >= *this;
  }
  int operator<(Timeval const& arg2) const {
    return !(*this >= arg2);
  }
  int operator>(Timeval const& arg2) const {
    return arg2 < *this;
  }
  int operator==(Timeval const& arg2) const {
    return *this >= arg2 && arg2 >= *this;
  }
  int operator!=(Timeval const& arg2) const {
    return !(*this == arg2);
  }

  LIVE555_EXPORT void operator+=(class DelayInterval const& arg2);
  LIVE555_EXPORT void operator-=(class DelayInterval const& arg2);
  // returns ZERO iff arg2 >= arg1

protected:
  Timeval(time_base_seconds seconds, time_base_seconds useconds) {
    fTv.tv_sec = seconds; fTv.tv_usec = useconds;
  }

private:
  time_base_seconds& secs() {
    return (time_base_seconds&)fTv.tv_sec;
  }
  time_base_seconds& usecs() {
    return (time_base_seconds&)fTv.tv_usec;
  }

  struct timeval fTv;
};

#ifndef max
inline Timeval max(Timeval const& arg1, Timeval const& arg2) {
  return arg1 >= arg2 ? arg1 : arg2;
}
#endif
#ifndef min
inline Timeval min(Timeval const& arg1, Timeval const& arg2) {
  return arg1 <= arg2 ? arg1 : arg2;
}
#endif

LIVE555_EXPORT class DelayInterval operator-(Timeval const& arg1, Timeval const& arg2);
// returns ZERO iff arg2 >= arg1


///// DelayInterval /////

class DelayInterval: public Timeval {
public:
  DelayInterval(time_base_seconds seconds, time_base_seconds useconds)
    : Timeval(seconds, useconds) {}
};

LIVE555_EXPORT DelayInterval operator*(short arg1, DelayInterval const& arg2);

LIVE555_EXPORT extern DelayInterval const DELAY_ZERO;
LIVE555_EXPORT extern DelayInterval const DELAY_SECOND;
LIVE555_EXPORT extern DelayInterval const DELAY_MINUTE;
LIVE555_EXPORT extern DelayInterval const DELAY_HOUR;
LIVE555_EXPORT extern DelayInterval const DELAY_DAY;

///// _EventTime /////

class _EventTime: public Timeval {
public:
  _EventTime(unsigned secondsSinceEpoch = 0,
	    unsigned usecondsSinceEpoch = 0)
    // We use the Unix standard epoch: January 1, 1970
    : Timeval(secondsSinceEpoch, usecondsSinceEpoch) {}
};

_EventTime TimeNow();

extern _EventTime const THE_END_OF_TIME;


///// DelayQueueEntry /////

class DelayQueueEntry {
public:
  LIVE555_EXPORT virtual ~DelayQueueEntry();

  intptr_t token() {
    return fToken;
  }

protected: // abstract base class
  LIVE555_EXPORT DelayQueueEntry(DelayInterval delay, intptr_t token);

  LIVE555_EXPORT virtual void handleTimeout();

private:
  friend class DelayQueue;
  DelayQueueEntry* fNext;
  DelayQueueEntry* fPrev;
  DelayInterval fDeltaTimeRemaining;

  intptr_t fToken;
};

///// DelayQueue /////

class DelayQueue: public DelayQueueEntry {
public:
  LIVE555_EXPORT DelayQueue();
  LIVE555_EXPORT virtual ~DelayQueue();

  LIVE555_EXPORT void addEntry(DelayQueueEntry* newEntry); // returns a token for the entry
  LIVE555_EXPORT void updateEntry(DelayQueueEntry* entry, DelayInterval newDelay);
  LIVE555_EXPORT void updateEntry(intptr_t tokenToFind, DelayInterval newDelay);
  LIVE555_EXPORT void removeEntry(DelayQueueEntry* entry); // but doesn't delete it
  LIVE555_EXPORT DelayQueueEntry* removeEntry(intptr_t tokenToFind); // but doesn't delete it

  LIVE555_EXPORT DelayInterval const& timeToNextAlarm();
  LIVE555_EXPORT void handleAlarm();

private:
  DelayQueueEntry* head() { return fNext; }
  LIVE555_EXPORT DelayQueueEntry* findEntryByToken(intptr_t token);
  LIVE555_EXPORT void synchronize(); // bring the 'time remaining' fields up-to-date

  _EventTime fLastSyncTime;
};

#endif
