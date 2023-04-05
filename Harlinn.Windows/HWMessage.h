#pragma once
#ifndef __HWMESSAGE_H__
#define __HWMESSAGE_H__

#include <HWDef.h>

namespace Harlinn::Windows
{
    struct Message : public tagMSG
    {
        using Base = tagMSG;
        using Result = LRESULT;

        Result result;
        bool handled;

        constexpr Message( ) noexcept
            : Base{}, result( 0 ), handled( false )
        {
            
        }
    };
}


#endif
