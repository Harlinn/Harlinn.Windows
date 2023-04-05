/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#pragma once

#include "skia/core/SkData.h"
#include <memory>

class SkAudioPlayer {
public:
    SK_API virtual ~SkAudioPlayer();

    // Returns null on failure (possibly unknown format?)
    SK_API static std::unique_ptr<SkAudioPlayer> Make(sk_sp<SkData>);

    // in seconds
    double duration() const { return this->onGetDuration(); }
    double time() const { return this->onGetTime(); }   // 0...duration()
    SK_API double setTime(double);                             // returns actual time

    double normalizedTime() const { return this->time() / this->duration(); }
    SK_API double setNormalizedTime(double t);

    enum class State {
        kPlaying,
        kStopped,
        kPaused,
    };
    State state() const  { return fState; }
    float volume() const { return fVolume; }    // 0...1
    float rate() const   { return fRate; }      // multiplier (e.g. 1.0 is default)

    SK_API State setState(State);      // returns actual State
    SK_API float setRate(float);       // returns actual rate
    SK_API float setVolume(float);     // returns actual volume

    void play()  { this->setState(State::kPlaying); }
    void pause() { this->setState(State::kPaused); }
    void stop()  { this->setState(State::kStopped); }

    bool isPlaying() const { return this->state() == State::kPlaying; }
    bool isPaused() const  { return this->state() == State::kPaused; }
    bool isStopped() const { return this->state() == State::kStopped; }

protected:
    SkAudioPlayer() {}    // only called by subclasses

    virtual double onGetDuration() const = 0;
    virtual double onGetTime() const = 0;
    virtual double onSetTime(double) = 0;

    virtual State onSetState(State) = 0;
    virtual float onSetRate(float) = 0;
    virtual float onSetVolume(float) = 0;

private:
    State   fState = State::kStopped;
    float   fRate = 1.0f;
    float   fVolume = 1.0f;
};
