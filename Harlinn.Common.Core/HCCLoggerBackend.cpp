#include "pch.h"
#include <HCCLoggerBackend.h>
#include <HCCEnvironment.h>

namespace Harlinn::Common::Core::Logging
{
    // ------------------------------------------------------------------------
    //  BackendLogger
    // ------------------------------------------------------------------------
    __declspec( thread ) BackendLogger* BackendLogger::threadInstance_ = nullptr;

    BackendLogger* BackendLogger::Instance( )
    {
        if ( threadInstance_ )
        {
            return threadInstance_;
        }
        else
        {
            Backend* backend = Backend::Instance( );
            if ( backend )
            {
                auto result = backend->GetThreadLogger( );
                threadInstance_ = result;
                return result;
            }
            return nullptr;
        }

    }


    

    // ------------------------------------------------------------------------
    //  Backend
    // ------------------------------------------------------------------------

    static size_t receivedBytes = 0;
    static size_t receivedRecordCount = 0;

    HCC_EXPORT Backend* Backend::instance_ = nullptr;

    Backend::Backend( const std::shared_ptr<BackendOptions>& options )
        : Base( L"Logging::Backend" ), options_( options ), processInfo_( BackendProcessInfo::Create( ) ), bufferManager_( this )
    {
        instance_ = this;
    }
    Backend::~Backend( )
    {
        instance_ = nullptr;
        for ( auto& threadData : loggers_ )
        {
            if ( threadData.logger_ )
            {
                auto tmp = threadData.logger_;
                threadData.logger_ = nullptr;
                delete tmp;
            }
        }
    }

    void Backend::ProcessMessage( const MessageType& message )
    {
        Base::ProcessMessage( message );
        auto messageType = message->MessageType( );
        switch ( messageType )
        {
            case BackendMessageType::ProcessBuffer:
            {
                auto* processBufferMessage = static_cast< ProcessBufferMessage* >( message.get() );
                if ( processBufferMessage->Value() )
                {
                    ProcessBuffer( processBufferMessage->Value( ) );
                }
                break;
            }
        }
    }

    void Backend::ProcessBuffer( BackendBuffer* buffer )
    {
        receivedBytes += buffer->size( );
        receivedRecordCount += buffer->RecordCount( );
        buffer->Release( );
    }


    void Backend::Start( )
    {
        Base::Start( );
    }

    void Backend::Stop( )
    {
        Base::Stop( );
        double mega = static_cast<double>( receivedBytes ) / ( 1024.0 * 1024.0 );
        printf( "Backend received %zu records, %f mega bytes (%zu bytes)\n", receivedRecordCount, mega, receivedBytes );
    }

    BackendLogger* Backend::GetThreadLogger( )
    {
        UInt32 threadId = CurrentThread::Id( );
        std::unique_lock lock( criticalSection_ );
        auto it = std::lower_bound( loggers_.begin( ), loggers_.end( ), threadId, []( const ThreadData& threadData, UInt32 threadId ) 
        {
            return threadData.threadId_ < threadId;
        } );
        if ( it != loggers_.end( ) && it->threadId_ == threadId )
        {
            return it->logger_;
        }
        auto enabledLevels = options_->EnabledLevels( );
        auto result = new BackendLogger( enabledLevels, this );
        ThreadData threadData{ threadId, result };
        loggers_.insert( it, threadData );
        return result;
    }


}