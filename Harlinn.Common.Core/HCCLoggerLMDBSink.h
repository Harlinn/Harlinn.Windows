#pragma once
#ifndef __HCCLOGGERLMDBSINK_H__
#define __HCCLOGGERLMDBSINK_H__

#include <HCCLoggerLMDBSinkOptions.h>
#include <HCCActiveObject.h>

namespace Harlinn::Common::Core::Logging::Sinks
{


    class LMDBSink : public ActiveObject<LMDBSink>
    {
    public:
        using Base = ActiveObject<LMDBSink>;
    private:
        LMDBSinkOptions options_;
    public:
        LMDBSink()
        { }

        LMDBSink( const LMDBSinkOptions& options )
            : options_( options )
        {
        }


        HCC_EXPORT void Start( );
        HCC_EXPORT void Stop( );

        HCC_EXPORT void Process( const Message& message ) noexcept;
    };
}

#endif
