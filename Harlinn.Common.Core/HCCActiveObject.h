#pragma once
#ifndef __HCCACTIVEOBJECT_H__
#define __HCCACTIVEOBJECT_H__

#include <HCCThread.h>
#include <HCCIOCompletionPort.h>

namespace Harlinn::Common::Core
{
#ifdef USES_OLD_ACTIVEOBJECT
    namespace ActiveObjectMessageIds
    {
        constexpr UInt64 Stop = 1;
        constexpr UInt64 Last = Stop;
    }

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
#else
    namespace Concurrency
    {
        template<typename MessageT>
        class ActiveObjectMessageEventArgs
        {
        public:
            using MessageType = MessageT;
        private:
            const MessageType& message_;
        public:
            ActiveObjectMessageEventArgs( const MessageType& message )
                : message_( message )
            {
            }

            const MessageType& Message( ) const noexcept
            {
                return message_;
            }
        };

        class ActiveObjectExceptionEventArgs
        {
        public:

        private:
            const std::exception& exception_;
            const WideString& message_;
        public:
            ActiveObjectExceptionEventArgs( const std::exception& exception, const WideString& message )
                : exception_( exception ), message_( message )
            {
            }

            const std::exception& Exception( ) const noexcept
            {
                return exception_;
            }

            const WideString& Message( ) const noexcept
            {
                return message_;
            }
        };


        namespace Messages
        {
            template<typename MessageIdT>
            class Message : public std::enable_shared_from_this<Message<MessageIdT>>
            {
            public:
                using MessageIdType = MessageIdT;
            private:
                MessageIdType messageType_;
            protected:
                Message( MessageIdType messageType )
                    : messageType_( messageType )
                {
                }
            public:
                virtual ~Message( ) = default;

                constexpr MessageIdType MessageType( ) const noexcept
                {
                    return messageType_;
                }
            };

            template<typename MessageIdT, MessageIdT messageId>
            class SimpleMessage : public Message<MessageIdT>
            {
            public:
                using Base = Message<MessageIdT>;
                SimpleMessage( )
                    : Base( messageId )
                {
                }
            };

            template<typename ValueT, typename MessageIdT, MessageIdT messageId>
            class SimpleValueMessage : public Message<MessageIdT>
            {
            public:
                using Base = Message<MessageIdT>;
                using value_type = ValueT;
                using ValueType = ValueT;
            private:
                ValueType value_;
            public:
                SimpleValueMessage( ValueType value )
                    : Base( messageId ), value_( value )
                {
                }

                ValueType Value( ) const
                {
                    return value_;
                }
            };
        }


        template<typename MessageT, size_t maxQueueSize = 10 * 1024>
        class ActiveObject;

        template<typename MessageT, size_t maxQueueSize = 10 * 1024>
        class ActiveObjectBase
        {
            template<typename MessageT, size_t maxQueueSize>
            friend class ActiveObject;
        public:
            using MessageType = MessageT;
            using ConcurrentQueue = SimpleConcurrentQueue<MessageT, maxQueueSize>;
            template<typename CallbackT>
            using Event = boost::signals2::signal<CallbackT>;
        private:
            ConcurrentQueue messages_;

            WideString threadName_;
            std::atomic<bool> started_;
            std::atomic<bool> stopped_;
        public:
            Event<void( ActiveObjectBase*, const ActiveObjectMessageEventArgs<MessageType>& )> OnProcessMessage;
            Event<void( ActiveObjectBase*, const ActiveObjectExceptionEventArgs& )> OnException;

            ActiveObjectBase( const WideString& threadName )
                : threadName_( threadName )
            {
            }

        protected:
            virtual bool IsStopMessage( const MessageType& message ) const noexcept = 0;
            virtual void PostStopMessage( ) = 0;
        public:
            const WideString& ThreadName( ) const noexcept
            {
                return threadName_;
            }

            bool Started( ) const noexcept
            {
                return started_;
            }

            bool Stopped( ) const noexcept
            {
                return stopped_;
            }


            virtual void Start( ) = 0;
            virtual void Stop( ) = 0;

            virtual bool PostMessage( const MessageType& message )
            {
                if ( messages_.IsClosed( ) == false )
                {
                    messages_.Push( message );
                    return true;
                }
                else
                {
                    return false;
                }
            }

        protected:
            virtual void ProcessMessage( const MessageType& message )
            {
                ActiveObjectMessageEventArgs eventArgs( message );
                OnProcessMessage( this, eventArgs );
            }

            /// <summary>
            /// Provides an opportunity to implement any initialization
            /// that needs to be performed in the context of the worker 
            /// thread of the active object before it starts the message
            /// loop.
            /// </summary>
            virtual void BeforeProcessMessages( )
            {
                started_ = true;
            }

            void ProcessMessages( )
            {
                while ( true )
                {
                    try
                    {
                        MessageType message;
                        messages_.Pop( message );
                        if ( this->IsStopMessage( message ) == false )
                        {
                            ProcessMessage( message );
                        }
                        else
                        {
                            break;
                        }
                    }
                    catch ( std::exception& ex )
                    {
                        auto message = Format( L"Exception caught in {}", CURRENT_FUNCTION );
                        this->HandleException( ex, message );
                    }
                }
            }


            /// <summary>
            /// Provides an opportunity to implement any cleanup
            /// that needs to be performed in the context of the worker 
            /// thread of the active object after the message loop exits.
            /// </summary>
            virtual void AfterProcessMessages( )
            {
            }


            virtual void Run( EventWaitHandle& manualEventWaitHandle )
            {
                this->BeforeProcessMessages( );
                try
                {
                    manualEventWaitHandle.Signal( );
                    ProcessMessages( );
                }
                catch ( ... )
                {
                    this->AfterProcessMessages( );
                    throw;
                }
                this->AfterProcessMessages( );
            }

            virtual void HandleException( const std::exception& error, const WideString& message )
            {
                if ( OnException.num_slots( ) )
                {
                    ActiveObjectExceptionEventArgs eventAregs( error, message );
                    OnException( this, eventAregs );
                }
            }
        };

        template<typename MessageT, size_t maxQueueSize>
        class ActiveObject : public ActiveObjectBase<MessageT, maxQueueSize>, public std::enable_shared_from_this<ActiveObject<MessageT, maxQueueSize>>
        {
            Thread thread_;
        public:
            using Base = ActiveObjectBase<MessageT, maxQueueSize>;
            using ESFT = std::enable_shared_from_this < ActiveObject<MessageT, maxQueueSize> >;
            ActiveObject( const WideString& threadName )
                : Base( threadName )
            {
            }

            virtual ~ActiveObject( ) = default;

            virtual void Start( ) override
            {
                EventWaitHandle manualEventWaitHandle( true );
                auto self = ESFT::shared_from_this( );
                thread_ = Thread( [ self, &manualEventWaitHandle ]
                    {
                        const auto& threadName = self->ThreadName( );
                        CurrentThread::SetDescription( threadName.c_str( ) );
                        self->Run( manualEventWaitHandle );
                    } );
                manualEventWaitHandle.Wait( );
            }
            virtual void Stop( ) override
            {
                if ( Base::stopped_ )
                    return;
                Base::stopped_ = true;
                this->PostStopMessage( );
                Base::messages_.Close( );
                thread_.Wait( );
            }

        };
    }
#endif
}

#endif
