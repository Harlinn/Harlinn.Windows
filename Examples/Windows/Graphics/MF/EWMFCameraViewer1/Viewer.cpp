/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include "Viewer.h"

//
//  Viewer constructor - instantiates internal objects and initializes MF
//
Viewer::Viewer(HWND videoWindow)
    : videoDisplayWindow_(videoWindow),
    state_(PlayerState::Closed),
    closeCompleteEvent_(false)
{
}



Viewer::~Viewer(void)
{
    CloseSession();
}


//
// Receive asynchronous event.
//
HRESULT Viewer::Invoke(IMFAsyncResult* asyncResult) noexcept
{

    if (!asyncResult)
    {
        return E_UNEXPECTED;
    }

    std::lock_guard lock(criticalSection_);
    try
    {
        // Get the event from the event queue.
        auto event = session_.EndGetEvent(asyncResult);

        // If the player is not closing, process the media event - if it is, do nothing.
        bool playerNoClosing = false;
        if (state_ != PlayerState::Closing)
        {
            playerNoClosing = ProcessMediaEvent(event);
        }

        // If the media event is MESessionClosed, it is guaranteed to be the last event.  If
        // the event is MESessionClosed, ProcessMediaEvent() will return S_FALSE.  In that 
        // case do not request the next event - otherwise tell the media session that this 
        // player is the object that will handle the next event in the queue.
        if (playerNoClosing)
        {
            session_.BeginGetEvent(this);
        }
    }
    HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
}



//
//  Called by Invoke() to do the actual event processing, and determine what, if anything,
//  needs to be done.  Returns S_FALSE if the media event type is MESessionClosed.
//
bool Viewer::ProcessMediaEvent(const MFMediaEvent& mediaEvent)
{
    // Not closing
    bool result = true;

    // Get the event type.
    auto eventType = mediaEvent.GetType();

    // Get the event status. If the operation that triggered the event did
    // not succeed, the status is a failure code.
    auto hrStatus = mediaEvent.GetStatus();

    // Check if the async operation succeeded.
    HCC_COM_CHECK_HRESULT(hrStatus);

    // Switch on the event type. Update the internal state of the Viewer as needed.
    if (eventType == MESessionTopologyStatus)
    {
        // Get the status code.
        auto topoStatus = mediaEvent.GetUINT32(MF_EVENT_TOPOLOGY_STATUS);

        if (topoStatus == MF_TOPOSTATUS_READY)
        {
            state_ = PlayerState::Stopped;
            OnTopologyReady();
        }
    }
    else if (eventType == MEEndOfPresentation)
    {
        state_ = PlayerState::Stopped;
    }
    else if (eventType == MESessionClosed)
    {
        // signal to anybody listening that the session is closed
        closeCompleteEvent_.Signal();
        result = false;
    }
    return result;
}




//
// OpenURL is the main initialization function that triggers bulding of the core
// MF components.
//
void Viewer::OpenURL(PCWSTR sURL)
{
    std::lock_guard lock(criticalSection_);

    try
    {
        // create a media session if one doesn't exist already
        if (session_ == nullptr)
        {
            CreateSession();
        }

        // build the topology.  Here we are using the TopoBuilder helper class.
        topologyBuilder_.RenderURL(WideString(sURL), videoDisplayWindow_);

        // get the topology from the TopoBuilder
        auto& topology = topologyBuilder_.GetTopology();

        // add the topology to the internal queue of topologies associated with this session
        session_.SetTopology(0, topology);

        // If a brand new topology was just created, set the player state to "open pending"
        // - not playing yet, but ready to begin.
        if (state_ == PlayerState::Ready)
        {
            state_ = PlayerState::OpenPending;
        }
    }
    catch (...)
    {
        state_ = PlayerState::Closed;
        throw;
    }
}


