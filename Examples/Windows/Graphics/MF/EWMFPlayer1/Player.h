#pragma once

#include <HCCSync.h>
#include <HCCComImpl.h>
#include <HWMediaFoundation.h>

#include "TopoBuilder.h"

enum class PlayerState
{
    // No session.
    Closed = 0,
    // Session was created, ready to open a file.
    Ready,
    // Session is opening a file.
    OpenPending,
    // Session is playing a file.
    Started,
    // Session is paused.
    Paused,
    // Session is stopped (ready to play).
    Stopped,
    // Application has closed the session, but is waiting for MESessionClosed.
    Closing
};

//  Player class implements the MediaSession functionality and hides it from a calling 
//  application.
class Player : public Com::IUknownImpl<Player, IMFAsyncCallback>
{
public:
    using Base = Com::IUknownImpl<Player, IMFAsyncCallback>;
private:
    CriticalSection criticalSection_;

    TopologyBuilder topologyBuilder_;

    MFMediaSession session_;
    MFVideoDisplayControl videoDisplay_;

    // Video window.
    HWND videoDisplayWindow_;
    // Current state of the media session.
    PlayerState state_;

    // event fired when session colse is complete
    EventWaitHandle closeCompleteEvent_;

public:
    Player(HWND videoWindow);
    ~Player();

    // Playback control
    void OpenURL(PCWSTR sURL);
    void Play();
    void Pause();
    PlayerState GetState() const { return state_; }

    // Video functionality
    void Repaint();
    void Resize(const Size& newSize);
    BOOL HasVideo() const 
    { 
        return videoDisplay_ != nullptr;
    }

    void Close()
    {
        CloseSession();
    }

    //
    // IMFAsyncCallback implementation.
    //
    // Skip the optional GetParameters() function - it is used only in advanced players.
    // Returning the E_NOTIMPL error code causes the system to use default parameters.
    STDMETHODIMP GetParameters(DWORD *pdwFlags, DWORD *pdwQueue) noexcept override
    { 
        return E_NOTIMPL; 
    }

    // Main MF event handling function
    STDMETHODIMP Invoke(IMFAsyncResult* pAsyncResult) noexcept override;

        

protected:

    // internal initialization
    void Initialize();

    // private session and playback controlling functions
    void CreateSession();
    void CloseSession();
    void StartPlayback();

    // MF event handling functionality
    bool ProcessMediaEvent(const MFMediaEvent& mediaEvent);
    
    // Media event handlers
    void OnTopologyReady();

        
};