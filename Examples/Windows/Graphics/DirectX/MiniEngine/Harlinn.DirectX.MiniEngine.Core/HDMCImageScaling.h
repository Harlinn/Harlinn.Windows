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

#pragma once

#include "HDMCDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{
    class GraphicsContext;
    class ColorBuffer;
    

    namespace ImageScaling
    {
        void Initialize( DXGI_FORMAT DestFormat );

        enum eScalingFilter { kBilinear, kSharpening, kBicubic, kLanczos, kFilterCount };

        void Upscale( GraphicsContext& Context, ColorBuffer& dest, ColorBuffer& source, eScalingFilter tech = kLanczos );
    }
}