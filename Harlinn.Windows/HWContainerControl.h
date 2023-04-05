#pragma once
#ifndef __HWCONTAINERCONTROL_H__
#define __HWCONTAINERCONTROL_H__

#include <HWScrollableControl.h>

namespace Harlinn::Windows
{
    class IContainerControl
    {
    public:
        virtual const Control* ActiveControl( ) const = 0;
        virtual Control* ActiveControl( ) = 0;
        virtual void SetActiveControl( Control* control ) = 0;
        virtual void ActivateControl( Control* control ) = 0;
    };

    class ContainerControl : public ScrollableControl, public IContainerControl
    {
        Control* activeControl_ = nullptr;
    public:
        using Base = ScrollableControl;

        ContainerControl( )
            : Base( )
        {
        }

        virtual const Control* ActiveControl( ) const override
        {
            return activeControl_;
        }
        virtual Control* ActiveControl( ) override
        {
            return activeControl_;
        }

        virtual void SetActiveControl( Control* control )
        {
            activeControl_ = control;
        }
        virtual void ActivateControl( Control* control )
        {
            this->SetActiveControl( control );
        }

    };

}

#endif
