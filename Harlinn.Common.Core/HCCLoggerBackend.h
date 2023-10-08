#pragma once
#ifndef __HCCLOGGERBACKEND_H__
#define __HCCLOGGERBACKEND_H__

#include <HCCLoggerBackendOptions.h>
#include <HCCLoggerBackendBuffer.h>
#include <HCCLoggerBackendDataTypes.h>
#include <HCCLogger.h>
#include <HCCBinaryWriter.h>
#include <HCCActiveObject.h>
#include <HCCGuid.h>


namespace Harlinn::Common::Core::Logging
{
    

    class BackendStream
    {
        Backend* backend_;
        BackendBuffer* buffer_ = nullptr;
        UInt64 bufferCount_ = 0;
        UInt64 bufferRecordCount_ = 0;
        UInt64 recordStart_;
    public:
        BackendStream( Backend* backend )
            : backend_( backend )
        {
            
            buffer_ = Allocate( );
        }
    private:
        BackendBuffer* Allocate(  );
        void Free( BackendBuffer* buffer );

        // Transfers ownership of the buffer to the queue
        void Post( BackendBuffer* buffer );
    public:
        void BeginRecord( const LogSite* site )
        {
            recordStart_ = buffer_->size( );
            BackendStreamRecordHeader header{ 0, site, __rdtsc( ) };
            Write( &header, sizeof( header ) );
            bufferRecordCount_++;
        }
        void EndRecord( )
        {
            UInt32 recordSize = static_cast<UInt32>(buffer_->size( ) - recordStart_) - sizeof( UInt32 );
            buffer_->WriteRecordSize( recordStart_, recordSize );
        }
    private:
        void PostCurrentBufferAndAllocateNew( )
        {
            if ( bufferRecordCount_ )
            {
                if ( recordStart_ != buffer_->size( ) ) [[likely]]
                {
                    auto nextBuffer = Allocate( );
                    nextBuffer->TakeStartOfRecordFrom( buffer_, recordStart_ );
                    buffer_->SetRecordCount( bufferRecordCount_ - 1 );
                    Post( buffer_ );
                    buffer_ = nextBuffer;
                    bufferRecordCount_ = 1;
                }
                else
                {
                    buffer_->SetRecordCount( bufferRecordCount_ );
                    Post( buffer_ );
                    buffer_ = Allocate( );
                    bufferRecordCount_ = 0;
                }
            }
        }
    public:

        void Flush( )
        {
            if ( bufferRecordCount_ )
            {
                buffer_->SetRecordCount( bufferRecordCount_ );
                Post( buffer_ );
                buffer_ = Allocate( );
                bufferRecordCount_ = 0;
            }
        }


        Int64 Write( const void* buffer, size_t bufferSize )
        {
            if ( buffer_->HasCapacity( bufferSize ) ) [[likely]]
            {
                return buffer_->Write( buffer, bufferSize );
            }
            else
            {
                PostCurrentBufferAndAllocateNew( );
                return buffer_->Write( buffer, bufferSize );
            }
        }

    };

    namespace Writers
    {
        class BackendWriter
        {
            using WriterType = IO::BinaryWriter<BackendStream>;

            BackendStream stream_;
            WriterType writer_;
        public:
            BackendWriter( Backend* backend )
                : stream_( backend ), writer_( stream_ )
            {
            }

            void Flush( )
            {
                stream_.Flush( );
            }


            template<typename ...Args>
            void WriteLogRecord( const LogSite* site, Args&& ...args ) noexcept
            {
                stream_.BeginRecord( site );
                Persistent::Write( writer_, std::forward<Args>( args )... );
                stream_.EndRecord( );
            }
        };

    }

    class BackendLogger : public Logger<Writers::BackendWriter, BuildOptions<Level::Default> >
    {
    public:
        static constexpr bool HasFixedSizeOptimization = true;
        using Base = Logger<Writers::BackendWriter, BuildOptions<Level::Default> >;
    private:
        static __declspec(thread) BackendLogger* threadInstance_;
    public:

