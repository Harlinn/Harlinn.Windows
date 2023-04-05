#pragma once
#ifndef __HWAPPLICATIONOPTIONS_H__
#define __HWAPPLICATIONOPTIONS_H__

#include <HWDef.h>
#include <HCCApplicationOptions.h>

namespace Harlinn::Windows
{
    class ApplicationOptions : public Common::Core::ApplicationOptions
    {
    public:
        using Base = Common::Core::ApplicationOptions;

        ApplicationOptions()
            : Base()
        { }
    };
}

#endif
