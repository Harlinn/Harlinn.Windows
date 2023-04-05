#pragma once
#ifndef __HCCLOGGERBACKENDOPTIONS_H__
#define __HCCLOGGERBACKENDOPTIONS_H__

#include <HCCLoggerLMDBSinkOptions.h>
#include <HCCLoggerLevel.h>


namespace Harlinn::Common::Core::Logging
{
    class Backend;

    enum class BackendSinks : UInt32
    {
        None = 0,
        Console = 0x00000001,
        LMDB = 0x00000002,
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( BackendSinks, UInt32 );



    class BackendOptions
    {
        Level enabledLevels_ = Level::Default;
        BackendSinks enabledSinks_ = BackendSinks::None;
        //ConsoleSinkOptions consoleSinkOptions_;
        Sinks::LMDBSinkOptions lmdbSinkOptions_;
    public:
        BackendOptions()
        { }

        explicit BackendOptions( BackendSinks enabledSinks,  Level enabledLevels = Level::Default )
            : enabledLevels_( enabledLevels ), enabledSinks_(enabledSinks)
        {
        }


        void Load( )
        {
            lmdbSinkOptions_.Load( );
        }

        Level EnabledLevels( ) const noexcept
        {
            return enabledLevels_;
        }
        BackendSinks EnabledSinks( ) const noexcept
        {
            return enabledSinks_;
        }
        //ConsoleSinkOptions consoleSinkOptions_;
        const Sinks::LMDBSinkOptions& LMDBSinkOptions( ) const noexcept
        {
            return lmdbSinkOptions_;
        }

    };

}

#endif
