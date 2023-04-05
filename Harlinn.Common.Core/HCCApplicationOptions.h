#pragma once
#ifndef __HCCAPPLICATIONOPTIONS_H__
#define __HCCAPPLICATIONOPTIONS_H__

#include <HCCDef.h>
#include <HCCLoggerBackendOptions.h>

namespace Harlinn::Common::Core
{
    class ApplicationOptions
    {
        Logging::BackendOptions loggingBackendOptions_;
    public:
        ApplicationOptions()
        { }

        ApplicationOptions( const Logging::BackendOptions& loggingBackendOptions )
            : loggingBackendOptions_( loggingBackendOptions )
        {
        }

        ApplicationOptions( const ApplicationOptions& other ) = delete;
        ApplicationOptions( ApplicationOptions&& other ) = delete;
        ApplicationOptions& operator = ( const ApplicationOptions& other ) = delete;
        ApplicationOptions& operator = ( ApplicationOptions&& other ) = delete;


        void Load( )
        {
            loggingBackendOptions_.Load( );
        }

        const Logging::BackendOptions& LoggingBackendOptions( ) const noexcept
        {
            return loggingBackendOptions_;
        }


    };
}

#endif
