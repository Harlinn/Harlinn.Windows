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
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#pragma once

#include "HDMCDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    namespace GameInput
    {
        HDMC_EXPORT void Initialize( );
        HDMC_EXPORT void Shutdown( );
        HDMC_EXPORT void Update( float frameDelta );

        enum DigitalInput
        {
            // keyboard
            // kKey must start at zero, see s_DXKeyMapping
            kKey_escape = 0,
            kKey_1,
            kKey_2,
            kKey_3,
            kKey_4,
            kKey_5,
            kKey_6,
            kKey_7,
            kKey_8,
            kKey_9,
            kKey_0,
            kKey_minus,
            kKey_equals,
            kKey_back,
            kKey_tab,
            kKey_q,
            kKey_w,
            kKey_e,
            kKey_r,
            kKey_t,
            kKey_y,
            kKey_u,
            kKey_i,
            kKey_o,
            kKey_p,
            kKey_lbracket,
            kKey_rbracket,
            kKey_return,
            kKey_lcontrol,
            kKey_a,
            kKey_s,
            kKey_d,
            kKey_f,
            kKey_g,
            kKey_h,
            kKey_j,
            kKey_k,
            kKey_l,
            kKey_semicolon,
            kKey_apostrophe,
            kKey_grave,
            kKey_lshift,
            kKey_backslash,
            kKey_z,
            kKey_x,
            kKey_c,
            kKey_v,
            kKey_b,
            kKey_n,
            kKey_m,
            kKey_comma,
            kKey_period,
            kKey_slash,
            kKey_rshift,
            kKey_multiply,
            kKey_lalt,
            kKey_space,
            kKey_capital,
            kKey_f1,
            kKey_f2,
            kKey_f3,
            kKey_f4,
            kKey_f5,
            kKey_f6,
            kKey_f7,
            kKey_f8,
            kKey_f9,
            kKey_f10,
            kKey_numlock,
            kKey_scroll,
            kKey_numpad7,
            kKey_numpad8,
            kKey_numpad9,
            kKey_subtract,
            kKey_numpad4,
            kKey_numpad5,
            kKey_numpad6,
            kKey_add,
            kKey_numpad1,
            kKey_numpad2,
            kKey_numpad3,
            kKey_numpad0,
            kKey_decimal,
            kKey_f11,
            kKey_f12,
            kKey_numpadenter,
            kKey_rcontrol,
            kKey_divide,
            kKey_sysrq,
            kKey_ralt,
            kKey_pause,
            kKey_home,
            kKey_up,
            kKey_pgup,
            kKey_left,
            kKey_right,
            kKey_end,
            kKey_down,
            kKey_pgdn,
            kKey_insert,
            kKey_delete,
            kKey_lwin,
            kKey_rwin,
            kKey_apps,

            kNumKeys,

            // gamepad
            kDPadUp = kNumKeys,
            kDPadDown,
            kDPadLeft,
            kDPadRight,
            kStartButton,
            kBackButton,
            kLThumbClick,
            kRThumbClick,
            kLShoulder,
            kRShoulder,
            kAButton,
            kBButton,
            kXButton,
            kYButton,

            // mouse
            kMouse0,
            kMouse1,
            kMouse2,
            kMouse3,
            kMouse4,
            kMouse5,
            kMouse6,
            kMouse7,

            kNumDigitalInputs
        };

        enum AnalogInput
        {
            // gamepad
            kAnalogLeftTrigger,
            kAnalogRightTrigger,
            kAnalogLeftStickX,
            kAnalogLeftStickY,
            kAnalogRightStickX,
            kAnalogRightStickY,

            // mouse
            kAnalogMouseX,
            kAnalogMouseY,
            kAnalogMouseScroll,

            kNumAnalogInputs
        };

        HDMC_EXPORT bool IsAnyPressed( void );

        HDMC_EXPORT bool IsPressed( DigitalInput di );
        HDMC_EXPORT bool IsFirstPressed( DigitalInput di );
        HDMC_EXPORT bool IsReleased( DigitalInput di );
        HDMC_EXPORT bool IsFirstReleased( DigitalInput di );

        HDMC_EXPORT float GetDurationPressed( DigitalInput di );

        HDMC_EXPORT float GetAnalogInput( AnalogInput ai );
        HDMC_EXPORT float GetTimeCorrectedAnalogInput( AnalogInput ai );

#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_TV_TITLE | WINAPI_PARTITION_DESKTOP)
        HDMC_EXPORT void SetKeyState( Windows::System::VirtualKey key, bool IsDown );
#endif
    }
}