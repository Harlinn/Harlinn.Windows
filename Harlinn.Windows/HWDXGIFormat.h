#pragma once
#ifndef HWDXGIFORMAT_H_
#define HWDXGIFORMAT_H_
/*
   Copyright 2024 Espen Harlinn

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

#include "HWDef.h"

namespace Harlinn::Windows::Graphics::DXGI
{
    /// <summary>
    /// Resource data formats, including fully-typed and type-less formats.
    /// </summary>
    typedef enum Format : UInt32
    {
        /// <summary>
        /// The format is not known
        /// </summary>
        Unknown = DXGI_FORMAT_UNKNOWN,
        /// <summary>
        /// A four-component, 128-bit typeless format that supports 32 bits per channel including alpha.
        /// </summary>
        RGBA32 = DXGI_FORMAT_R32G32B32A32_TYPELESS,
        R32G32B32A32_TYPELESS = DXGI_FORMAT_R32G32B32A32_TYPELESS,
        /// <summary>
        /// A four-component, 128-bit floating-point format that supports 32 bits per channel including alpha. 
        /// </summary>
        RGBAFloat32 = DXGI_FORMAT_R32G32B32A32_FLOAT,
        R32G32B32A32_FLOAT = DXGI_FORMAT_R32G32B32A32_FLOAT,
        /// <summary>
        /// A four-component, 128-bit unsigned-integer format that supports 32 bits per channel including alpha. 
        /// </summary>
        RGBAUInt32 = DXGI_FORMAT_R32G32B32A32_UINT,
        R32G32B32A32_UINT = DXGI_FORMAT_R32G32B32A32_UINT,
        /// <summary>
        /// A four-component, 128-bit signed-integer format that supports 32 bits per channel including alpha.
        /// </summary>
        RGBAInt32 = DXGI_FORMAT_R32G32B32A32_SINT,
        R32G32B32A32_SINT = DXGI_FORMAT_R32G32B32A32_SINT,
        /// <summary>
        /// A three-component, 96-bit typeless format that supports 32 bits per color channel.
        /// </summary>
        RGB32 = DXGI_FORMAT_R32G32B32_TYPELESS,
        R32G32B32_TYPELESS = DXGI_FORMAT_R32G32B32_TYPELESS,
        /// <summary>
        /// A three-component, 96-bit floating-point format that supports 32 bits per color channel
        /// </summary>
        RGBFloat32 = DXGI_FORMAT_R32G32B32_FLOAT,
        R32G32B32_FLOAT = DXGI_FORMAT_R32G32B32_FLOAT,
        /// <summary>
        /// A three-component, 96-bit unsigned-integer format that supports 32 bits per color channel.
        /// </summary>
        RGBUInt32 = DXGI_FORMAT_R32G32B32_UINT,
        R32G32B32_UINT = DXGI_FORMAT_R32G32B32_UINT,
        /// <summary>
        /// A three-component, 96-bit signed-integer format that supports 32 bits per color channel.
        /// </summary>
        RGBInt32 = DXGI_FORMAT_R32G32B32_SINT,
        R32G32B32_SINT = DXGI_FORMAT_R32G32B32_SINT,
        /// <summary>
        /// A four-component, 64-bit typeless format that supports 16 bits per channel including alpha.
        /// </summary>
        RGBA16 = DXGI_FORMAT_R16G16B16A16_TYPELESS,
        R16G16B16A16_TYPELESS = DXGI_FORMAT_R16G16B16A16_TYPELESS,
        /// <summary>
        /// A four-component, 64-bit floating-point format that supports 16 bits per channel including alpha.
        /// </summary>
        RGBAFloat16 = DXGI_FORMAT_R16G16B16A16_FLOAT,
        R16G16B16A16_FLOAT = DXGI_FORMAT_R16G16B16A16_FLOAT,
        /// <summary>
        /// A four-component, 64-bit unsigned-normalized-integer format that supports 16 bits per channel including alpha.
        /// </summary>
        RGBANUInt16 = DXGI_FORMAT_R16G16B16A16_UNORM,
        R16G16B16A16_UNORM = DXGI_FORMAT_R16G16B16A16_UNORM,
        /// <summary>
        /// A four-component, 64-bit unsigned-integer format that supports 16 bits per channel including alpha.
        /// </summary>
        RGBAUInt16 = DXGI_FORMAT_R16G16B16A16_UINT,
        R16G16B16A16_UINT = DXGI_FORMAT_R16G16B16A16_UINT,
        /// <summary>
        /// A four-component, 64-bit signed-normalized-integer format that supports 16 bits per channel including alpha.
        /// </summary>
        RGBANInt16 = DXGI_FORMAT_R16G16B16A16_SNORM,
        R16G16B16A16_SNORM = DXGI_FORMAT_R16G16B16A16_SNORM,
        /// <summary>
        /// A four-component, 64-bit signed-integer format that supports 16 bits per channel including alpha.
        /// </summary>
        RGBAInt16 = DXGI_FORMAT_R16G16B16A16_SINT,
        R16G16B16A16_SINT = DXGI_FORMAT_R16G16B16A16_SINT,
        /// <summary>
        /// A two-component, 64-bit typeless format that supports 32 bits for the red channel and 32 bits for the green channel.
        /// </summary>
        RG32 = DXGI_FORMAT_R32G32_TYPELESS,
        R32G32_TYPELESS = DXGI_FORMAT_R32G32_TYPELESS,
        /// <summary>
        /// A two-component, 64-bit floating-point format that supports 32 bits for the red channel and 32 bits for the green channel.
        /// </summary>
        RGFloat32 = DXGI_FORMAT_R32G32_FLOAT,
        R32G32_FLOAT = DXGI_FORMAT_R32G32_FLOAT,
        /// <summary>
        /// A two-component, 64-bit unsigned-integer format that supports 32 bits for the red channel and 32 bits for the green channel.
        /// </summary>
        RGUInt32 = DXGI_FORMAT_R32G32_UINT,
        R32G32_UINT = DXGI_FORMAT_R32G32_UINT,
        /// <summary>
        /// A two-component, 64-bit signed-integer format that supports 32 bits for the red channel and 32 bits for the green channel.
        /// </summary>
        RGInt32 = DXGI_FORMAT_R32G32_SINT,
        R32G32_SINT = DXGI_FORMAT_R32G32_SINT,
        /// <summary>
        /// A two-component, 64-bit typeless format that supports 32 bits for the red channel, 8 bits for the green channel, and 24 bits are unused.
        /// </summary>
        R32G8X24 = DXGI_FORMAT_R32G8X24_TYPELESS,
        R32G8X24_TYPELESS = DXGI_FORMAT_R32G8X24_TYPELESS,
        /// <summary>
        /// A 32-bit floating-point component, and two unsigned-integer components (with an additional 32 bits). This format supports 32-bit depth, 8-bit stencil, and 24 bits are unused.
        /// </summary>
        DFloat32SInt8X24 = DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
        D32_FLOAT_S8X24_UINT = DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
        /// <summary>
        /// A 32-bit floating-point component, and two typeless components (with an additional 32 bits). This format supports 32-bit red channel, 8 bits are unused, and 24 bits are unused.
        /// </summary>
        RFloat32X8X24 = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
        R32_FLOAT_X8X24_TYPELESS = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
        /// <summary>
        /// A 32-bit typeless component, and two unsigned-integer components (with an additional 32 bits). This format has 32 bits unused, 8 bits for green channel, and 24 bits are unused.
        /// </summary>
        X32GUInt8X24 = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
        X32_TYPELESS_G8X24_UINT = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
        /// <summary>
        /// A four-component, 32-bit typeless format that supports 10 bits for each color and 2 bits for alpha.
        /// </summary>
        RGB10A2 = DXGI_FORMAT_R10G10B10A2_TYPELESS,
        R10G10B10A2_TYPELESS = DXGI_FORMAT_R10G10B10A2_TYPELESS,
        /// <summary>
        /// A four-component, 32-bit unsigned-normalized-integer format that supports 10 bits for each color and 2 bits for alpha.
        /// </summary>
        RGBNUInt10ANUInt2 = DXGI_FORMAT_R10G10B10A2_UNORM,
        R10G10B10A2_UNORM = DXGI_FORMAT_R10G10B10A2_UNORM,
        /// <summary>
        /// A four-component, 32-bit unsigned-integer format that supports 10 bits for each color and 2 bits for alpha.
        /// </summary>
        RGBUInt10AUInt2 = DXGI_FORMAT_R10G10B10A2_UINT,
        R10G10B10A2_UINT = DXGI_FORMAT_R10G10B10A2_UINT,
        /// <summary>
        /// <para>
        /// Three partial-precision floating-point numbers encoded into a single 32-bit value (a variant of s10e5, which is sign bit, 10-bit mantissa, and 5-bit biased exponent).
        /// </para>
        /// <para>
        /// There are no sign bits, and there is a 5-bit biased exponent for each channel, 6-bit mantissa for R and G, and a 5-bit mantissa for B.
        /// </para>
        /// </summary>
        RGFloat11BFloat10_float = DXGI_FORMAT_R11G11B10_FLOAT,
        R11G11B10_FLOAT = DXGI_FORMAT_R11G11B10_FLOAT,
        /// <summary>
        /// A four-component, 32-bit typeless format that supports 8 bits per channel including alpha.
        /// </summary>
        RGBA8 = DXGI_FORMAT_R8G8B8A8_TYPELESS,
        R8G8B8A8_TYPELESS = DXGI_FORMAT_R8G8B8A8_TYPELESS,
        /// <summary>
        /// A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits per channel including alpha.
        /// </summary>
        RGBANUInt8 = DXGI_FORMAT_R8G8B8A8_UNORM,
        R8G8B8A8_UNORM = DXGI_FORMAT_R8G8B8A8_UNORM,
        /// <summary>
        /// A four-component, 32-bit unsigned-normalized integer sRGB format that supports 8 bits per channel including alpha.
        /// </summary>
        RGBANUInt8SRGB = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
        R8G8B8A8_UNORM_SRGB = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
        /// <summary>
        /// A four-component, 32-bit unsigned-integer format that supports 8 bits per channel including alpha.
        /// </summary>
        RGBAUInt8 = DXGI_FORMAT_R8G8B8A8_UINT,
        R8G8B8A8_UINT = DXGI_FORMAT_R8G8B8A8_UINT,
        /// <summary>
        /// A four-component, 32-bit signed-normalized-integer format that supports 8 bits per channel including alpha.
        /// </summary>
        RGBANInt8 = DXGI_FORMAT_R8G8B8A8_SNORM,
        R8G8B8A8_SNORM = DXGI_FORMAT_R8G8B8A8_SNORM,
        /// <summary>
        /// A four-component, 32-bit signed-integer format that supports 8 bits per channel including alpha.
        /// </summary>
        RGBAInt8 = DXGI_FORMAT_R8G8B8A8_SINT,
        R8G8B8A8_SINT = DXGI_FORMAT_R8G8B8A8_SINT,
        /// <summary>
        /// A two-component, 32-bit typeless format that supports 16 bits for the red channel and 16 bits for the green channel.
        /// </summary>
        RG16 = DXGI_FORMAT_R16G16_TYPELESS,
        R16G16_TYPELESS = DXGI_FORMAT_R16G16_TYPELESS,
        /// <summary>
        /// A two-component, 32-bit floating-point format that supports 16 bits for the red channel and 16 bits for the green channel.
        /// </summary>
        RGFloat16 = DXGI_FORMAT_R16G16_FLOAT,
        R16G16_FLOAT = DXGI_FORMAT_R16G16_FLOAT,
        /// <summary>
        /// A two-component, 32-bit unsigned-normalized-integer format that supports 16 bits each for the green and red channels.
        /// </summary>
        RGNUInt16 = DXGI_FORMAT_R16G16_UNORM,
        R16G16_UNORM = DXGI_FORMAT_R16G16_UNORM,
        /// <summary>
        /// A two-component, 32-bit unsigned-integer format that supports 16 bits for the red channel and 16 bits for the green channel.
        /// </summary>
        RGUInt16 = DXGI_FORMAT_R16G16_UINT,
        R16G16_UINT = DXGI_FORMAT_R16G16_UINT,
        /// <summary>
        /// A two-component, 32-bit signed-normalized-integer format that supports 16 bits for the red channel and 16 bits for the green channel.
        /// </summary>
        RGNInt16 = DXGI_FORMAT_R16G16_SNORM,
        R16G16_SNORM = DXGI_FORMAT_R16G16_SNORM,
        /// <summary>
        /// A two-component, 32-bit signed-integer format that supports 16 bits for the red channel and 16 bits for the green channel.
        /// </summary>
        RGInt16 = DXGI_FORMAT_R16G16_SINT,
        R16G16_SINT = DXGI_FORMAT_R16G16_SINT,
        /// <summary>
        /// A single-component, 32-bit typeless format that supports 32 bits for the red channel.
        /// </summary>
        R32 = DXGI_FORMAT_R32_TYPELESS,
        R32_TYPELESS = DXGI_FORMAT_R32_TYPELESS,
        /// <summary>
        /// A single-component, 32-bit floating-point format that supports 32 bits for depth.
        /// </summary>
        DFloat32 = DXGI_FORMAT_D32_FLOAT,
        D32_FLOAT = DXGI_FORMAT_D32_FLOAT,
        /// <summary>
        /// A single-component, 32-bit floating-point format that supports 32 bits for the red channel.
        /// </summary>
        RFloat32 = DXGI_FORMAT_R32_FLOAT,
        R32_FLOAT = DXGI_FORMAT_R32_FLOAT,
        /// <summary>
        /// A single-component, 32-bit unsigned-integer format that supports 32 bits for the red channel.
        /// </summary>
        RUInt32 = DXGI_FORMAT_R32_UINT,
        /// <summary>
        /// A single-component, 32-bit signed-integer format that supports 32 bits for the red channel.
        /// </summary>
        RInt32 = DXGI_FORMAT_R32_SINT,
        /// <summary>
        /// A two-component, 32-bit typeless format that supports 24 bits for the red channel and 8 bits for the green channel.
        /// </summary>
        R24G8 = DXGI_FORMAT_R24G8_TYPELESS,
        /// <summary>
        /// A 32-bit z-buffer format that supports 24 bits for depth and 8 bits for stencil.
        /// </summary>
        DNUInt24SUInt8 = DXGI_FORMAT_D24_UNORM_S8_UINT,
        /// <summary>
        /// A 32-bit format, that contains a 24 bit, single-component, unsigned-normalized integer, with an additional typeless 8 bits. This format has 24 bits red channel and 8 bits unused.
        /// </summary>
        RNUInt24X8 = DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
        /// <summary>
        /// A 32-bit format, that contains a 24 bit, single-component, typeless format, with an additional 8 bit unsigned integer component. This format has 24 bits unused and 8 bits green channel.
        /// </summary>
        X24GUInt8 = DXGI_FORMAT_X24_TYPELESS_G8_UINT,
        /// <summary>
        /// A two-component, 16-bit typeless format that supports 8 bits for the red channel and 8 bits for the green channel.
        /// </summary>
        RG8 = DXGI_FORMAT_R8G8_TYPELESS,
        /// <summary>
        /// A two-component, 16-bit unsigned-normalized-integer format that supports 8 bits for the red channel and 8 bits for the green channel.
        /// </summary>
        RGNUInt8 = DXGI_FORMAT_R8G8_UNORM,
        /// <summary>
        /// A two-component, 16-bit unsigned-integer format that supports 8 bits for the red channel and 8 bits for the green channel.
        /// </summary>
        RGUInt8 = DXGI_FORMAT_R8G8_UINT,
        /// <summary>
        /// A two-component, 16-bit signed-normalized-integer format that supports 8 bits for the red channel and 8 bits for the green channel.
        /// </summary>
        RGNInt8 = DXGI_FORMAT_R8G8_SNORM,
        /// <summary>
        /// A two-component, 16-bit signed-integer format that supports 8 bits for the red channel and 8 bits for the green channel.
        /// </summary>
        RGInt8 = DXGI_FORMAT_R8G8_SINT,
        /// <summary>
        /// A single-component, 16-bit typeless format that supports 16 bits for the red channel.
        /// </summary>
        R16 = DXGI_FORMAT_R16_TYPELESS,
        /// <summary>
        /// A single-component, 16-bit floating-point format that supports 16 bits for the red channel.
        /// </summary>
        RFloat16 = DXGI_FORMAT_R16_FLOAT,
        /// <summary>
        /// A single-component, 16-bit unsigned-normalized-integer format that supports 16 bits for depth.
        /// </summary>
        D16_unorm = DXGI_FORMAT_D16_UNORM,
        /// <summary>
        /// A single-component, 16-bit unsigned-normalized-integer format that supports 16 bits for the red channel.
        /// </summary>
        RNUInt16 = DXGI_FORMAT_R16_UNORM,
        /// <summary>
        /// A single-component, 16-bit unsigned-integer format that supports 16 bits for the red channel.
        /// </summary>
        RUInt16 = DXGI_FORMAT_R16_UINT,
        /// <summary>
        /// A single-component, 16-bit signed-normalized-integer format that supports 16 bits for the red channel.
        /// </summary>
        RNInt16 = DXGI_FORMAT_R16_SNORM,
        /// <summary>
        /// A single-component, 16-bit signed-integer format that supports 16 bits for the red channel.
        /// </summary>
        RInt16 = DXGI_FORMAT_R16_SINT,
        /// <summary>
        /// A single-component, 8-bit typeless format that supports 8 bits for the red channel.
        /// </summary>
        R8 = DXGI_FORMAT_R8_TYPELESS,
        /// <summary>
        /// A single-component, 8-bit unsigned-normalized-integer format that supports 8 bits for the red channel.
        /// </summary>
        RNUInt8 = DXGI_FORMAT_R8_UNORM,
        /// <summary>
        /// A single-component, 8-bit unsigned-integer format that supports 8 bits for the red channel.
        /// </summary>
        RUInt8 = DXGI_FORMAT_R8_UINT,
        /// <summary>
        /// A single-component, 8-bit signed-normalized-integer format that supports 8 bits for the red channel.
        /// </summary>
        RNInt8 = DXGI_FORMAT_R8_SNORM,
        /// <summary>
        /// A single-component, 8-bit signed-integer format that supports 8 bits for the red channel.
        /// </summary>
        RInt8 = DXGI_FORMAT_R8_SINT,
        /// <summary>
        /// A single-component, 8-bit unsigned-normalized-integer format for alpha only.
        /// </summary>
        ANUInt8 = DXGI_FORMAT_A8_UNORM,
        /// <summary>
        /// A single-component, 1-bit unsigned-normalized integer format that supports 1 bit for the red channel. 
        /// </summary>
        /// <remarks>
        /// RNUInt1 is designed specifically for text filtering, and must be used with a 
        /// format-specific, configurable 8x8 filter mode. When calling an HLSL sampling 
        /// function using this format, the address offset parameter must be set to (0,0).
        /// </remarks>
        RNUInt1 = DXGI_FORMAT_R1_UNORM,
        /// <summary>
        /// <para>
        /// Three partial-precision floating-point numbers encoded into a single 32-bit value 
        /// all sharing the same 5-bit exponent (variant of s10e5, which is sign bit, 10-bit 
        /// mantissa, and 5-bit biased exponent). There is no sign bit, and there is a shared 5-bit biased exponent and a 9-bit mantissa for each channel
        /// </para>
        /// </summary>
        RGBMantissa9SharedExp5 = DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
        /// <summary>
        /// A four-component, 32-bit unsigned-normalized-integer format. This packed RGB 
        /// format is analogous to the UYVY format. Each 32-bit block describes a pair of 
        /// pixels: (R8, G8, B8) and (R8, G8, B8) where the R8/B8 values are repeated, and 
        /// the G8 values are unique to each pixel.
        /// </summary>
        RGBGNUInt8 = DXGI_FORMAT_R8G8_B8G8_UNORM,
        /// <summary>
        /// A four-component, 32-bit unsigned-normalized-integer format. This packed RGB format 
        /// is analogous to the YUY2 format. Each 32-bit block describes a pair of pixels: 
        /// (R8, G8, B8) and (R8, G8, B8) where the R8/B8 values are repeated, and the G8 
        /// values are unique to each pixel.
        /// </summary>
        GRGBNUInt8 = DXGI_FORMAT_G8R8_G8B8_UNORM,
        /// <summary>
        /// Four-component typeless block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed1 = DXGI_FORMAT_BC1_TYPELESS,
        /// <summary>
        /// Four-component block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed1UNorm = DXGI_FORMAT_BC1_UNORM,
        /// <summary>
        /// Four-component block-compression format for sRGB data. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed1UNormSRGB = DXGI_FORMAT_BC1_UNORM_SRGB, 
        /// <summary>
        /// Four-component typeless block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed2 = DXGI_FORMAT_BC2_TYPELESS,
        /// <summary>
        /// Four-component block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed2UNorm = DXGI_FORMAT_BC2_UNORM, 
        /// <summary>
        /// Four-component block-compression format for sRGB data. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed2UNormSRGB = DXGI_FORMAT_BC2_UNORM_SRGB,
        /// <summary>
        /// Four-component typeless block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed3 = DXGI_FORMAT_BC3_TYPELESS,
        /// <summary>
        /// Four-component block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>. 
        /// </summary>
        BlockCompressed3UNorm = DXGI_FORMAT_BC3_UNORM,
        /// <summary>
        /// Four-component block-compression format for sRGB data. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed3UNormSRGB = DXGI_FORMAT_BC3_UNORM_SRGB,
        /// <summary>
        /// One-component typeless block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed4 = DXGI_FORMAT_BC4_TYPELESS,
        /// <summary>
        /// One-component block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed4UNorm = DXGI_FORMAT_BC4_UNORM,
        /// <summary>
        /// One-component block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed4SNorm = DXGI_FORMAT_BC4_SNORM,
        /// <summary>
        /// Two-component typeless block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed5 = DXGI_FORMAT_BC5_TYPELESS,
        /// <summary>
        /// Two-component block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed5UNorm = DXGI_FORMAT_BC5_UNORM,
        /// <summary>
        /// Two-component block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed5SNorm = DXGI_FORMAT_BC5_SNORM,
        /// <summary>
        /// A three-component, 16-bit unsigned-normalized-integer format that supports 5 bits for blue, 6 bits for green, and 5 bits for red.
        /// </summary>
        BNUInt5GNUInt6RNUInt5 = DXGI_FORMAT_B5G6R5_UNORM,
        /// <summary>
        /// A four-component, 16-bit unsigned-normalized-integer format that supports 5 bits for each color channel and 1-bit alpha.
        /// </summary>
        BNUInt5GNUint5RNUint5ANUInt1 = DXGI_FORMAT_B5G5R5A1_UNORM,
        /// <summary>
        /// A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits for each color channel and 8-bit alpha.
        /// </summary>
        BNUInt8GNUInt8RNUInt8ANUInt8 = DXGI_FORMAT_B8G8R8A8_UNORM,
        /// <summary>
        /// A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits for each color channel and 8 bits unused.
        /// </summary>
        BNUInt8GNUInt8RNUInt8X8_unorm = DXGI_FORMAT_B8G8R8X8_UNORM,
        /// <summary>
        /// A four-component, 32-bit 2.8-biased fixed-point format that supports 10 bits for each color channel and 2-bit alpha.
        /// </summary>
        RFixed10GFixed10BFixed10ANUInt2 = DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
        /// <summary>
        /// A four-component, 32-bit typeless format that supports 8 bits for each channel including alpha.
        /// </summary>
        B8G8R8A8 = DXGI_FORMAT_B8G8R8A8_TYPELESS,
        /// <summary>
        /// A four-component, 32-bit unsigned-normalized standard RGB format that supports 8 bits for each channel including alpha.
        /// </summary>
        BNUInt8GNUInt8RNUInt8ANUInt8SRGB = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
        /// <summary>
        /// A four-component, 32-bit typeless format that supports 8 bits for each color channel, and 8 bits are unused.
        /// </summary>
        B8G8R8X8 = DXGI_FORMAT_B8G8R8X8_TYPELESS,
        /// <summary>
        /// A four-component, 32-bit unsigned-normalized standard RGB format that supports 8 bits for each color channel, and 8 bits are unused.
        /// </summary>
        BNUInt8GNUInt8RNUInt8X8SRGB = DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,
        /// <summary>
        /// A typeless block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed6H = DXGI_FORMAT_BC6H_TYPELESS,
        /// <summary>
        /// A block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed6H_UF16 = DXGI_FORMAT_BC6H_UF16,
        /// <summary>
        /// A block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed6H_SF16 = DXGI_FORMAT_BC6H_SF16,
        /// <summary>
        /// A typeless block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed7 = DXGI_FORMAT_BC7_TYPELESS,
        /// <summary>
        /// A block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed7UNorm = DXGI_FORMAT_BC7_UNORM,
        /// <summary>
        /// A block-compression format. For information about block-compression 
        /// formats, see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">Texture Block Compression in Direct3D 11</see>.
        /// </summary>
        BlockCompressed7UNormSRGB = DXGI_FORMAT_BC7_UNORM_SRGB,
        AYUV = DXGI_FORMAT_AYUV,
        Y410 = DXGI_FORMAT_Y410,
        Y416 = DXGI_FORMAT_Y416,
        NV12 = DXGI_FORMAT_NV12,
        P010 = DXGI_FORMAT_P010,
        P016 = DXGI_FORMAT_P016,
        Opaque420 = DXGI_FORMAT_420_OPAQUE,
        YUY2 = DXGI_FORMAT_YUY2,
        Y210 = DXGI_FORMAT_Y210,
        Y216 = DXGI_FORMAT_Y216,
        NV11 = DXGI_FORMAT_NV11,
        AI44 = DXGI_FORMAT_AI44,
        IA44 = DXGI_FORMAT_IA44,
        P8 = DXGI_FORMAT_P8,
        A8P8 = DXGI_FORMAT_A8P8,
        B4g4r4a4_unorm = DXGI_FORMAT_B4G4R4A4_UNORM,
        P208 = DXGI_FORMAT_P208,
        V208 = DXGI_FORMAT_V208,
        V408 = DXGI_FORMAT_V408,
        Sampler_feedback_min_mip_opaque = DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE,
        Sampler_feedback_mip_region_used_opaque = DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE,
        Force_uint = std::bit_cast<UInt32>(DXGI_FORMAT_FORCE_UINT)
    };
}

#endif
