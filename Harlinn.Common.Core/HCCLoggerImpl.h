#pragma once
#ifndef __HCCLOGGERBACKEND_H__
#define __HCCLOGGERBACKEND_H__

#include <HCCLoggerOptions.h>
#include <HCCLoggerBuffer.h>
#include <HCCLoggerTypes.h>
#include <HCCLogger.h>
#include <HCCBinaryWriter.h>
#include <HCCActiveObject.h>
#include <HCCGuid.h>
#include <HCCPersistentPrinter.h>


namespace Harlinn::Common::Core::Logging::Internal
{
    /// <summary>
    /// RecordStream implements: 
    ///    Int64 Write( const void* buffer, size_t bufferSize );
    /// which is required by IO::BinaryWriter<> in ThreadWriter::WriteLogRecord
    /// 
    /// Instances of this class should not need any synchronization as 
    /// they are supposed to only be used by the ThreadWriter class.
    /// </summary>
    class RecordStream
    {
        std::shared_ptr<LogManager> logManager_;
        BufferPointer buffer_;
        UInt64 bufferCount_ = 0;
        UInt64 bufferRecordCount_ = 0;
        UInt64 recordStart_;
    public:
        RecordStream( const std::shared_ptr<LogManager>& logManager )
            : logManager_( logManager )
        {

            buffer_ = Allocate( );
        }
    private:
        BufferPointer Allocate( );
        //void Free( Buffer* buffer );

        // Transfers ownership of the buffer to the queue
        void Post( BufferPointer buffer );
        //void Post( BufferPointer&& buffer );
    public:
        void BeginRecord( const LogSite* site )
        {
            recordStart_ = buffer_->size( );
            RecordHeader header{ 0, site, __rdtsc( ) };
            constexpr size_t headerSize = sizeof( RecordHeader );
            if ( buffer_->FreeCapacity( ) > headerSize ) [[likely]]
            {
                buffer_->Write( &header, headerSize );
            }
            else
            {
                PostCurrentBufferAndAllocateNew( true );
                buffer_->Write( &header, headerSize );
            }
            bufferRecordCount_++;
        }
        void EndRecord( )
        {
            UInt32 recordSize = static_cast< UInt32 >( buffer_->size( ) - recordStart_ ) - sizeof( UInt32 );
            buffer_->WriteRecordSize( recordStart_, recordSize );
        }
    private:
        void EndRecord( size_t recordSize )
        {
            buffer_->WriteRecordSize( recordStart_, static_cast< UInt32 >( recordSize ) );
        }
        const LogSite* CurrentLogSite( ) const
        {
            return buffer_->GetLogSite( recordStart_ );
        }
        void PostCurrentBufferAndAllocateNew( bool lastRecordIsIncomplete )
        {
            if ( bufferRecordCount_ )
            {
                buffer_->SetLastRecordIsIncomplete( lastRecordIsIncomplete );
                buffer_->SetRecordCount( bufferRecordCount_ );
                auto newBuffer = Allocate( );
                //Post( std::move(buffer_) );
                Post( buffer_ );
                buffer_ = newBuffer;
                bufferRecordCount_ = 0;
            }
        }
    public:

        void Flush( Logging::FlushType flushType = Logging::FlushType::Normal )
        {
            if ( bufferRecordCount_ )
            {
                buffer_->SetRecordCount( bufferRecordCount_ );
                buffer_->SetLastRecordIsIncomplete( false );
                if ( flushType == FlushType::Final )
                {
                    buffer_->SetFinal( true );
                }
                auto newBuffer = Allocate( );
                // Post( std::move( buffer_ ) );
                Post( buffer_ );
                buffer_ = newBuffer;
                bufferRecordCount_ = 0;
            }
        }

