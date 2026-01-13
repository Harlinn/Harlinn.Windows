#pragma once
#ifndef __HCCACTIVEOBJECT_H__
#define __HCCACTIVEOBJECT_H__
/*
   Copyright 2024-2026 Espen Harlinn

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


#include <HCCThread.h>
#include <HCCConcurrentQueue.h>
#include <HCCMemory.h>

namespace Harlinn::Common::Core::Concurrency
{
    /// <summary>
    /// The default implementation of ActiveObjectBase&lt;MessageT,maxQueueSize&gt;::ProcessMessage(const MessageType& message)
    /// calls each of the callbacks registered with the OnProcessMessage signal. 
    /// </summary>
    /// <typeparam name="MessageT">
    /// The base type of the message type for ActiveObjectBase.
    /// </typeparam>
    template<typename MessageT>
    class ActiveObjectMessageEventArgs
    {
    public:
        using MessageType = MessageT;
    private:
        const MessageType& message_;
    public:
        /// <summary>
        /// constructs a new instance of an ActiveObjectMessageEventArgs object.
        /// </summary>
        /// <param name="message">
        /// The message passed to ActiveObjectBase&lt;MessageT,maxQueueSize&gt;::ProcessMessage(const MessageType& message)
        /// </param>
        ActiveObjectMessageEventArgs( const MessageType& message )
            : message_( message )
        {
        }

        const MessageType& Message( ) const noexcept
        {
            return message_;
        }
    };

    /// <summary>
    /// <para>
    /// When an exception is caught in the message processing loop in
    /// ActiveObjectBase&lt;MessageT,maxQueueSize&gt;::ProcessMessages( ) the function
    /// calls HandleException( const std::exception& error, const WideString& message )
    /// passing information about the exception.
    /// </para>
    /// <para>
    /// The default implementation of HandleException calls each of the callbacks
    /// registered with the OnException signal passing an instance of ActiveObjectExceptionEventArgs
    /// containing the information about the exception. 
    /// </para>
    /// </summary>
    class ActiveObjectExceptionEventArgs
    {
    public:

    private:
        const std::exception& exception_;
        const WideString& message_;
    public:
        /// <summary>
        /// Constructs a new instance of an ActiveObjectExceptionEventArgs object.
        /// </summary>
        /// <param name="exception">A reference to the caught exception.</param>
        /// <param name="message">A reference to the message passed to HandleException.</param>
        ActiveObjectExceptionEventArgs( const std::exception& exception, const WideString& message )
            : exception_( exception ), message_( message )
        {
        }

        /// <summary>
        /// The exception passed to HandleException.
        /// </summary>
        /// <returns>The exception</returns>
        const std::exception& Exception( ) const noexcept
        {
            return exception_;
        }

        /// <summary>
        /// The message passed to HandleException.
        /// </summary>
        /// <returns>
        /// The message.
        /// </returns>
        const WideString& Message( ) const noexcept
        {
            return message_;
        }
    };


    namespace Messages
    {
        /// <summary>
        /// A template that may be used as a base class for message
        /// types that will be posted to the active object.
        /// </summary>
        /// <typeparam name="MessageIdT">
        /// The type used to discriminate between derived message types.
        /// </typeparam>
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

        /// <summary>
        /// A template that may be used to implement 
        /// whose meaning can be fully determined the value
        /// messageId template parameter.
        /// </summary>
        /// <typeparam name="MessageIdT">
        /// The type used to discriminate between derived message types.
        /// </typeparam>
        /// <typeparam name="messageId"></typeparam>
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


        /// <summary>
        /// A template that may be used to implement messages
        /// that requests a single object from the active object.
        /// </summary>
        template<typename ReplyT, typename MessageIdT, MessageIdT messageId>
        class SimpleRequestMessage : public Message<MessageIdT>
        {
        public:
            using Base = Message<MessageIdT>;
            using reply_type = ReplyT;
            using ReplyType = ReplyT;
        private:
            std::promise<ReplyType> promise_;
        public:
            SimpleRequestMessage( ) 
                : Base( messageId )
            { }
        protected:
            SimpleRequestMessage( MessageIdT msgId )
                : Base( msgId )
            { }
        public:
            std::future<ReplyType> GetFuture( )
            {
                return promise_.get_future( );
            }
            void SetResult( const ReplyType& model )
            {
                promise_.set_value( model );
            }

            void SetException( )
            {
                try
                {
                    promise_.set_exception( std::current_exception( ) );
                }
                catch ( ... )
                {
                }
            }

        };


        /// <summary>
        /// A template that may be used to implement messages
        /// that pass a single value to the active object.
        /// </summary>
        /// <typeparam name="ValueT"></typeparam>
        /// <typeparam name="MessageIdT"></typeparam>
        /// <typeparam name="messageId"></typeparam>
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

        /// <summary>
        /// A template that may be used to implement messages
        /// that pass a single value to the active object, and 
        /// requests a reply in the form of a single object 
        /// from the active object.
        /// </summary>
        template<typename ValueT, typename ReplyT, typename MessageIdT, MessageIdT messageId>
        class SimpleValueRequestMessage : public SimpleRequestMessage<ReplyT, MessageIdT, messageId>
        {
        public:
            using Base = SimpleRequestMessage<ReplyT, MessageIdT, messageId>;
            using value_type = ValueT;
            using ValueType = ValueT;
        private:
            ValueType value_;
        public:
            SimpleValueRequestMessage( const ValueType& value )
                : Base( messageId ), value_( value )
            { }
            SimpleValueRequestMessage( ValueType&& value )
                : Base( messageId ), value_( std::move( value ) )
            { }

            ValueType Value( ) const
            {
                return value_;
            }
        };

    }

    



    template<typename MessageT, size_t maxQueueSize = 10 * 1024>
    class ActiveObject;


#define USES_SIMPLECONCURRENTQUEUE 1
    /// <summary>
    /// The base template class for the active object type.
    /// </summary>
    /// <typeparam name="MessageT">
    /// The message type for the active object.
    /// </typeparam>
    /// <typeparam name="maxQueueSize">
    /// The maximum queue size for the active object.
    /// </typeparam>
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
        /// <summary>
        /// Register callbacks with this signal to process messages passed to the
        /// active object.
        /// </summary>
        Event<void( ActiveObjectBase*, const ActiveObjectMessageEventArgs<MessageType>& )> OnProcessMessage;
        /// <summary>
        /// Register callbacks with this signal to process exceptions caught in the message event loop
        /// of the active object.
        /// </summary>
        Event<void( ActiveObjectBase*, const ActiveObjectExceptionEventArgs& )> OnException;

        /// <summary>
        /// Constructs a new active object
        /// </summary>
        /// <param name="threadName">
        /// This is the thread name for the message processing thread
        /// created by the active object. 
        /// </param>
        ActiveObjectBase( const WideString& threadName )
            : threadName_( threadName )
        {
        }

    protected:
        /// <summary>
        /// IsStopMessage must be implemented by derived classes
        /// to determine if a message is a stop message causing the
        /// event loop to be terminated.
        /// </summary>
        /// <param name="message"></param>
        /// <returns></returns>
        virtual bool IsStopMessage( const MessageType& message ) const noexcept = 0;
        /// <summary>
        /// PostStopMessage must be implemented by derived classes.
        /// The implementation must post a message the will cause
        /// IsStopMessage to return true.
        /// </summary>
        virtual void PostStopMessage( ) = 0;
    public:
        const WideString& ThreadName( ) const noexcept
        {
            return threadName_;
        }

        /// <summary>
        /// Determine whether the active object has started the message processing thread.
        /// </summary>
        /// <returns>true if the message processing thread has started.</returns>
        bool Started( ) const noexcept
        {
            return started_;
        }

        /// <summary>
        /// Determine whether the active object has exited the message processing thread.
        /// </summary>
        /// <returns>
        /// true if the message processing thread has exited.
        /// </returns>
        bool Stopped( ) const noexcept
        {
            return stopped_;
        }

        /// <summary>
        /// Retrieves the number of messages posted to the active object.
        /// </summary>
        /// <returns>
        /// The number of messages posted to the active object.
        /// </returns>
        size_t MessagesPosted( ) const
        {
            return messagesPosted_;
        }
        /// <summary>
        /// Retrieves the number of messages processed by the message processing loop.
        /// </summary>
        /// <returns>
        /// The number of messages processed by the message processing loop.
        /// </returns>
        size_t MessagesProcessed( ) const
        {
            return messagesProcessed_;
        }

        /// <summary>
        /// Start must be implemented by derived classes. The implementation
        /// should only return when it is able to determine that the 
        /// thread has successfully started.
        /// </summary>
        virtual bool Start( const TimeSpan& timeout ) = 0;
        /// <summary>
        /// Stop must be implemented by derived classes. The implementation
        /// should wait a reasonable amount time for the message processing
        /// thread to exit.
        /// </summary>
        virtual bool Stop( const TimeSpan& timeout ) = 0;

        /// <summary>
        /// Posts a message to the active object.
        /// </summary>
        /// <param name="message">
        /// The message to post.
        /// </param>
        /// <returns>
        /// false if the message queue is closed, indicating that the 
        /// active object has shut down, or is about to do so - otherwise true. 
        /// </returns>
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



        /// <summary>
        /// Posts a message, by moving it, to the active object.
        /// </summary>
        /// <param name="message">
        /// The message to post.
        /// </param>
        /// <returns>
        /// false if the message queue is closed, indicating that the 
        /// active object has shut down, or is about to do so - otherwise true. 
        /// </returns>
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
        /// <summary>
        /// <para>
        /// Called by the active object to process a single message.
        /// </para>
        /// <para>
        /// When overridden by a derived class, the implementation
        /// should call the implementation of the base class.
        /// </para>
        /// </summary>
        /// <param name="message">The message to process.</param>
        virtual void ProcessMessage( const MessageType& message )
        {
            ActiveObjectMessageEventArgs eventArgs( message );
            OnProcessMessage( this, eventArgs );
        }

        /// <summary>
        /// <para>
        /// Provides an opportunity to implement any initialization
        /// that needs to be performed in the context of the worker 
        /// thread of the active object before it starts the message
        /// loop.
        /// </para>
        /// <para>
        /// BeforeProcessMessages is called from Run, and if an exception is
        /// thrown it will not be caught unless the thread catches the exception.
        /// </para>
        /// <para>
        /// If overridden by a derived class, the implementation must call the
        /// implementation provided by the base class.
        /// </para>
        /// </summary>
        virtual void BeforeProcessMessages( )
        {
            started_ = true;
        }

        /// <summary>
        /// This function implements the message processing loop.
        /// </summary>
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

        /// <summary>
        /// Run must be called by the thread that will be used to process
        /// messages for the active object.
        /// </summary>
        /// <param name="manualEventWaitHandle">
        /// An un-signalled manual reset event. This event will be signalled 
        /// to indicate that the active object is running its message processing
        /// loop.
        /// </param>
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

        /// <summary>
        /// Called when exceptions are caught in the message processing loop.
        /// </summary>
        /// <param name="error"></param>
        /// <param name="message"></param>
        virtual void HandleException( const std::exception& error, const WideString& message )
        {
            if ( OnException.num_slots( ) )
            {
                ActiveObjectExceptionEventArgs eventAregs( error, message );
                OnException( this, eventAregs );
            }
        }
    };

    /// <summary>
    /// Extends the ActiveObjectBase template, implementing the message 
    /// processing thread and the Start and Stop functions.
    /// </summary>
    /// <typeparam name="MessageT">
    /// The message type for the active object.
    /// </typeparam>
    /// <typeparam name="maxQueueSize">
    /// The maximum queue size for the active object.
    /// </typeparam>
    template<typename MessageT, size_t maxQueueSize>
    class ActiveObject : public ActiveObjectBase<MessageT, maxQueueSize>, public std::enable_shared_from_this<ActiveObject<MessageT, maxQueueSize>>
    {
        Thread thread_;
    public:
        static constexpr Int64 DefaultStartStopTimeoutInTicks = TimeSpan::TicksPerMinute * 10;
        using Base = ActiveObjectBase<MessageT, maxQueueSize>;
        using ESFT = std::enable_shared_from_this < ActiveObject<MessageT, maxQueueSize> >;
        /// <summary>
        /// Constructs a new instance of an ActiveObject object. 
        /// </summary>
        /// <param name="threadName">
        /// This is the thread name for the message processing thread
        /// created by the active object. 
        /// </param>
        ActiveObject( const WideString& threadName )
            : Base( threadName )
        {
        }

        virtual ~ActiveObject( ) = default;
        /// <summary>
        /// Starts the message processing thread.
        /// </summary>
        /// <param name="timeout">
        /// The maximum amount of time to wait for the message processing thread to
        /// start.
        /// </param>
        /// <returns>
        /// true if the message processing thread started in time, false otherwise.
        /// </returns>
        virtual bool Start( const TimeSpan& timeout ) override
        {
            EventWaitHandle manualEventWaitHandle( true );
            ActiveObject* activeObjectPtr = this;
            thread_ = Thread( [ activeObjectPtr, &manualEventWaitHandle ]
                {
                    try
                    {
                        auto activeObject = activeObjectPtr->shared_from_this( );
                        const auto& threadName = activeObject->ThreadName( );
                        CurrentThread::SetDescription( threadName.c_str( ) );
                        activeObject->Run( manualEventWaitHandle );
                    }
                    catch(...)
                    { }
                } );
            return manualEventWaitHandle.Wait( timeout );
        }

        /// <summary>
        /// Starts the message processing thread.
        /// </summary>
        /// <returns>
        /// true if the message processing thread started in time, false otherwise.
        /// </returns>
        bool Start( )
        {
            return this->Start( TimeSpan( DefaultStartStopTimeoutInTicks ) );
        }

        /// <summary>
        /// Stops the message processing thread by posting the stop message,
        /// closing the message queue, and waiting for the thread to exit.
        /// </summary>
        /// <param name="timeout">
        /// The maximum amount of time to wait for the message processing thread to
        /// exit.
        /// </param>
        /// <returns>
        /// true if the message processing thread has stopped, otherwise false.
        /// </returns>
        virtual bool Stop( const TimeSpan& timeout ) override
        {
            if ( Base::stopped_.exchange(true) )
            {
                return true;
            }
            this->PostStopMessage( );
            Base::messages_.Close( );
            return thread_.Wait( timeout );
        }

        /// <summary>
        /// Stops the message processing thread by posting the stop message,
        /// closing the message queue, and waiting for the thread to exit.
        /// </summary>
        /// <returns>
        /// true if the message processing thread has stopped, otherwise false.
        /// </returns>
        bool Stop( )
        {
            return this->Stop( TimeSpan( DefaultStartStopTimeoutInTicks ) );
        }

    };
}


#endif
