#pragma once
#ifndef __HWMOUSEBUTTON_H__
#define __HWMOUSEBUTTON_H__

#include <HWDef.h>

namespace Harlinn::Windows
{

    enum class MouseButton : int
    {
        Left = 0,
        Right = 1,
        Middle = 2
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( MouseButton, int );
}

#endif