        void Poll( DateTime now, UInt64 referenceRdtscCycle, TimeSpan maxAge )
        {
            if ( bufferRecordCount_ )
            {
                auto bufferTimestamp = buffer_->Timestamp( );
                if ( now > bufferTimestamp )
                {
                    auto age = now - bufferTimestamp;
                    if ( age >= maxAge )
                    {
                        Flush( FlushType::Poll );
                    }
                }
            }
            else
            {
                buffer_->SetTimestamp( now );
                buffer_->SetReferenceRdtscCycle( referenceRdtscCycle );
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
                const auto* logSite = CurrentLogSite( );
                const Byte* ptr = reinterpret_cast< const Byte* >( buffer );
                size_t remaining = bufferSize;
                while ( remaining )
                {
                    size_t currentFreeCapacity = buffer_->FreeCapacity( );
                    size_t numberOfBytesToCopyToBuffer = std::min( remaining, currentFreeCapacity );
                    buffer_->Write( ptr, numberOfBytesToCopyToBuffer );
                    EndRecord( numberOfBytesToCopyToBuffer );
                    ptr += numberOfBytesToCopyToBuffer;
                    remaining -= numberOfBytesToCopyToBuffer;
                    if ( remaining )
                    {
                        PostCurrentBufferAndAllocateNew( true );
                        buffer_->SetFirstRecordIsIncomplete( true );
                        BeginRecord( logSite );
                    }
                }
                return static_cast<Int64>(bufferSize);
            }
        }

    };
}

namespace Harlinn::Common::Core::Logging
{

    namespace Writers
    {
        /// <summary>
        /// This is the class that creates log entries for a single thread.
        /// 
        /// Flush may be called from another thread, but only after the
        /// thread has exited. 
        /// 
        /// Poll will be called from another thread, as the LogManager
        /// will periodically poll for buffers that contain log records
        /// older than maxAge.
        /// </summary>
        class ThreadWriter
        {
            using WriterType = IO::BinaryWriter<Internal::RecordStream>;

            Internal::RecordStream stream_;
            WriterType writer_;
            Spinlock spinlock_;
        public:
            ThreadWriter( const std::shared_ptr<LogManager>& logManager )
                : stream_( logManager ), writer_( stream_ )
            {
            }

            void Flush( FlushType flushType = FlushType::Normal )
            {
                std::lock_guard guard( spinlock_ );
                stream_.Flush( flushType );
            }


            void Poll( DateTime now, UInt64 referenceRdtscCycle, TimeSpan maxAge )
            {
                std::lock_guard guard( spinlock_ );
                stream_.Poll( now, referenceRdtscCycle, maxAge );
            }


            template<typename ...Args>
            void WriteLogRecord( const LogSite* site, Args&& ...args ) noexcept
            {
                std::lock_guard guard( spinlock_ );
                stream_.BeginRecord( site );
                Persistent::Write( writer_, std::forward<Args>( args )... );
                stream_.EndRecord( );
            }
        };

    }

    /// <summary>
    /// This is the class that implements the logging API.
    /// </summary>
    class ThreadLogger : public Logger<Writers::ThreadWriter, BuildOptions<Level::Default> >, public std::enable_shared_from_this<ThreadLogger>
    {
        // Needs to access threadInstance_
        friend void CurrentThread::FlushLogger( FlushType flushType ) noexcept;
        friend class LogManager;
    public:
        static constexpr bool HasFixedSizeOptimization = true;
        using Base = Logger<Writers::ThreadWriter, BuildOptions<Level::Default> >;
    private:
        static thread_local ThreadLogger* threadInstance_;
    public:

        ThreadLogger( Level enabledLevels, const std::shared_ptr<LogManager>& logManager )
            : Base( enabledLevels, logManager )
        {
        }

        /// <summary>
        /// Retrieves a pointer to the ThreadLogger for the current thread.
        /// </summary>
        /// <returns></returns>
        HCC_EXPORT static ThreadLogger* Instance( ) noexcept;
    };
    enum class LogManagerMessageType
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
        /// Param1: pointer to reference counted LogManagerBuffer*
        /// </summary>
        ProcessBuffer,

        AddBufferHandler,

        RemoveBufferHandler,

        AddRecordHandler,

        RemoveRecordHandler,

