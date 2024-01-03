#pragma once
#ifndef __HCCLOGGERLMDBSINK_H__
#define __HCCLOGGERLMDBSINK_H__
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
