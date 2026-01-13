#pragma once
#ifndef __HWCONTAINERCONTROL_H__
#define __HWCONTAINERCONTROL_H__
/*
   Copyright 2024-2026 Espen Harlinn

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
