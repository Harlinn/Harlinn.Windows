#pragma once
#ifndef __HCCACTIVEOBJECT_H__
#define __HCCACTIVEOBJECT_H__

#include <HCCThread.h>
#include <HCCIOCompletionPort.h>

namespace Harlinn::Common::Core
{

    namespace ActiveObjectMessageIds
    {
        constexpr UInt64 Stop = 1;
        constexpr UInt64 Last = Stop;
    }

#ifdef ACTIVEOBJECT_USES_IOCOMPLETIONPORT
    template<typename DerivedT>
    class ActiveObject : public IO::IOCompletionPort
    {
    public:
        using Base = IO::IOCompletionPort;
        using DerivedType = DerivedT;
        using Message = Base::Message;
    private:
        EventWaitHandle stopEvent_;
        Thread backgroundThread_;
    public:
        ActiveObject()
            : Base(1), stopEvent_(false)
        { }

        using Base::Post;
        void Post( UInt64 messageId, OVERLAPPED* requestData = nullptr )
        {
            Base::Post( 0, reinterpret_cast<void*>( messageId ), requestData );
        }


        void Start( )
        {
            auto* stopEvent = &stopEvent_;
            DerivedType* self = static_cast<DerivedType*>( this );
            backgroundThread_ = Thread( [stopEvent, self]( )
            {
                Message message;
                while ( self->Dequeue( message, INFINITE ) )
                {
                    auto messageId = message.Id( );
                    if ( messageId != ActiveObjectMessageIds::Stop )
                    {
                        self->Process( message );
                    }
                    else
                    {
                        break;
                    }
                }
                stopEvent->Signal( );
            } );
        }
        void Stop( )
        {
            if ( backgroundThread_ )
            {
                if ( backgroundThread_.IsStillActive( ) )
                {
                    Post( ActiveObjectMessageIds::Stop );
                    stopEvent_.Wait( );
                }
            }
        }
    };
#else

    template<typename DerivedT>
    class ActiveObject : public SimpleConcurrentQueue<IO::IOCompletionPort::Message, 10*1024 >
    {
    public:
        using Base = SimpleConcurrentQueue<IO::IOCompletionPort::Message, 10 * 1024 >;
        using DerivedType = DerivedT;
        using Message = IO::IOCompletionPort::Message;
    private:
        EventWaitHandle stopEvent_;
        Thread backgroundThread_;
    public:
        ActiveObject( )
            : stopEvent_( false )
        {
        }

        void Post( DWORD numberOfBytesTransferred, void* data, OVERLAPPED* overlapped )
        {
            Message message( numberOfBytesTransferred, data, overlapped );
            Base::Push( message );
        }

        void Post( const Message& message ) const
        {
            Post( message.numberOfBytesTransferred_, message.data_, message.overlapped_ );
        }

        void Post( UInt64 messageId, OVERLAPPED* requestData = nullptr )
        {
            Post( 0, reinterpret_cast<void*>( messageId ), requestData );
        }

        bool Dequeue( Message& message, DWORD timeoutInMillis ) const
        {
            auto result = Pop( message );
            return result;
        }

        Message Dequeue( DWORD timeoutInMillis ) const
        {
            Message message;
            Dequeue( message, timeoutInMillis );
            return message;
        }


        void Start( )
        {
            auto* stopEvent = &stopEvent_;
            DerivedType* self = static_cast<DerivedType*>( this );
            backgroundThread_ = Thread( [stopEvent, self]( )
            {
                Message message;
                while ( self->Pop( message ) )
                {
                    auto messageId = message.Id( );
                    try
                    {
                        self->Process( message );
                    }
                    catch( ... )
                    { }
                    if ( messageId == ActiveObjectMessageIds::Stop )
                    {
                        break;
                    }
                }
                stopEvent->Signal( );
            } );
        }
        void Stop( )
        {
            if ( backgroundThread_ )
            {
                if ( backgroundThread_.IsStillActive( ) )
                {
                    Post( ActiveObjectMessageIds::Stop );
                    stopEvent_.Wait( );
                }
            }
        }
    };
#endif
}

#endif
