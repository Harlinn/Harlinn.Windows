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

#include "pch.h"
#include <HWHandles.h>
#include <HWImaging.h>
#include <HWControl.h>

namespace Harlinn::Windows
{

    // ----------------------------------------------------------------------
    // BitmapHandle
    // ----------------------------------------------------------------------

    BitmapHandle BitmapHandle::LoadFromFile( const WideString& theFileMame )
    {
        using namespace Graphics::Imaging;

        auto factory = ImagingFactory::Create( );
        auto decoder = factory.CreateDecoderFromFilename( theFileMame );
        auto frame = decoder.GetFrame( 0 );
        auto result = frame.AsBitmapHandle( );
        return result;
    }



    // ----------------------------------------------------------------------
    // IconHandle
    // ----------------------------------------------------------------------
    const IconHandle IconHandle::Question( OIC_QUES, 0, 0 );
    const IconHandle IconHandle::WinLogo( OIC_WINLOGO, 0, 0 );
    const IconHandle IconHandle::Warning( OIC_WARNING, 0, 0 );
    const IconHandle IconHandle::Error( OIC_ERROR, 0, 0 );
    const IconHandle IconHandle::Information( OIC_INFORMATION, 0, 0 );
    const IconHandle IconHandle::Shield( OIC_SHIELD, 0, 0 );

    const IconHandle IconHandle::Question16x16( OIC_QUES, 16, 16 );
    const IconHandle IconHandle::WinLogo16x16( OIC_WINLOGO, 16, 16 );
    const IconHandle IconHandle::Warning16x16( OIC_WARNING, 16, 16 );
    const IconHandle IconHandle::Error16x16( OIC_ERROR, 16, 16 );
    const IconHandle IconHandle::Information16x16( OIC_INFORMATION, 16, 16 );
    const IconHandle IconHandle::Shield16x16( OIC_SHIELD, 16, 16 );

    const IconHandle IconHandle::Question24x24( OIC_QUES, 24, 24 );
    const IconHandle IconHandle::WinLogo24x24( OIC_WINLOGO, 24, 24 );
    const IconHandle IconHandle::Warning24x24( OIC_WARNING, 24, 24 );
    const IconHandle IconHandle::Error24x24( OIC_ERROR, 24, 24 );
    const IconHandle IconHandle::Information24x24( OIC_INFORMATION, 24, 24 );
    const IconHandle IconHandle::Shield24x24( OIC_SHIELD, 24, 24 );

    const IconHandle IconHandle::Question32x32( OIC_QUES, 32, 32 );
    const IconHandle IconHandle::WinLogo32x32( OIC_WINLOGO, 32, 32 );
    const IconHandle IconHandle::Warning32x32( OIC_WARNING, 32, 32 );
    const IconHandle IconHandle::Error32x32( OIC_ERROR, 32, 32 );
    const IconHandle IconHandle::Information32x32( OIC_INFORMATION, 32, 32 );
    const IconHandle IconHandle::Shield32x32( OIC_SHIELD, 32, 32 );



    // ----------------------------------------------------------------------
    // CursorHandle
    // ----------------------------------------------------------------------
    const CursorHandle CursorHandle::Normal( OCR_NORMAL, 0, 0 );
    const CursorHandle CursorHandle::IBeam( OCR_IBEAM, 0, 0 );
    const CursorHandle CursorHandle::Wait( OCR_WAIT, 0, 0 );
    const CursorHandle CursorHandle::Cross( OCR_CROSS, 0, 0 );
    const CursorHandle CursorHandle::Up( OCR_UP, 0, 0 );
    const CursorHandle CursorHandle::Size( OCR_SIZEALL, 0, 0 );
    const CursorHandle CursorHandle::SizeNWSE( OCR_SIZENWSE, 0, 0 );
    const CursorHandle CursorHandle::SizeNESW( OCR_SIZENESW, 0, 0 );
    const CursorHandle CursorHandle::SizeWE( OCR_SIZEWE, 0, 0 );
    const CursorHandle CursorHandle::SizeNS( OCR_SIZENS, 0, 0 );
    const CursorHandle CursorHandle::No( OCR_NO, 0, 0 );
    const CursorHandle CursorHandle::Hand( OCR_HAND, 0, 0 );
    const CursorHandle CursorHandle::AppStarting( OCR_APPSTARTING, 0, 0 );


    void DeviceContextHandle::DrawCaption( const Control& control, const RECT& boundingRectangle, DrawCaptionOptions options ) const
    {
        if ( ::DrawCaption( control.GetHandle( ), Value( ), &boundingRectangle, static_cast<UINT>( options ) ) == FALSE )
        {
            ThrowLastOSError( );
        }
    }

    RegionType DeviceContextHandle::ExcludeUpdateRgn( const Control& control ) const
    {
        auto rc = ::ExcludeUpdateRgn( Value( ), control.GetHandle( ) );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
        return RegionType( rc );
    }


    // ----------------------------------------------------------------------
    // PaintDeviceContextHandle
    // ----------------------------------------------------------------------
    PaintDeviceContextHandle::PaintDeviceContextHandle( const Control& control )
        : PaintDeviceContextHandle( control.GetHandle( ) )
    {
    }
}