//
//  Starts playback from paused or stopped state.
//
void Viewer::Play()
{
    std::lock_guard lock(criticalSection_);

    // make sure everything is in the right state
    if (state_ != PlayerState::Paused && state_ != PlayerState::Stopped)
    {
        HCC_COM_CHECK_HRESULT(MF_E_INVALIDREQUEST);
    }

    // make sure the session has been created
    if (session_ == nullptr)
    {
        HCC_COM_CHECK_HRESULT(E_UNEXPECTED);
    }

    // start playback
    StartPlayback();

    // if we got here, everything was properly started
    state_ = PlayerState::Started;

}


//
//  Pauses playback.
//
void Viewer::Pause(void)
{
    std::lock_guard lock(criticalSection_);

    // pause makes sense only if playback has started
    if (state_ != PlayerState::Started)
    {
        HCC_COM_CHECK_HRESULT(MF_E_INVALIDREQUEST);
    }

    // make sure the session has been created
    if (session_ == nullptr)
    {
        HCC_COM_CHECK_HRESULT(E_UNEXPECTED);
    }

    // pause
    session_.Pause();

    // if we got here, everything is properly paused
    state_ = PlayerState::Paused;
}

//
//  Repaints the video window - called from main windows message loop when WM_PAINT
// is received.
//
void Viewer::Repaint()
{
    if (videoDisplay_)
    {
        videoDisplay_.RepaintVideo();
    }
}

void Viewer::Resize(const Size& newSize)
{
    if (videoDisplay_)
    {
        RECT rect(0, 0, newSize.Width(), newSize.Height());
        videoDisplay_.SetVideoPosition(nullptr, &rect);
    }

}


//
// Handler for MESessionTopologyReady event - starts video playback.
//
void Viewer::OnTopologyReady()
{
    // release any previous instance of the interface held by videoDisplay_
    videoDisplay_.ResetPtr();

    // Ask the session for the IMFVideoDisplayControl interface. This interface is 
    // implemented by the EVR (Enhanced Video Renderer) and is exposed by the media 
    // session as a service.  The session will query the topology for the right 
    // component and return this EVR interface.  The interface will be used to tell the
    // video to repaint whenever the hosting window receives a WM_PAINT window message.
    videoDisplay_ = session_.GetService<MFVideoDisplayControl>(MR_VIDEO_RENDER_SERVICE);

    // since the topology is ready, start playback
    Play();
}



//
//  Creates a new instance of the media session.
//
void Viewer::CreateSession()
{
    std::lock_guard lock(criticalSection_);

    // close the session if one is already created
    CloseSession();

    if (state_ != PlayerState::Closed)
    {
        HCC_COM_CHECK_HRESULT(E_UNEXPECTED);
    }

    // Create the media session.
    session_ = MFMediaSession::Create();

    state_ = PlayerState::Ready;

    // designate this class as the one that will be handling events from the media 
    // session
    session_.BeginGetEvent(this);
}


//
//  Closes the media session, blocking until the session closure is complete
//
void Viewer::CloseSession()
{
    bool waitForCloseEvent = false;
    {
        std::lock_guard lock(criticalSection_);
        state_ = PlayerState::Closing;

        // release the video display object
        videoDisplay_.ResetPtr();

        // Call the asynchronous Close() method and then wait for the close
        // operation to complete on another thread
        if (session_ != nullptr)
        {
            waitForCloseEvent = true;
            session_.Close();
        }
    }

    if (waitForCloseEvent)
    {
        // Begin waiting for the Win32 close event, fired in CPlayer::Invoke(). The 
        // close event will indicate that the close operation is finished, and the 
        // session can be shut down.
        closeCompleteEvent_.Wait(5000);
    }

    // Shut down the media session. (Synchronous operation, no events.)  Releases all of
    // the internal session resources.
    if (session_ != nullptr)
    {
        session_.Shutdown();
        // release the session
        session_.ResetPtr();
    }
    state_ = PlayerState::Closed;

}


//
//  Start playback from the current position.
//
void Viewer::StartPlayback()
{
    PropertyVariant varStart;

    // If Start fails later, we will get an MESessionStarted event with an error code, 
    // and will update our state. Passing in GUID_NULL and VT_EMPTY indicates that
    // playback should start from the current position.
    session_.Start(&GUID_NULL, &varStart);
}