        BackendLogger( Level enabledLevels, Backend* backend )
            : Base( enabledLevels, backend )
        { }

        HCC_EXPORT static BackendLogger* Instance( );
    };



    namespace Internal
    {
        class BackendQueue;
    }

    enum class BackendMessageType
    {
        Unknown,
        /// <summary>
        /// Tell the backend object to exit its
        /// background processing thread.
        /// </summary>
        Stop,

        /// <summary>
        /// Param1: Id of thread that has terminated
        /// </summary>
        ThreadDetached,

        /// <summary>
        /// Param1: pointer to reference counted BackendBuffer*
        /// </summary>
        ProcessBuffer
    };

    using BackendMessage = Concurrency::Messages::Message<BackendMessageType>;
    
    template<BackendMessageType messageId>
    using SimpleBackendMessage = Concurrency::Messages::SimpleMessage<BackendMessageType, messageId>;
    
    template<typename ValueT, BackendMessageType messageId>
    using SimpleBackendValueMessage = Concurrency::Messages::SimpleValueMessage<ValueT, BackendMessageType, messageId>;

    using ProcessBufferMessage = SimpleBackendValueMessage<BackendBuffer*, BackendMessageType::ProcessBuffer>;



    class Backend : public Concurrency::ActiveObject<std::shared_ptr<BackendMessage>>
    {
        friend class BackendLogger;
    public:
        using Base = Concurrency::ActiveObject<std::shared_ptr<BackendMessage>>;
    private:
        HCC_EXPORT static Backend* instance_;
        std::shared_ptr<BackendOptions> options_;
        BackendProcessInfo processInfo_;
        BackendBufferManager bufferManager_;

        struct ThreadData
        {
            UInt32 threadId_;
            BackendLogger* logger_;
        };
        CriticalSection criticalSection_;
        Vector<ThreadData> loggers_;
    public:
        HCC_EXPORT Backend( const std::shared_ptr<BackendOptions>& options );
        HCC_EXPORT ~Backend( );

        static Backend* Instance( )
        {
            return instance_;
        }


        HCC_EXPORT void Start( );
        HCC_EXPORT void Stop( );

        // Transfers ownership of the buffer to the queue
        void Post( BackendBuffer* buffer )
        {
            auto message = std::make_shared< ProcessBufferMessage >( buffer );
            PostMessage( message );
        }


        HCC_EXPORT virtual void ProcessMessage( const MessageType& message ) override;
    protected:
        virtual bool IsStopMessage( const MessageType& message ) const noexcept override
        {
            return message->MessageType( ) == BackendMessageType::Stop;
        }
        virtual void PostStopMessage( ) override
        {
            auto message = std::make_shared< SimpleBackendMessage<BackendMessageType::Stop > >( );
            PostMessage( message );
        }
    protected:
    private:
        void ProcessBuffer( BackendBuffer* buffer );
    public:
        BackendBuffer* Allocate( UInt32 threadId, UInt64 sequenceNumber )
        {
            return bufferManager_.Allocate( threadId, sequenceNumber );
        }
        void Free( BackendBuffer* buffer )
        {
            bufferManager_.Free( buffer );
        }
    private:
        HCC_EXPORT BackendLogger* GetThreadLogger( );
    };

    inline BackendBuffer* BackendStream::Allocate( )
    {
        auto threadId = (UInt32)CurrentThread::EnvironmentBlock( )->ClientId.Thread;
        auto result = backend_->Allocate( threadId, bufferCount_ + 1 );
        bufferCount_++;
        return result;
    }
    inline void BackendStream::Free( BackendBuffer* buffer )
    {
        backend_->Free( buffer );
    }

    inline void BackendStream::Post( BackendBuffer* buffer )
    {
        backend_->Post( buffer );
    }

}

#endif
