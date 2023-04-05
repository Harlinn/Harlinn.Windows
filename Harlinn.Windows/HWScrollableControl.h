#pragma once
#ifndef __HWSCROLLABLECONTROL_H__
#define __HWSCROLLABLECONTROL_H__

#include <HWControl.h>

namespace Harlinn::Windows
{
    class ScrollableControl : public Control
    {
    public:
        using Base = Control;
        ScrollableControl( )
            : Base( )
        {
        }
    };
}
#endif
