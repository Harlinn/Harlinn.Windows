#pragma once
/*
   Copyright 2024-2025 Espen Harlinn

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

//--------------------------------------------------------------------------------------
// pch.h
//
// Header for standard system include files.
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------

#pragma once

#include <HAIDirectMLX.h>
#include <HAIONNXDirectML.h>
#include <HWGraphics.h>
#include <HWDWrite.h>
#include <HWGraphicsD3D11.h>
#include <HWGraphicsD3D12SdkLayers.h>
#include <HWGraphicsD3D11On12.h>
#include <HWMediaEngine.h>
#include <HWMediaFoundation.h>
#include <HWImaging.h>
#include <HWDXCore.h>
#include <HWApplication.h>
#include <HWForm.h>
#include <HCCEnvironment.h>
#include <HCCIO.h>
#include <Harlinn/Math/VectorMath.h>

#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx12.h"


using namespace Harlinn::AI;
using namespace Harlinn::Windows::Graphics;

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <wincodec.h>

#include "d3dx12.h"

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <vector>
#ifdef __cpp_lib_span 
#include <span>
#endif
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <numeric>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#include <stdio.h>
#include <pix3.h>
#include <variant>
#include <optional>

#include "CommonStates.h"
#include "Effects.h"
#include "GamePad.h"
#include "GraphicsMemory.h"
#include "DescriptorHeap.h"
#include "DirectXHelpers.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "PrimitiveBatch.h"
#include "RenderTargetState.h"
#include "ResourceUploadBatch.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"


//#include "half.hpp"
//#include "cxxopts.hpp"


#include <dxcore_interface.h>
#include <dxcore.h>

#include <onnxruntime_cxx_api.h>

#include "dml_provider_factory.h"

using Microsoft::WRL::ComPtr;

// Use video frames as input to the DirectML model, instead of a static texture.
#define USE_VIDEO 1

// Let DirectML manage the data in the weight tensors. This can be faster on some hardware.
#define DML_MANAGED_WEIGHTS 1

namespace DX
{
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception( HRESULT hr ) : result( hr ) {}

        virtual const char* what( ) const override
        {
            static char s_str[ 64 ] = {};
            sprintf_s( s_str, "Failure with HRESULT of %08X", static_cast< unsigned int >( result ) );
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed( HRESULT hr )
    {
        if ( FAILED( hr ) )
        {
            throw com_exception( hr );
        }
    }
}
