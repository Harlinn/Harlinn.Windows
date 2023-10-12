#pragma once
#ifndef __HCCACTIVEOBJECT_H__
#define __HCCACTIVEOBJECT_H__

#include <HCCThread.h>
#include <HCCConcurrentQueue.h>
#include <HCCMemory.h>

namespace Harlinn::Common::Core::Concurrency
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


#define USES_SIMPLECONCURRENTQUEUE 1
    template<typename MessageT, size_t maxQueueSize = 10 * 1024>
    class ActiveObjectBase
    {
        template<typename MessageT, size_t maxQueueSize>
        friend class ActiveObject;
    public:
        using MessageType = MessageT;
#ifdef USES_SIMPLECONCURRENTQUEUE
        using ConcurrentQueue = SimpleConcurrentQueue<MessageT, maxQueueSize>;
#else
        using ConcurrentQueue = BlockingConcurrentQueue<MessageT>;
#endif
        template<typename CallbackT>
        using Event = boost::signals2::signal<CallbackT>;
    private:
        ConcurrentQueue messages_;

        WideString threadName_;
        std::atomic<bool> started_;
        std::atomic<bool> stopped_;
        std::atomic<size_t> messagesPosted_;
        std::atomic<size_t> messagesProcessed_;
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

        size_t MessagesPosted( ) const
        {
            return messagesPosted_;
        }
        size_t MessagesProcessed( ) const
        {
            return messagesProcessed_;
        }


        virtual void Start( ) = 0;
        virtual void Stop( ) = 0;

        virtual bool PostMessage( const MessageType& message )
        {

            if ( messages_.IsClosed( ) == false )
            {
#ifdef USES_SIMPLECONCURRENTQUEUE
                messages_.Push( message );
#else
                messages_.enqueue( message );
#endif
                ++messagesPosted_;
                return true;
            }
            else
            {
                return false;
            }
        }

        virtual bool PostMessage( MessageType&& message )
        {

            if ( messages_.IsClosed( ) == false )
            {
#ifdef USES_SIMPLECONCURRENTQUEUE
                messages_.Push( std::move( message ) );
#else
                messages_.enqueue( std::move( message ) );
#endif
                ++messagesPosted_;
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
#ifdef USES_SIMPLECONCURRENTQUEUE
                    auto popped = messages_.Pop( message );
                    if ( popped )
                    {
                        ++messagesProcessed_;
                        if ( this->IsStopMessage( message ) == false )
                        {
                            ProcessMessage( message );
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
#else
                    messages_.wait_dequeue( message );
                    if ( this->IsStopMessage( message ) == false )
                    {
                        ProcessMessage( message );
                    }
                    else
                    {
                        break;
                    }
#endif
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
            //auto self = ESFT::shared_from_this( );
            ActiveObject* activeObjectPtr = this;
            thread_ = Thread( [ activeObjectPtr, &manualEventWaitHandle ]
                {
                    auto activeObject = activeObjectPtr->shared_from_this( );
                    const auto& threadName = activeObject->ThreadName( );
                    CurrentThread::SetDescription( threadName.c_str( ) );
                    activeObject->Run( manualEventWaitHandle );
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