        RetrieveStatistics,

        Timer
    };

    using LogManagerMessage = Concurrency::Messages::Message<LogManagerMessageType>;
    
    template<LogManagerMessageType messageId>
    using SimpleLogManagerMessage = Concurrency::Messages::SimpleMessage<LogManagerMessageType, messageId>;
    
    template<typename ValueT, LogManagerMessageType messageId>
    using SimpleLogManagerValueMessage = Concurrency::Messages::SimpleValueMessage<ValueT, LogManagerMessageType, messageId>;

    


    using LogManagerStopMessage = SimpleLogManagerMessage<LogManagerMessageType::Stop>;
    using LogManagerProcessBufferMessage = SimpleLogManagerValueMessage<Internal::BufferPointer, LogManagerMessageType::ProcessBuffer>;
    
    using LogManagerThreadDetachedMessage = SimpleLogManagerValueMessage<UInt32, LogManagerMessageType::ThreadDetached>;
    using LogManagerAddBufferHandlerMessage = SimpleLogManagerValueMessage<std::shared_ptr<BufferHandler>, LogManagerMessageType::AddBufferHandler>;
    using LogManagerRemoveBufferHandlerMessage = SimpleLogManagerValueMessage<std::shared_ptr<BufferHandler>, LogManagerMessageType::RemoveBufferHandler>;

    using LogManagerAddRecordHandlerMessage = SimpleLogManagerValueMessage<std::shared_ptr<RecordHandler>, LogManagerMessageType::AddRecordHandler>;
    using LogManagerRemoveRecordHandlerMessage = SimpleLogManagerValueMessage<std::shared_ptr<RecordHandler>, LogManagerMessageType::RemoveRecordHandler>;


    class LogManagerStatistics : public std::enable_shared_from_this<LogManagerStatistics>
    {
    public:
        using BufferManagerStatisticsType = Internal::BufferManager::StatisticsType;
    private:
        size_t messagesPosted_ = 0;
        size_t messagesProcessed_ = 0;
        size_t recordsPosted_ = 0;
        size_t recordsProcessed_ = 0;
        size_t bytesReceived_ = 0;
        size_t activeThreadLoggers_ = 0;
        BufferManagerStatisticsType bufferManagerStatistics_;
    public:
        constexpr LogManagerStatistics( ) = default;
        inline LogManagerStatistics( LogManager* logManager, const BufferManagerStatisticsType& bufferManagerStatistics, size_t activeThreadLoggers );

        size_t MessagesPosted() const noexcept 
        { 
            return messagesPosted_; 
        }
        size_t MessagesProcessed() const noexcept 
        { 
            return messagesProcessed_; 
        }
        size_t RecordsPosted() const noexcept 
        { 
            return recordsPosted_; 
        }
        size_t RecordsProcessed() const noexcept 
        { 
            return recordsProcessed_; 
        }
        size_t BytesReceived( ) const noexcept 
        { 
            return bytesReceived_; 
        }

        size_t ActiveThreadLoggers( ) const noexcept
        {
            return activeThreadLoggers_;
        }

        const BufferManagerStatisticsType& BufferManagerStatistics( ) const noexcept
        {
            return bufferManagerStatistics_;
        }
    };

    inline [[nodiscard]] WideString ToWideString( const LogManagerStatistics& statistics )
    {
        auto bufferManagerStatistics = ToWideString( statistics.BufferManagerStatistics( ) );
        return Format( L"Active ThreadLoggers: {}, Messages Posted: {}, Messages Processed: {}, Records Posted: {}, Records Processed: {}, Bytes Received: {}, {}", statistics.ActiveThreadLoggers( ), statistics.MessagesPosted( ), statistics.MessagesProcessed( ), statistics.RecordsPosted( ), statistics.RecordsProcessed( ), statistics.BytesReceived( ), bufferManagerStatistics );
    }

    inline [[nodiscard]] AnsiString ToAnsiString( const LogManagerStatistics& statistics )
    {
        auto bufferManagerStatistics = ToAnsiString( statistics.BufferManagerStatistics() );
        return Format( "Active ThreadLoggers: {}, Messages Posted: {}, Messages Processed: {}, Records Posted: {}, Records Processed: {}, Bytes Received: {}, {}", statistics.ActiveThreadLoggers( ), statistics.MessagesPosted(), statistics.MessagesProcessed(), statistics.RecordsPosted(), statistics.RecordsProcessed(), statistics.BytesReceived(), bufferManagerStatistics );
    }

    inline [[nodiscard]] WideString ToWideString( const std::shared_ptr<LogManagerStatistics>& statistics )
    {
        if ( statistics )
        {
            return ToWideString( *statistics );
        }
        else
        {
            return L"<null>";
        }
    }
    inline [[nodiscard]] AnsiString ToAnsiString( const std::shared_ptr<LogManagerStatistics>& statistics )
    {
        if ( statistics )
        {
            return ToAnsiString( *statistics );
        }
        else
        {
            return "<null>";
        }
    }


    class LogManagerRetrieveStatisticsMessage : public SimpleLogManagerMessage<LogManagerMessageType::RetrieveStatistics>
    {
        std::promise< std::shared_ptr<LogManagerStatistics> > promise_;
    public:
        LogManagerRetrieveStatisticsMessage()
        { }


        std::shared_ptr<LogManagerStatistics> Reply( )
        {
            auto future = promise_.get_future( );
            return future.get( );
        }
        void SetReply( const std::shared_ptr<LogManagerStatistics>& reply )
        {
            promise_.set_value( reply );
        }
    };

    using LogManagerTimerMessage = SimpleLogManagerMessage<LogManagerMessageType::Timer>;




    class LogManager : public Concurrency::ActiveObject<std::shared_ptr<LogManagerMessage>>
    {
        friend class ThreadLogger;
        
    public:
        using Base = Concurrency::ActiveObject<std::shared_ptr<LogManagerMessage>>;
        using RuntimeBufferConverter = BufferConverter<LogSiteExtractor>;
    private:
        HCC_EXPORT static std::shared_ptr<LogManager> instance_;
        std::shared_ptr<LoggerOptions> options_;
        Types::ProcessInfo processInfo_;
        Internal::BufferManager bufferManager_;
        UInt64 logManagerThreadId_ = 0xFFFFFFFFFFFFFFFF;
        std::atomic<UInt64> recordsPosted_{};
        std::atomic<UInt64> recordsProcessed_{};
        std::atomic<UInt64> bytesReceived_{};
        TimerQueue timerQueue_;
        TimerQueueTimer timerQueueTimer_;
        LogSiteExtractor logSiteExtractor_;
        ConsoleLogger consoleLogger_{ Level::Default };

        class ThreadData
        {
            UInt32 threadId_ = 0;
            std::shared_ptr<ThreadLogger> logger_;
        public:
            ThreadData( ) = default;
            ThreadData( UInt32 threadId, std::shared_ptr<ThreadLogger>&& logger )
                : threadId_( threadId ), logger_( std::move( logger ) )
            { }

            ThreadData( UInt32 threadId, const std::shared_ptr<ThreadLogger>& logger )
                : threadId_( threadId ), logger_( logger )
            {
            }


            ThreadData( const ThreadData& ) = delete;
            ThreadData( ThreadData&& other ) noexcept
                : threadId_( other.threadId_ ), logger_( std::move( other.logger_ ) )
            {
            }

            ThreadData& operator = ( const ThreadData& ) = delete;
            ThreadData& operator = ( ThreadData&& other ) noexcept
            {
                threadId_ = other.threadId_; 
                std::swap( logger_, other.logger_ );
                return *this;
            }

            constexpr UInt32 ThreadId( ) const noexcept
            {
                return threadId_;
            }
            ThreadLogger* Logger( ) const noexcept
            {
                return logger_.get( );
            }

        };
        CriticalSection criticalSection_;
        std::vector<ThreadData> loggers_;
        std::vector<std::shared_ptr<BufferHandler>> handlers_;
        std::shared_ptr<RuntimeBufferConverter> runtimeBufferConverter_;
    public:
        HCC_EXPORT LogManager( );
        HCC_EXPORT LogManager( const std::shared_ptr<LoggerOptions>& options );
    public:
        HCC_EXPORT ~LogManager( );
        HCC_EXPORT static LogManager* Instance( );
        HCC_EXPORT static void SetOptions( const std::shared_ptr<LoggerOptions>& options );

        HCC_EXPORT void Start( );
        HCC_EXPORT void Stop( );

        std::shared_ptr<const LogManager> Self( ) const
        {
            return std::static_pointer_cast< const LogManager >( shared_from_this() );
        }
        std::shared_ptr<LogManager> Self( )
        {
            return std::static_pointer_cast< LogManager >( shared_from_this( ) );
        }


        UInt64 RecordsPosted( ) const noexcept
        {
            return recordsPosted_;
        }

        UInt64 RecordsProcessed( ) const noexcept
        {
            return recordsProcessed_;
        }

        UInt64 BytesReceived( ) const noexcept
        {
            return bytesReceived_;
        }

        



        // Transfers ownership of the buffer to the queue
        void Post( const Internal::BufferPointer buffer )
        {
            recordsPosted_ += buffer->RecordCount( );
            auto message = std::make_shared< LogManagerProcessBufferMessage >( buffer );
            PostMessage( message );
        }

        /*
        void Post( Internal::BufferPointer&& buffer )
        {
            recordsPosted_ += buffer->RecordCount( );
            auto message = std::make_shared< LogManagerProcessBufferMessage >( std::move( buffer ) );
            PostMessage( message );
        }
        */

        HCC_EXPORT virtual void ProcessMessage( const MessageType& message ) override;
    protected:
        virtual bool IsStopMessage( const MessageType& message ) const noexcept override
        {
            return message->MessageType( ) == LogManagerMessageType::Stop;
        }
        virtual void PostStopMessage( ) override
        {
            auto message = std::make_shared< SimpleLogManagerMessage<LogManagerMessageType::Stop > >( );
            PostMessage( message );
        }
        HCC_EXPORT virtual void BeforeProcessMessages( ) override;
        HCC_EXPORT virtual void AfterProcessMessages( ) override;
    protected:
        HCC_EXPORT virtual void ProcessBufferMessage( const std::shared_ptr<LogManagerProcessBufferMessage>& message );
    public:
        HCC_EXPORT void PostThreadDetachedMessage( );
    protected:
        HCC_EXPORT virtual void ProcessThreadDetachedMessage( const std::shared_ptr<LogManagerThreadDetachedMessage>& message );
    private:
        HCC_EXPORT void PostAddBufferHandlerMessage( const std::shared_ptr<BufferHandler>& handler );
    protected:
        HCC_EXPORT virtual void ProcessAddBufferHandlerMessage( const std::shared_ptr<LogManagerAddBufferHandlerMessage>& message );
    private:
        HCC_EXPORT void PostRemoveBufferHandlerMessage( const std::shared_ptr<BufferHandler>& handler );
    protected:
        HCC_EXPORT virtual void ProcessRemoveBufferHandlerMessage( const std::shared_ptr<LogManagerRemoveBufferHandlerMessage>& message );
    private:
        HCC_EXPORT void PostAddRecordHandlerMessage( const std::shared_ptr<RecordHandler>& handler );
    protected:
        HCC_EXPORT virtual void ProcessAddRecordHandlerMessage( const std::shared_ptr<LogManagerAddRecordHandlerMessage>& message );
    private:
        HCC_EXPORT void PostRemoveRecordHandlerMessage( const std::shared_ptr<RecordHandler>& handler );
    protected:
        HCC_EXPORT virtual void ProcessRemoveRecordHandlerMessage( const std::shared_ptr<LogManagerRemoveRecordHandlerMessage>& message );
    public:
        HCC_EXPORT std::shared_ptr<LogManagerStatistics> Statistics( );
    private:
        HCC_EXPORT void ProcessRetrieveStatisticsMessage( const std::shared_ptr<LogManagerRetrieveStatisticsMessage>& message );
    public:

    public:
        HCC_EXPORT void PostTimerMessage( );
    private:
        HCC_EXPORT void ProcessTimerMessage( const std::shared_ptr<LogManagerTimerMessage>& message );
    public:


        void Add( const std::shared_ptr<BufferHandler>& handler )
        {
            PostAddBufferHandlerMessage( handler );
        }
        void Remove( const std::shared_ptr<BufferHandler>& handler )
        {
            PostRemoveBufferHandlerMessage( handler );
        }
        void Add( const std::shared_ptr<RecordHandler>& handler )
        {
            PostAddRecordHandlerMessage( handler );
        }
        void Remove( const std::shared_ptr<RecordHandler>& handler )
        {
            PostRemoveRecordHandlerMessage( handler );
        }

    public:
        Internal::BufferPointer Allocate( UInt32 threadId, UInt64 sequenceNumber )
        {
            return bufferManager_.Allocate( threadId, sequenceNumber );
        }
        /*
        void Free( Internal::Buffer* buffer )
        {
            bufferManager_.Free( buffer );
        }
        */
    private:
        HCC_EXPORT ThreadLogger* GetThreadLogger( );
    };


    inline LogManagerStatistics::LogManagerStatistics( LogManager* logManager, const BufferManagerStatisticsType& bufferManagerStatistics, size_t activeThreadLoggers )
        : messagesPosted_( logManager->MessagesPosted() ), messagesProcessed_( logManager->MessagesProcessed() ), recordsPosted_( logManager->RecordsPosted() ), recordsProcessed_( logManager->RecordsProcessed() ), bytesReceived_( logManager->BytesReceived() ), activeThreadLoggers_( activeThreadLoggers ), bufferManagerStatistics_( bufferManagerStatistics )
    { }


    class Trace
    {
        static constexpr auto EmptyDescriptor = Persistent::Descriptor( );
        static constexpr char Entering[ ] = "Entering";
        static constexpr char Leaving[ ] = "Leaving";
        LogSite enteringSite_;
        LogSite leavingSite_;

    public:
        Trace( UInt32 line, UInt32 column, const char* file, const char* function ) noexcept
            : enteringSite_( Logging::Level::Entering, Entering, EmptyDescriptor, true, 0, line, column, file, function ),
              leavingSite_( Logging::Level::Leaving, Leaving, EmptyDescriptor, true, 0, line, column, file, function )
        {
            auto* logger = ThreadLogger::Instance( );
            if ( logger->IsTraceEnabled( ) )
            {
                logger->Entering( &enteringSite_ );
            }
        }

        ~Trace( )
        {
            auto* logger = ThreadLogger::Instance( );
            if ( logger->IsTraceEnabled( ) )
            {
                logger->Leaving( &leavingSite_ );
            }
        }

    };


    namespace Formatters
    {
        template<IO::StreamWriter OutputStreamT = IO::MemoryStream>
        class TextFormatter : public RecordHandler
        {
        public:
            using CharType = char;
            using OutputStreamType = OutputStreamT;
            using ArgmentsStreamType = IO::BufferStream;
            using ArgmentsReaderType = IO::BinaryReader<ArgmentsStreamType>;
        private:
            using ThreadKeyData = Internal::ThreadKeyData;
            struct ThreadData
            {
                // The number of LogRecord objects seen with Level Logging::Level::Entering
                // minus the number of LogRecord objects seen with Level Logging::Level::Leaving
                // for a thread
                Int32 TraceDepth = 0;
            };
            using ThreadDataMap = std::unordered_map<ThreadKeyData, std::unique_ptr<ThreadData>>;
            ThreadDataMap threadDataMap_;
            OutputStreamType& outputStream_;
            
        public:
            explicit TextFormatter( OutputStreamType& outputStream )
                : outputStream_( outputStream )
            { }

            virtual void Process( const LogRecord& logRecord ) noexcept override
            {
                HandleTraceDepth( logRecord );
                Write( logRecord );
            }

            virtual void Final( const Guid& processId, UInt32 threadId ) noexcept override
            {
                ThreadKeyData threadKeyData( processId, threadId );
                threadDataMap_.erase( threadKeyData );
            }
        private:
            void Write( const LogRecord& logRecord )
            {
                auto formatString = logRecord.FormatString( );
                auto argumentsDescriptor = logRecord.ArgumentsDescriptor( );
                auto argumentsData = logRecord.ArgumentsData( );

                ArgmentsStreamType argumentsStream( const_cast<Byte*>( argumentsData.data() ), argumentsData.size() );

                Persistent::Printer<CharType, ArgmentsStreamType, OutputStreamType> printer( formatString.data(), formatString.length(), argumentsDescriptor.data(), argumentsStream, outputStream_ );
                printer.Print( );
                outputStream_.Write( "\r\n", 2 );
            }

            void HandleTraceDepth( const LogRecord& logRecord )
            {
                auto level = logRecord.Level( );
                switch ( level )
                {
                    case Level::Entering:
                    {
                        ThreadKeyData threadKeyData( logRecord.ProcessId( ), logRecord.ThreadId( ) );
                        auto it = threadDataMap_.find( threadKeyData );
                        if ( it != threadDataMap_.end( ) )
                        {
                            auto& threadData = it->second;
                            ++threadData->TraceDepth;
                        }
                        else
                        {
                            auto threadData = std::make_unique<ThreadData>( );
                            threadData->TraceDepth = 1;
                            threadDataMap_.emplace( threadKeyData, std::move( threadData ) );
                        }
                    }
                    break;
                    case Level::Leaving:
                    {
                        ThreadKeyData threadKeyData( logRecord.ProcessId( ), logRecord.ThreadId( ) );
                        auto it = threadDataMap_.find( threadKeyData );
                        if ( it != threadDataMap_.end( ) )
                        {
                            auto& threadData = it->second;
                            --threadData->TraceDepth;
                        }
                    }
                    break;
                }
            }

        };
    }

    namespace Sinks
    {
        class TextSink : public RecordHandler
        {
            std::shared_ptr<TextSinkOptions> options_;
            IO::FileStream fileStream_;
            using FormatterType = Formatters::TextFormatter<IO::FileStream>;
            std::shared_ptr<FormatterType> formatter_;
        public:
            TextSink( const std::shared_ptr<TextSinkOptions>& options )
                : options_( options ), fileStream_( options->Filename(), IO::FileAccess::ReadWrite | IO::FileAccess::Append, IO::FileShare::Read, IO::FileMode::Append, IO::FileAttributes::Normal, IO::FileOptions::Default )
            { 
                formatter_ = std::make_shared<FormatterType>( fileStream_ );
            }

            virtual void Process( const LogRecord& logRecord ) noexcept override
            {
                formatter_->Process( logRecord );
            }

            virtual void Final( const Guid& processId, UInt32 threadId ) noexcept override
            {
                formatter_->Final( processId, threadId );
            }

        };
    }


}

namespace Harlinn::Common::Core::Logging::Internal
{

    inline BufferPointer RecordStream::Allocate( )
    {
        auto threadId = (UInt32)CurrentThread::EnvironmentBlock( )->ClientId.Thread;
        auto result = logManager_->Allocate( threadId, bufferCount_ + 1 );
        bufferCount_++;
        return result;
    }
    /*
    inline void RecordStream::Free( Buffer* buffer )
    {
        logManager_->Free( buffer );
    }
    */

    inline void RecordStream::Post( BufferPointer buffer )
    {
        logManager_->Post( buffer );
    }

    /*
    inline void RecordStream::Post( BufferPointer&& buffer )
    {
        logManager_->Post( std::move( buffer ) );
    }
    */

}


#endif
