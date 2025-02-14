/*
   Copyright 2024-2025 Espen Harlinn

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

#include "pch.h"
#include <HCCLoggerImpl.h>
#include <HCCEnvironment.h>
#include <HCCApplication.h>
#include <HCCRdtscConverter.h>

namespace Harlinn::Common::Core::Logging
{
    namespace
    {
        
        RdtscConverter rdtscConverter;
    }

    // ------------------------------------------------------------------------
    //  ThreadLogger
    // ------------------------------------------------------------------------
    thread_local ThreadLogger* ThreadLogger::threadInstance_ = nullptr;

    ThreadLogger* ThreadLogger::Instance( ) noexcept
    {
        if ( threadInstance_ )
        {
            return threadInstance_;
        }
        else
        {
            auto logManager = LogManager::Instance( );
            if ( logManager )
            {
                auto result = logManager->GetThreadLogger( );
                threadInstance_ = result;
                return result;
            }
            return nullptr;
        }
    }
    

    // ------------------------------------------------------------------------
    //  LogManager
    // ------------------------------------------------------------------------

    namespace
    {
        CriticalSection criticalSection;
        std::atomic<bool> logManagerStopped;
        UInt64 logManagerThreadId = 0xFFFFFFFFFFFFFFFF;
        std::shared_ptr<LoggerOptions> loggerOptions;
    }
    HCC_EXPORT std::shared_ptr<LogManager> LogManager::instance_;

    LogManager::LogManager( const std::shared_ptr<LoggerOptions>& options )
        : Base( WideString(L"Logging::LogManager") ), options_( options ), processInfo_( Types::ProcessInfo::Create( ) ), bufferManager_( this )
    {

    }

    LogManager::LogManager( )
        : LogManager( std::make_shared<LoggerOptions>( ) )
    {
    }
    LogManager::~LogManager( )
    {
        puts( "LogManager destroyed." );
    }

    LogManager* LogManager::Instance( )
    {
        if ( logManagerStopped == false )
        {
            if ( !instance_ )
            {
                std::lock_guard guard( criticalSection );
                if ( !instance_ )
                {
                    if ( loggerOptions )
                    {
                        auto instance = std::make_shared<LogManager>( loggerOptions );
                        instance_ = instance;
                    }
                    else
                    {
                        auto instance = std::make_shared<LogManager>( );
                        instance_ = instance;
                    }
                }

            }
            return instance_.get();
        }
        return nullptr;
    }

    void LogManager::SetOptions( const std::shared_ptr<LoggerOptions>& options )
    {
        std::lock_guard guard( criticalSection );
        if ( options )
        {
            loggerOptions = options;
            if ( instance_ )
            {
                instance_->options_ = options;
            }
        }
    }


    void LogManager::ProcessMessage( const MessageType& message )
    {
        Base::ProcessMessage( message );
        auto messageType = message->MessageType( );
        switch ( messageType )
        {
            case LogManagerMessageType::ProcessBuffer:
            {
                this->ProcessBufferMessage( std::static_pointer_cast< LogManagerProcessBufferMessage >( message ) );
            }
            break;
            case LogManagerMessageType::ThreadDetached:
            {
                this->ProcessThreadDetachedMessage( std::static_pointer_cast< LogManagerThreadDetachedMessage >( message ) );
            }
            break;
            case LogManagerMessageType::AddBufferHandler:
            {
                this->ProcessAddBufferHandlerMessage( std::static_pointer_cast< LogManagerAddBufferHandlerMessage >( message ) );
            }
            break;
            case LogManagerMessageType::RemoveBufferHandler:
            {
                this->ProcessRemoveBufferHandlerMessage( std::static_pointer_cast< LogManagerRemoveBufferHandlerMessage >( message ) );
            }
            break;
            case LogManagerMessageType::AddRecordHandler:
            {
                this->ProcessAddRecordHandlerMessage( std::static_pointer_cast< LogManagerAddRecordHandlerMessage >( message ) );
            }
            break;
            case LogManagerMessageType::RemoveRecordHandler:
            {
                this->ProcessRemoveRecordHandlerMessage( std::static_pointer_cast< LogManagerRemoveRecordHandlerMessage >( message ) );
            }
            break;
            case LogManagerMessageType::RetrieveStatistics:
            {
                this->ProcessRetrieveStatisticsMessage( std::static_pointer_cast< LogManagerRetrieveStatisticsMessage >( message ) );
            }
            break;
            case LogManagerMessageType::Timer:
            {
                this->ProcessTimerMessage( std::static_pointer_cast< LogManagerTimerMessage >( message ) );
            }
            break;
        }
    }

    void LogManager::BeforeProcessMessages( )
    {
        Base::BeforeProcessMessages( );
        timerQueue_ = TimerQueue::Create( );
        
        timerQueueTimer_ = timerQueue_.CreateTimer( options_->PollInterval( ), TimerQueueTimerFlags::Default, [ ]( )
            {
                auto logManger = LogManager::Instance( );
                if ( logManger && logManagerStopped == false )
                {
                    logManger->PostTimerMessage( );
                }
            } );

        logManagerThreadId = CurrentThread::Id( );
        logManagerThreadId_ = logManagerThreadId;
    }

    void LogManager::AfterProcessMessages( )
    {
        timerQueueTimer_.Close( );
        timerQueue_.Close( );
    }

    void LogManager::ProcessBufferMessage( const std::shared_ptr<LogManagerProcessBufferMessage>& message )
    {
        auto buffer = message->Value( );
        if ( buffer )
        {
            bytesReceived_ += buffer->size( );
            recordsProcessed_ += buffer->RecordCount( );

            buffer->SetRdtscCyclesPerTick( rdtscConverter.RdtscCyclesPerTick( ) );

            size_t handlerCount = handlers_.size( );
            for ( int i = 0; i < handlerCount; ++i )
            {
                auto& handler = handlers_[ i ];
                handler->Process( buffer );
            }
        }
    }

    void LogManager::PostThreadDetachedMessage( )
    {
        UInt64 threadId = CurrentThread::Id( );
        
        if ( Application::MainThreadId( ) != threadId && logManagerThreadId != threadId )
        {
            ThreadLogger::threadInstance_ = nullptr;
            auto message = std::make_shared< LogManagerThreadDetachedMessage >( static_cast<UInt32>( threadId ) );
            PostMessage( message );
        }
    }

    void LogManager::ProcessThreadDetachedMessage( const std::shared_ptr<LogManagerThreadDetachedMessage>& message )
    {
        auto detachedThreadId = message->Value( );
        std::unique_lock lock( criticalSection_ );
        auto it = std::lower_bound( loggers_.begin( ), loggers_.end( ), detachedThreadId, []( const ThreadData& threadData, UInt32 threadId )
            {
                return threadData.ThreadId( ) < threadId;
            } );
        if ( it != loggers_.end( ) && it->ThreadId( ) == detachedThreadId )
        {
            ThreadLogger* logger = it->Logger( );
            if ( logger )
            {
                logger->Flush( FlushType::Final );
            }
            loggers_.erase( it );
        }
    }

    void LogManager::PostAddBufferHandlerMessage( const std::shared_ptr<BufferHandler>& handler )
    {
        if ( handler )
        {
            if ( Started( ) && Stopped() == false )
            {
                auto message = std::make_shared< LogManagerAddBufferHandlerMessage >( handler );
                PostMessage( message );
            }
            else
            {
                auto it = std::find( handlers_.begin( ), handlers_.end( ), handler );
                if ( it == handlers_.end( ) )
                {
                    handlers_.emplace_back( handler );
                }
            }
        }
    }
    
    void LogManager::ProcessAddBufferHandlerMessage( const std::shared_ptr<LogManagerAddBufferHandlerMessage>& message )
    {
        auto handler = message->Value( );
        if ( handler )
        {
            auto it = std::find( handlers_.begin( ), handlers_.end( ), handler );
            if ( it == handlers_.end( ) )
            {
                handlers_.emplace_back( handler );
            }
        }
    }
    
    void LogManager::PostRemoveBufferHandlerMessage( const std::shared_ptr<BufferHandler>& handler )
    {
        if ( handler )
        {
            if ( Started( ) && Stopped( ) == false )
            {
                auto message = std::make_shared< LogManagerRemoveBufferHandlerMessage >( handler );
                PostMessage( message );
            }
            else
            {
                auto it = std::find( handlers_.begin( ), handlers_.end( ), handler );
                if ( it != handlers_.end( ) )
                {
                    handlers_.erase( it );
                }
            }
        }
    }
    
    void LogManager::ProcessRemoveBufferHandlerMessage( const std::shared_ptr<LogManagerRemoveBufferHandlerMessage>& message )
    {
        auto handler = message->Value( );
        if ( handler )
        {
            auto it = std::find( handlers_.begin( ), handlers_.end( ), handler );
            if ( it != handlers_.end( ) )
            {
                handlers_.erase( it );
            }
        }
    }

    
    void LogManager::PostAddRecordHandlerMessage( const std::shared_ptr<RecordHandler>& handler )
    {
        if ( handler )
        {
            if ( Started( ) && Stopped( ) == false )
            {
                auto message = std::make_shared< LogManagerAddRecordHandlerMessage >( handler );
                PostMessage( message );
            }
            else
            {
                if ( !runtimeBufferConverter_ )
                {
                    runtimeBufferConverter_ = std::make_shared<RuntimeBufferConverter>( logSiteExtractor_, consoleLogger_ );
                    handlers_.push_back( runtimeBufferConverter_ );
                }
                runtimeBufferConverter_->Add( handler );
            }
        }
    }

    void LogManager::ProcessAddRecordHandlerMessage( const std::shared_ptr<LogManagerAddRecordHandlerMessage>& message )
    {
        auto handler = message->Value( );
        if ( handler )
        {
            if ( !runtimeBufferConverter_ )
            {
                runtimeBufferConverter_ = std::make_shared<RuntimeBufferConverter>( logSiteExtractor_, consoleLogger_ );
                handlers_.push_back( runtimeBufferConverter_ );
            }
            runtimeBufferConverter_->Add( handler );
        }
    }

    void LogManager::PostRemoveRecordHandlerMessage( const std::shared_ptr<RecordHandler>& handler )
    {
        if ( handler )
        {
            if ( Started( ) && Stopped( ) == false )
            {
                auto message = std::make_shared< LogManagerRemoveRecordHandlerMessage >( handler );
                PostMessage( message );
            }
            else
            {
                if ( runtimeBufferConverter_ )
                {
                    runtimeBufferConverter_->Remove( handler );
                }
            }
        }
    }

    void LogManager::ProcessRemoveRecordHandlerMessage( const std::shared_ptr<LogManagerRemoveRecordHandlerMessage>& message )
    {
        auto handler = message->Value( );
        if ( handler )
        {
            if ( runtimeBufferConverter_ )
            {
                runtimeBufferConverter_->Remove( handler );
            }
        }
    }
    

    std::shared_ptr<LogManagerStatistics> LogManager::Statistics( )
    {
        if ( Started( ) && Stopped( ) == false )
        {
            auto message = std::make_shared<LogManagerRetrieveStatisticsMessage>( );
            PostMessage( message );
            auto reply = message->Reply( );
            return reply;
        }
        else
        {
            auto statistics = std::make_shared<LogManagerStatistics>( this, bufferManager_.Statistics(), loggers_.size( ) );
            return statistics;
        }
    }
    
    void LogManager::ProcessRetrieveStatisticsMessage( const std::shared_ptr<LogManagerRetrieveStatisticsMessage>& message )
    {
        auto statistics = std::make_shared<LogManagerStatistics>( this, bufferManager_.Statistics( ), loggers_.size( ) );
        message->SetReply( statistics );
    }

    void LogManager::PostTimerMessage( )
    {
        if ( Started( ) && Stopped( ) == false )
        {
            auto message = std::make_shared<LogManagerTimerMessage>( );
            PostMessage( message );
        }
    }
    
    void LogManager::ProcessTimerMessage( const std::shared_ptr<LogManagerTimerMessage>& message )
    {
        auto now = DateTime::UtcNow( );
        UInt64 rdtscCycle = __rdtsc( );
        auto maxAge = options_->PollInterval( );

        std::unique_lock lock( criticalSection_ );

        for ( auto& entry : loggers_ )
        {
            entry.Logger( )->Poll( now, rdtscCycle, maxAge );
        }
    }





    bool LogManager::Start( const TimeSpan& timeout )
    {
        return Base::Start( timeout );
    }

    bool LogManager::Stop( const TimeSpan& timeout )
    {
        if ( ThreadLogger::threadInstance_ )
        {
            ThreadLogger::threadInstance_->Flush( FlushType::Final );
        }
        logManagerStopped = true;
        ThreadLogger::threadInstance_ = nullptr;
        auto result = Base::Stop( timeout );
        size_t recordsPosted = RecordsPosted( );
        size_t recordsProcessed = RecordsProcessed( );
        size_t bytesReceived = BytesReceived( );

        double mega = static_cast<double>( bytesReceived ) / ( 1024.0 * 1024.0 );
        size_t messagesPosted = MessagesPosted( );
        size_t messagesProcessed = MessagesProcessed( );
        printf( "LogManager posted %zu records, received %zu records, %f mega bytes (%zu bytes) - Messages posted: %zu, Messages processed: %zu \n", recordsPosted, recordsProcessed, mega, bytesReceived, messagesPosted, messagesProcessed );
        loggers_.clear( );
        instance_ = nullptr;
        return result;
    }

    ThreadLogger* LogManager::GetThreadLogger( )
    {
        UInt32 threadId = CurrentThread::Id( );
        std::unique_lock lock( criticalSection_ );
        auto it = std::lower_bound( loggers_.begin( ), loggers_.end( ), threadId, []( const ThreadData& threadData, UInt32 threadId ) 
        {
            return threadData.ThreadId( ) < threadId;
        } );
        if ( it != loggers_.end( ) && it->ThreadId( ) == threadId )
        {
            return it->Logger( );
        }
        if ( logManagerStopped == false )
        {
            auto enabledLevels = options_->EnabledLevels( );
            auto threadLogger = std::make_shared<ThreadLogger>( enabledLevels, Self( ) );
            auto result = threadLogger.get( );
            ThreadData threadData{ threadId, std::move( threadLogger ) };
            loggers_.emplace( it, std::move( threadData ) );
            return result;
        }
        return nullptr;
    }
}

namespace Harlinn::Common::Core::CurrentThread
{
    HCC_EXPORT void FlushLogger( Logging::FlushType flushType ) noexcept
    {
        try
        {
            if ( Logging::ThreadLogger::threadInstance_ )
            {
                Logging::ThreadLogger::threadInstance_->Flush( flushType );
            }
        }
        catch(...)
        { }
    }

    HCC_EXPORT Logging::ThreadLogger* ThreadLogger( ) noexcept
    {
        return Logging::ThreadLogger::Instance( );
    }

}
