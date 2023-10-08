#pragma once
#ifndef __HCCLOGGERLMDBSINK_H__
#define __HCCLOGGERLMDBSINK_H__

#include <HCCLoggerLMDBSinkOptions.h>
#include <HCCActiveObject.h>

namespace Harlinn::Common::Core::Logging::Sinks
{
    enum class LMDBSinkMessageType
    {
        Unknown,
        Stop
    };

    using LMDBSinkMessage = Concurrency::Messages::Message<LMDBSinkMessageType>;
    template<LMDBSinkMessageType messageId>
    using SimpleMessage = Concurrency::Messages::SimpleMessage<LMDBSinkMessageType, messageId>;


    class LMDBSink : public Concurrency::ActiveObject<std::shared_ptr<LMDBSinkMessage>>
    {
    public:
        using Base = Concurrency::ActiveObject<std::shared_ptr<LMDBSinkMessage>>;
    private:
        LMDBSinkOptions options_;
    public:
        LMDBSink( const WideString& threadName )
            : Base( threadName )
        { }

        LMDBSink( const WideString& threadName, const LMDBSinkOptions& options )
            : Base( threadName ), options_( options )
        {
        }


        HCC_EXPORT void Start( );
        HCC_EXPORT void Stop( );

        HCC_EXPORT virtual void ProcessMessage( const MessageType& message ) override;
    };
}

#endif
