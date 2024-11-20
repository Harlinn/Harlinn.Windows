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
#include <HWImaging.h>
#include <HWHandles.h>
#include <HCCException.h>

namespace Harlinn::Windows::Graphics
{
    namespace Imaging
    {
        // -----------------------------------------------------------------
        // Palette
        // -----------------------------------------------------------------
        Palette& Palette::InitializePredefined( BitmapPaletteType ePaletteType, bool addTransparentColor )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializePredefined( WICBitmapPaletteType( ePaletteType ), addTransparentColor );
            CheckHRESULT( hr );
            return *this;
        }
        Palette& Palette::InitializeCustom( Color* pColors, UINT cCount )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeCustom( pColors, cCount );
            CheckHRESULT( hr );
            return *this;
        }

        Palette& Palette::InitializeCustom( const std::vector< Color >& theColors )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeCustom( (WICColor*)theColors.data( ), UINT( theColors.size( ) ) );
            CheckHRESULT( hr );
            return *this;
        }
        Palette& Palette::InitializeCustom( std::shared_ptr<const std::vector< Color >>& theColors )
        {
            if ( !theColors )
            {
                ThrowPointerIsNULL( );
            }
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeCustom( (WICColor*)theColors->data( ), UINT( theColors->size( ) ) );
            CheckHRESULT( hr );
            return *this;
        }
        Palette& Palette::InitializeFromBitmap( const BitmapSource& theSurface, UINT cCount, bool addTransparentColor )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromBitmap( theSurface, cCount, addTransparentColor );
            CheckHRESULT( hr );
            return *this;
        }
        Palette& Palette::InitializeFromPalette( const Palette& thePalette )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromPalette( thePalette );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapPaletteType Palette::Type( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BitmapPaletteType result;
            auto hr = pInterface->GetType( (WICBitmapPaletteType*)&result );
            CheckHRESULT( hr );
            return result;
        }
        UINT Palette::GetColorCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            UINT result;
            auto hr = pInterface->GetColorCount( &result );
            CheckHRESULT( hr );
            return result;
        }
        std::shared_ptr<std::vector< Color > > Palette::Colors( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto count = GetColorCount( );
            auto result = std::make_shared<std::vector< Color > >( size_t( count ) );
            auto hr = pInterface->GetColors( count, result->data( ), &count );
            CheckHRESULT( hr );
            return result;
        }
        bool Palette::IsBlackWhite( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result;
            auto hr = pInterface->IsBlackWhite( &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }
        bool Palette::IsGrayscale( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result;
            auto hr = pInterface->IsGrayscale( &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }
        bool Palette::HasAlpha( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result;
            auto hr = pInterface->HasAlpha( &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }

        // -----------------------------------------------------------------
        // BitmapSource
        // -----------------------------------------------------------------
        const BitmapSource& BitmapSource::GetSize( UINT* puiWidth, UINT* puiHeight ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetSize( puiWidth, puiHeight );
            CheckHRESULT( hr );
            return *this;
        }

        Size BitmapSource::GetSize( ) const
        {
            UINT width = 0;
            UINT height = 0;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetSize( &width, &height );
            CheckHRESULT( hr );
            return Size( width, height );
        }
        const BitmapSource& BitmapSource::GetPixelFormat( WICPixelFormatGUID* pPixelFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPixelFormat( pPixelFormat );
            CheckHRESULT( hr );
            return *this;
        }
        WICPixelFormatGUID BitmapSource::GetPixelFormat( ) const
        {
            WICPixelFormatGUID result = { 0, };
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPixelFormat( &result );
            CheckHRESULT( hr );
            return result;
        }
        const BitmapSource& BitmapSource::GetResolution( double* pDpiX, double* pDpiY ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetResolution( pDpiX, pDpiY );
            CheckHRESULT( hr );
            return *this;
        }
        Resolution BitmapSource::GetResolution( ) const
        {
            double dpiX, dpiY;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetResolution( &dpiX, &dpiY );
            CheckHRESULT( hr );
            return Resolution( dpiX, dpiY );
        }

        const BitmapSource& BitmapSource::CopyPalette( Palette& theTargetPalette ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CopyPalette( theTargetPalette );
            CheckHRESULT( hr );
            return *this;
        }

        Palette BitmapSource::CopyPalette( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }

            Palette thePalette = factory->CreatePalette( );
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CopyPalette( thePalette );
            CheckHRESULT( hr );
            return thePalette;
        }
        const BitmapSource& BitmapSource::CopyPixels( Rectangle& rectangle, UINT bytePerStride, UINT bufferSize, BYTE* pbBuffer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CopyPixels( rectangle, bytePerStride, bufferSize, pbBuffer );
            CheckHRESULT( hr );
            return *this;
        }

        const BitmapSource& BitmapSource::CopyPixels( UINT bytePerStride, UINT bufferSize, BYTE* pbBuffer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CopyPixels( nullptr, bytePerStride, bufferSize, pbBuffer );
            CheckHRESULT( hr );
            return *this;
        }

        FormatConverter BitmapSource::Convert( REFGUID dstFormat, BitmapDitherType dither, const Palette& thePalette, double alphaThresholdPercent, BitmapPaletteType paletteTranslate ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            FormatConverter result = factory->CreateFormatConverter( );
            result.Initialize( *this, dstFormat, dither, thePalette, alphaThresholdPercent, paletteTranslate );
            return result;
        }

        FormatConverter BitmapSource::Convert( REFGUID dstFormat ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            FormatConverter result = factory->CreateFormatConverter( );
            result.Initialize( *this, dstFormat, 0.0, BitmapPaletteType::Custom );
            return result;
        }
        FormatConverter BitmapSource::Convert( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            FormatConverter result = factory->CreateFormatConverter( );
            result.Initialize( *this, GUID_WICPixelFormat32bppBGR, 0.0, BitmapPaletteType::Custom );
            return result;
        }
        BitmapScaler BitmapSource::Scale( UINT uiWidth, UINT uiHeight, BitmapInterpolationMode mode ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            BitmapScaler result = factory->CreateBitmapScaler( );
            result.Initialize( *this, uiWidth, uiHeight, mode );
            return result;
        }
        BitmapScaler BitmapSource::Scale( const Size& size, BitmapInterpolationMode mode ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            BitmapScaler result = factory->CreateBitmapScaler( );
            result.Initialize( *this, size.Width( ), size.Height( ), mode );
            return result;
        }
        BitmapClipper BitmapSource::Clip( const Rectangle& reactangle ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            BitmapClipper result = factory->CreateBitmapClipper( );
            result.Initialize( *this, reactangle );
            return result;
        }
        BitmapFlipRotator BitmapSource::Rotate( BitmapTransformOptions options ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            BitmapFlipRotator result = factory->CreateBitmapFlipRotator( );
            result.Initialize( *this, options );
            return result;
        }


        Bitmap BitmapSource::ToBitmap( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            auto result = factory->CreateBitmapFromSource( *this, BitmapCreateCacheOption::CacheOnDemand );
            return result;
        }


        BitmapHandle BitmapSource::AsBitmapHandle( ) const
        {
            auto pixelFormat = this->GetPixelFormat( );
            if ( IsEqualGUID( GUID_WICPixelFormat32bppBGR, pixelFormat ) == FALSE )
            {
                auto converter = Convert( );
                auto result = converter.AsBitmapHandle( );
                return result;
            }
            else
            {
                UINT width = 0;
                UINT height = 0;
                auto hr = GetSize( &width, &height );
                CheckHRESULT( hr );

                BITMAPINFO bminfo;
                memset( &bminfo, 0, sizeof( bminfo ) );
                bminfo.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
                bminfo.bmiHeader.biWidth = width;
                bminfo.bmiHeader.biHeight = -(LONG)height; //top-down DIB with origin in the upper-left corner
                bminfo.bmiHeader.biPlanes = 1;
                bminfo.bmiHeader.biBitCount = 32;
                bminfo.bmiHeader.biCompression = BI_RGB;

                HDC hdcScreen = GetDC( nullptr );
                if ( !hdcScreen )
                {
                    ThrowLastOSError( );
                }

                BYTE* imageBits = nullptr;

                HBITMAP hBitmap = CreateDIBSection( hdcScreen, &bminfo, DIB_RGB_COLORS, (void**)&imageBits, nullptr, 0 );
                ReleaseDC( nullptr, hdcScreen );
                if ( !hBitmap )
                {
                    ThrowLastOSError( );
                }
                BitmapHandle result( hBitmap, true );
                UINT strideSize = width * 4;
                UINT imageByteCount = strideSize * height;
                hr = CopyPixels( strideSize, imageByteCount, imageBits );

                if ( FAILED( hr ) )
                {
                    DeleteObject( hBitmap );
                    CheckHRESULT( hr );
                }

                return result;
            }

        }



        // -----------------------------------------------------------------
        // FormatConverter
        // -----------------------------------------------------------------
        FormatConverter& FormatConverter::Initialize( const BitmapSource& theSource, REFGUID dstFormat, BitmapDitherType dither, const Palette& thePalette, double alphaThresholdPercent, BitmapPaletteType paletteTranslate )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( theSource, dstFormat, WICBitmapDitherType( dither ), thePalette, alphaThresholdPercent, WICBitmapPaletteType( paletteTranslate ) );
            CheckHRESULT( hr );
            return *this;
        }
        FormatConverter& FormatConverter::Initialize( const BitmapSource& theSource, REFGUID dstFormat, double alphaThresholdPercent, BitmapPaletteType paletteTranslate )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( theSource, dstFormat, WICBitmapDitherTypeNone, nullptr, alphaThresholdPercent, WICBitmapPaletteType( paletteTranslate ) );
            CheckHRESULT( hr );
            return *this;
        }
        bool FormatConverter::CanConvert( REFGUID  srcPixelFormat, REFGUID  dstPixelFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result = FALSE;
            auto hr = pInterface->CanConvert( srcPixelFormat, dstPixelFormat, &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }

        // -----------------------------------------------------------------
        // BitmapScaler
        // -----------------------------------------------------------------
        BitmapScaler& BitmapScaler::Initialize( const BitmapSource& theSource, UINT uiWidth, UINT uiHeight, BitmapInterpolationMode mode )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( theSource, uiWidth, uiHeight, WICBitmapInterpolationMode( mode ) );
            CheckHRESULT( hr );
            return *this;
        }
        BitmapScaler& BitmapScaler::Initialize( const BitmapSource& theSource, const Size& theSize, BitmapInterpolationMode mode )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( theSource, theSize.Width( ), theSize.Height( ), WICBitmapInterpolationMode( mode ) );
            CheckHRESULT( hr );
            return *this;
        }

        // -----------------------------------------------------------------
        // BitmapClipper
        // -----------------------------------------------------------------
        BitmapClipper& BitmapClipper::Initialize( const BitmapSource& theSource, const Rectangle& reactangle )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( theSource, reactangle );
            CheckHRESULT( hr );
            return *this;
        }

        // -----------------------------------------------------------------
        // BitmapFlipRotator
        // -----------------------------------------------------------------
        BitmapFlipRotator& BitmapFlipRotator::Initialize( const BitmapSource& theSource, BitmapTransformOptions options )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( theSource, WICBitmapTransformOptions( options ) );
            CheckHRESULT( hr );
            return *this;
        }

        // -----------------------------------------------------------------
        // BitmapLock
        // -----------------------------------------------------------------
        const BitmapLock& BitmapLock::GetSize( UINT* puiWidth, UINT* puiHeight ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetSize( puiWidth, puiHeight );
            CheckHRESULT( hr );
            return *this;
        }
        Size BitmapLock::GetSize( ) const
        {
            UINT width = 0;
            UINT height = 0;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetSize( &width, &height );
            CheckHRESULT( hr );
            return Size( width, height );
        }

        const BitmapLock& BitmapLock::GetStride( UINT* pcbStride ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetStride( pcbStride );
            CheckHRESULT( hr );
            return *this;
        }
        UINT BitmapLock::GetStride( ) const
        {
            UINT stride;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetStride( &stride );
            CheckHRESULT( hr );
            return stride;
        }
        const BitmapLock& BitmapLock::GetDataPointer( UINT* pcbBufferSize, BYTE** ppbData ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetDataPointer( pcbBufferSize, ppbData );
            CheckHRESULT( hr );
            return *this;
        }
        const BitmapLock& BitmapLock::GetPixelFormat( GUID* pPixelFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPixelFormat( pPixelFormat );
            CheckHRESULT( hr );
            return *this;
        }
        GUID BitmapLock::GetPixelFormat( ) const
        {
            GUID result = { 0, };
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPixelFormat( &result );
            CheckHRESULT( hr );
            return result;
        }

        // -----------------------------------------------------------------
        // Bitmap
        // -----------------------------------------------------------------
        BitmapLock Bitmap::Lock( const Rectangle& lockRectangle, DWORD flags )
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapLock* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Lock( lockRectangle, flags, &result );
            CheckHRESULT( hr );
            return BitmapLock( factory, result );
        }
        Bitmap& Bitmap::SetPalette( const Palette& thePalette )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetPalette( thePalette );
            CheckHRESULT( hr );
            return *this;
        }
        Bitmap& Bitmap::SetResolution( double dpiX, double dpiY )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetResolution( dpiX, dpiY );
            CheckHRESULT( hr );
            return *this;
        }
        Bitmap& Bitmap::SetResolution( const Resolution& resolution )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetResolution( resolution.X( ), resolution.Y( ) );
            CheckHRESULT( hr );
            return *this;
        }

        // -----------------------------------------------------------------
        // ColorContext
        // -----------------------------------------------------------------
        ColorContext& ColorContext::InitializeFromFilename( LPCWSTR theFilename )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromFilename( theFilename );
            CheckHRESULT( hr );
            return *this;
        }
        ColorContext& ColorContext::InitializeFromFilename( const WideString& theFilename )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromFilename( theFilename.c_str( ) );
            CheckHRESULT( hr );
            return *this;
        }
        ColorContext& ColorContext::InitializeFromMemory( const BYTE* theBuffer, UINT theBufferSize )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromMemory( theBuffer, theBufferSize );
            CheckHRESULT( hr );
            return *this;
        }
        ColorContext& ColorContext::InitializeFromExifColorSpace( UINT value )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromExifColorSpace( value );
            CheckHRESULT( hr );
            return *this;
        }
        ColorContextType ColorContext::GetType( ) const
        {
            ColorContextType result = ColorContextType::Uninitialized;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetType( (WICColorContextType*)&result );
            CheckHRESULT( hr );
            return result;
        }
        const ColorContext& ColorContext::GetProfileBytes( UINT bufferSize, BYTE* pbBuffer, UINT* actualNumberOfBytesCopied ) const
        {
            ColorContextType result = ColorContextType::Uninitialized;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetProfileBytes( bufferSize, pbBuffer, actualNumberOfBytesCopied );
            CheckHRESULT( hr );
            return *this;
        }
        UINT ColorContext::GetExifColorSpace( ) const
        {
            UINT result = 0;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetExifColorSpace( &result );
            CheckHRESULT( hr );
            return result;
        }

        // -----------------------------------------------------------------
        // ColorTransform
        // -----------------------------------------------------------------
        ColorTransform& ColorTransform::Initialize( const BitmapSource& theBitmapSource, const ColorContext& theContextSource, const ColorContext& theContextDest, REFGUID pixelFmtDest )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( theBitmapSource, theContextSource, theContextDest, pixelFmtDest );
            CheckHRESULT( hr );
            return *this;
        }

        // -----------------------------------------------------------------
        // Stream
        // -----------------------------------------------------------------
        Stream& Stream::InitializeFromIStream( IStream* theStream )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromIStream( theStream );
            CheckHRESULT( hr );
            return *this;
        }
        Stream& Stream::InitializeFromFilename( LPCWSTR theFileName, DWORD theDesiredAccess )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromFilename( theFileName, theDesiredAccess );
            CheckHRESULT( hr );
            return *this;
        }
        Stream& Stream::InitializeFromMemory( BYTE* theBuffer, DWORD theBufferSize )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromMemory( theBuffer, theBufferSize );
            CheckHRESULT( hr );
            return *this;
        }
        Stream& Stream::InitializeFromIStreamRegion( IStream* theStream, unsigned long long theOffset, unsigned long long theMaxSize )
        {
            ULARGE_INTEGER offset;
            ULARGE_INTEGER maxSize;
            offset.QuadPart = theOffset;
            maxSize.QuadPart = theMaxSize;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromIStreamRegion( theStream, offset, maxSize );
            CheckHRESULT( hr );
            return *this;
        }

        // -----------------------------------------------------------------
        // EnumMetadataItem
        // -----------------------------------------------------------------
        bool EnumMetadataItem::Next( ULONG celt,
            PROPVARIANT* rgeltSchema, PROPVARIANT* rgeltId, PROPVARIANT* rgeltValue,
            ULONG* pceltFetched )
        {
            InterfaceType* pInterface = GetInterface( );
            ULONG numberOfElementsFetched = 0;
            auto hr = pInterface->Next( celt, rgeltSchema, rgeltId, rgeltValue, &numberOfElementsFetched );
            if ( SUCCEEDED( hr ) )
            {
                if ( pceltFetched )
                {
                    *pceltFetched = numberOfElementsFetched;
                }
                return true;
            }
            return false;
        }

        EnumMetadataItem& EnumMetadataItem::Skip( ULONG celt )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Skip( celt );
            CheckHRESULT( hr );
            return *this;
        }
        EnumMetadataItem& EnumMetadataItem::Reset( )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Reset( );
            CheckHRESULT( hr );
            return *this;
        }
        EnumMetadataItem EnumMetadataItem::Clone( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            InterfaceType* pClone = 0;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Clone( &pClone );
            CheckHRESULT( hr );
            EnumMetadataItem result( factory, pClone );
            return result;
        }

        // -----------------------------------------------------------------
        // MetadataQueryReader
        // -----------------------------------------------------------------
        const MetadataQueryReader& MetadataQueryReader::GetContainerFormat( GUID* pguidContainerFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetContainerFormat( pguidContainerFormat );
            CheckHRESULT( hr );
            return *this;
        }
        GUID MetadataQueryReader::GetContainerFormat( ) const
        {
            GUID result = { 0, };
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetContainerFormat( &result );
            CheckHRESULT( hr );
            return result;
        }
        const MetadataQueryReader& MetadataQueryReader::GetLocation( UINT cchMaxLength, WCHAR* wzNamespace, UINT* pcchActualLength ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetLocation( cchMaxLength, wzNamespace, pcchActualLength );
            CheckHRESULT( hr );
            return *this;
        }
        WideString MetadataQueryReader::GetLocation( ) const
        {
            UINT actualLength = 0;
            WCHAR buffer[512];
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetLocation( sizeof( buffer ) / sizeof( WCHAR ), buffer, &actualLength );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actualLength ) );
        }
        const MetadataQueryReader& MetadataQueryReader::GetMetadataByName( LPCWSTR wzName, PROPVARIANT* pvarValue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetMetadataByName( wzName, pvarValue );
            CheckHRESULT( hr );
            return *this;
        }
        const MetadataQueryReader& MetadataQueryReader::GetMetadataByName( const WideString& theName, PROPVARIANT* pvarValue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetMetadataByName( theName.c_str( ), pvarValue );
            CheckHRESULT( hr );
            return *this;
        }

        EnumString MetadataQueryReader::GetEnumerator( ) const
        {
            IEnumString* result;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetEnumerator( &result );
            CheckHRESULT( hr );
            return EnumString( result );
        }

        // -----------------------------------------------------------------
        // MetadataQueryWriter
        // -----------------------------------------------------------------
        MetadataQueryWriter& MetadataQueryWriter::SetMetadataByName( LPCWSTR wzName, const PROPVARIANT* pvarValue )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetMetadataByName( wzName, pvarValue );
            CheckHRESULT( hr );
            return *this;
        }
        MetadataQueryWriter& MetadataQueryWriter::RemoveMetadataByName( LPCWSTR wzName )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->RemoveMetadataByName( wzName );
            CheckHRESULT( hr );
            return *this;
        }

        // -----------------------------------------------------------------
        // BitmapEncoder
        // -----------------------------------------------------------------
        BitmapEncoder& BitmapEncoder::Initialize( IStream* theStream, BitmapEncoderCacheOption cacheOption )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( theStream, WICBitmapEncoderCacheOption( cacheOption ) );
            CheckHRESULT( hr );
            return *this;
        }
        const BitmapEncoder& BitmapEncoder::GetContainerFormat( GUID* pguidContainerFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetContainerFormat( pguidContainerFormat );
            CheckHRESULT( hr );
            return *this;
        }
        GUID BitmapEncoder::GetContainerFormat( ) const
        {
            GUID result = { 0, };
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetContainerFormat( &result );
            CheckHRESULT( hr );
            return result;
        }

        BitmapEncoderInfo BitmapEncoder::GetEncoderInfo( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapEncoderInfo* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetEncoderInfo( &result );
            CheckHRESULT( hr );
            return BitmapEncoderInfo( factory, result );
        }

        BitmapEncoder& BitmapEncoder::SetColorContexts( std::shared_ptr< std::vector<ColorContext> > colorContexts )
        {
            InterfaceType* pInterface = GetInterface( );
            std::vector<IWICColorContext*> contexts;
            contexts.reserve( colorContexts->size( ) );
            for ( auto it = colorContexts->begin( ); it != colorContexts->end( ); it++ )
            {
                contexts.push_back( *it );
            }
            auto hr = pInterface->SetColorContexts( UINT( contexts.size( ) ), contexts.data( ) );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapEncoder& BitmapEncoder::SetPalette( const Palette& thePalette )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetPalette( thePalette );
            CheckHRESULT( hr );
            return *this;
        }
        BitmapEncoder& BitmapEncoder::SetThumbnail( const BitmapSource& theThumbnail )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetThumbnail( theThumbnail );
            CheckHRESULT( hr );
            return *this;
        }
        BitmapEncoder& BitmapEncoder::SetPreview( const BitmapSource& thePreview )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetPreview( thePreview );
            CheckHRESULT( hr );
            return *this;
        }
        BitmapFrameEncode BitmapEncoder::CreateNewFrame( IPropertyBag2** ppIEncoderOptions )
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapFrameEncode* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateNewFrame( &result, ppIEncoderOptions );
            CheckHRESULT( hr );
            return BitmapFrameEncode( factory, result );
        }
        BitmapFrameEncode BitmapEncoder::CreateNewFrame( )
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapFrameEncode* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateNewFrame( &result, nullptr );
            CheckHRESULT( hr );
            return BitmapFrameEncode( factory, result );
        }
        BitmapEncoder& BitmapEncoder::Commit( )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Commit( );
            CheckHRESULT( hr );
            return *this;
        }
        MetadataQueryWriter BitmapEncoder::GetMetadataQueryWriter( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICMetadataQueryWriter* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetMetadataQueryWriter( &result );
            CheckHRESULT( hr );
            return MetadataQueryWriter( factory, result );
        }

        // -----------------------------------------------------------------
        // BitmapFrameEncode
        // -----------------------------------------------------------------
        BitmapFrameEncode& BitmapFrameEncode::Initialize( )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( nullptr );
            CheckHRESULT( hr );
            return *this;
        }
        BitmapFrameEncode& BitmapFrameEncode::Initialize( IPropertyBag2* pIEncoderOptions )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( pIEncoderOptions );
            CheckHRESULT( hr );
            return *this;
        }
        BitmapFrameEncode& BitmapFrameEncode::SetSize( UINT uiWidth, UINT uiHeight )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetSize( uiWidth, uiHeight );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::SetSize( const Size& size )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetSize( size.Width( ), size.Height( ) );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::SetResolution( double dpiX, double dpiY )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetResolution( dpiX, dpiY );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::SetResolution( const Resolution& resolution )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetResolution( resolution.X( ), resolution.Y( ) );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::SetPixelFormat( GUID* pPixelFormat )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetPixelFormat( pPixelFormat );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::SetPixelFormat( const GUID& thePixelFormat )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetPixelFormat( (GUID*)&thePixelFormat );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::SetColorContexts( std::shared_ptr< std::vector<ColorContext> > colorContexts )
        {
            InterfaceType* pInterface = GetInterface( );
            std::vector<IWICColorContext*> contexts;
            contexts.reserve( colorContexts->size( ) );
            for ( auto it = colorContexts->begin( ); it != colorContexts->end( ); it++ )
            {
                contexts.push_back( *it );
            }
            auto hr = pInterface->SetColorContexts( UINT( contexts.size( ) ), contexts.data( ) );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::SetPalette( const Palette& thePalette )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetPalette( thePalette );
            CheckHRESULT( hr );
            return *this;
        }
        BitmapFrameEncode& BitmapFrameEncode::SetThumbnail( const BitmapSource& theThumbnail )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetThumbnail( theThumbnail );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::WritePixels( UINT lineCount, UINT cbStride, UINT cbBufferSize, BYTE* pbPixels )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->WritePixels( lineCount, cbStride, cbBufferSize, pbPixels );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::WriteSource( const BitmapSource& theBitmapSource, const Rectangle& rectangle )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->WriteSource( theBitmapSource, rectangle );
            CheckHRESULT( hr );
            return *this;
        }
        BitmapFrameEncode& BitmapFrameEncode::WriteSource( const BitmapSource& theBitmapSource )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->WriteSource( theBitmapSource, nullptr );
            CheckHRESULT( hr );
            return *this;
        }

        BitmapFrameEncode& BitmapFrameEncode::Commit( )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Commit( );
            CheckHRESULT( hr );
            return *this;
        }

        MetadataQueryWriter BitmapFrameEncode::GetMetadataQueryWriter( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICMetadataQueryWriter* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetMetadataQueryWriter( &result );
            CheckHRESULT( hr );
            return MetadataQueryWriter( factory, result );
        }

        // -----------------------------------------------------------------
        // ImageEncoder
        // -----------------------------------------------------------------
        ImageEncoder& ImageEncoder::WriteFrame( ID2D1Image* pImage, const BitmapFrameEncode& theFrameEncoder, const ImageParameters& theImageParameters )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->WriteFrame( pImage, theFrameEncoder, (WICImageParameters*)&theImageParameters );
            CheckHRESULT( hr );
            return *this;
        }

        ImageEncoder& ImageEncoder::WriteFrameThumbnail( ID2D1Image* pImage, const BitmapFrameEncode& theFrameEncoder, const ImageParameters& theImageParameters )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->WriteFrameThumbnail( pImage, theFrameEncoder, (WICImageParameters*)&theImageParameters );
            CheckHRESULT( hr );
            return *this;
        }

        ImageEncoder& ImageEncoder::WriteThumbnail( ID2D1Image* pImage, const BitmapEncoder& theEncoder, const ImageParameters& theImageParameters )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->WriteThumbnail( pImage, theEncoder, (WICImageParameters*)&theImageParameters );
            CheckHRESULT( hr );
            return *this;
        }

        // -----------------------------------------------------------------
        // BitmapDecoder
        // -----------------------------------------------------------------
        DWORD BitmapDecoder::QueryCapability( IStream* theStream ) const
        {
            DWORD result = 0;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->QueryCapability( theStream, &result );
            CheckHRESULT( hr );
            return result;
        }
        BitmapDecoder& BitmapDecoder::Initialize( IStream* theStream, DecodeOptions cacheOptions )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Initialize( theStream, WICDecodeOptions( cacheOptions ) );
            CheckHRESULT( hr );
            return *this;
        }
        const BitmapDecoder& BitmapDecoder::GetContainerFormat( GUID* pguidContainerFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetContainerFormat( pguidContainerFormat );
            CheckHRESULT( hr );
            return *this;
        }


        GUID BitmapDecoder::GetContainerFormat( ) const
        {
            GUID result = { 0, };
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetContainerFormat( &result );
            CheckHRESULT( hr );
            return result;
        }

        BitmapDecoderInfo BitmapDecoder::GetDecoderInfo( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapDecoderInfo* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetDecoderInfo( &result );
            CheckHRESULT( hr );
            return BitmapDecoderInfo( factory, result );
        }

        const BitmapDecoder& BitmapDecoder::CopyPalette( Palette& theTargetPalette ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CopyPalette( theTargetPalette );
            CheckHRESULT( hr );
            return *this;
        }

        Palette BitmapDecoder::CopyPalette( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }

            Palette thePalette = factory->CreatePalette( );
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CopyPalette( thePalette );
            CheckHRESULT( hr );
            return thePalette;
        }

        MetadataQueryReader BitmapDecoder::GetMetadataQueryReader( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICMetadataQueryReader* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetMetadataQueryReader( &result );
            CheckHRESULT( hr );
            return MetadataQueryReader( factory, result );
        }

        BitmapSource BitmapDecoder::GetPreview( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapSource* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPreview( &result );
            CheckHRESULT( hr );
            return BitmapSource( factory, result );
        }

        std::shared_ptr< std::vector<ColorContext> >  BitmapDecoder::GetColorContexts( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            auto result = std::make_shared< std::vector<ColorContext> >( );

            IWICColorContext* colorContexts[128];
            UINT actual = 0;
            InterfaceType* pInterface = GetInterface( );

            auto hr = pInterface->GetColorContexts( 128, colorContexts, &actual );
            CheckHRESULT( hr );

            for ( UINT i = 0; i < actual; i++ )
            {
                result->push_back( ColorContext( factory, colorContexts[i] ) );
            }
            return result;
        }

        BitmapSource BitmapDecoder::GetThumbnail( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapSource* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetThumbnail( &result );
            CheckHRESULT( hr );
            return BitmapSource( factory, result );
        }

        UINT BitmapDecoder::GetFrameCount( ) const
        {
            UINT result = 0;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetFrameCount( &result );
            CheckHRESULT( hr );
            return result;
        }

        BitmapFrameDecode BitmapDecoder::GetFrame( UINT index ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapFrameDecode* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetFrame( index, &result );
            CheckHRESULT( hr );
            return BitmapFrameDecode( factory, result );
        }

        // -----------------------------------------------------------------
        // BitmapSourceTransform
        // -----------------------------------------------------------------
        const BitmapSourceTransform& BitmapSourceTransform::CopyPixels( const Rectangle& rectangle, UINT uiWidth, UINT uiHeight, WICPixelFormatGUID* pguidDstFormat, BitmapTransformOptions dstTransform, UINT nStride, UINT cbBufferSize, BYTE* pbBuffer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CopyPixels( rectangle, uiWidth, uiHeight, pguidDstFormat, WICBitmapTransformOptions( dstTransform ), nStride, cbBufferSize, pbBuffer );
            CheckHRESULT( hr );
            return *this;
        }

        const BitmapSourceTransform& BitmapSourceTransform::GetClosestSize( UINT* puiWidth, UINT* puiHeight ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetClosestSize( puiWidth, puiHeight );
            CheckHRESULT( hr );
            return *this;
        }
        const BitmapSourceTransform& BitmapSourceTransform::GetClosestPixelFormat( WICPixelFormatGUID* pguidDstFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetClosestPixelFormat( pguidDstFormat );
            CheckHRESULT( hr );
            return *this;
        }
        bool BitmapSourceTransform::DoesSupportTransform( BitmapTransformOptions dstTransform ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result = FALSE;
            auto hr = pInterface->DoesSupportTransform( WICBitmapTransformOptions( dstTransform ), &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }

        // -----------------------------------------------------------------
        // BitmapFrameDecode
        // -----------------------------------------------------------------
        MetadataQueryReader BitmapFrameDecode::GetMetadataQueryReader( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICMetadataQueryReader* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetMetadataQueryReader( &result );
            CheckHRESULT( hr );
            return MetadataQueryReader( factory, result );
        }

        std::shared_ptr< std::vector<ColorContext> > BitmapFrameDecode::GetColorContexts( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            auto result = std::make_shared< std::vector<ColorContext> >( );

            IWICColorContext* colorContexts[128];
            UINT actual = 0;
            InterfaceType* pInterface = GetInterface( );

            auto hr = pInterface->GetColorContexts( 128, colorContexts, &actual );
            CheckHRESULT( hr );

            for ( UINT i = 0; i < actual; i++ )
            {
                result->push_back( ColorContext( factory, colorContexts[i] ) );
            }
            return result;
        }

        BitmapSource BitmapFrameDecode::GetThumbnail( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapSource* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetThumbnail( &result );
            CheckHRESULT( hr );
            return BitmapSource( factory, result );
        }

        // -----------------------------------------------------------------
        // BitmapCodecProgressNotification
        // -----------------------------------------------------------------
        BitmapCodecProgressNotification& BitmapCodecProgressNotification::RegisterProgressNotification( PFNProgressNotification pfnProgressNotification, LPVOID pvData, DWORD dwProgressFlags )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->RegisterProgressNotification( pfnProgressNotification, pvData, dwProgressFlags );
            CheckHRESULT( hr );
            return *this;
        }


        // -----------------------------------------------------------------
        // ComponentInfo
        // -----------------------------------------------------------------
        ComponentType ComponentInfo::GetComponentType( ) const
        {
            ComponentType result;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetComponentType( (WICComponentType*)&result );
            CheckHRESULT( hr );
            return result;
        }
        const ComponentInfo& ComponentInfo::GetCLSID( CLSID* pclsid ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetCLSID( pclsid );
            CheckHRESULT( hr );
            return *this;
        }
        CLSID ComponentInfo::GetCLSID( ) const
        {
            CLSID result = { 0, };
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetCLSID( &result );
            CheckHRESULT( hr );
            return result;
        }

        DWORD ComponentInfo::GetSigningStatus( ) const
        {
            DWORD result = 0;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetSigningStatus( &result );
            CheckHRESULT( hr );
            return result;
        }

        WideString ComponentInfo::GetAuthor( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            WCHAR buffer[1024];
            UINT actual = 0;
            auto hr = pInterface->GetAuthor( 1024, buffer, &actual );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actual ) );
        }

        const ComponentInfo& ComponentInfo::GetVendorGUID( GUID* pguidVendor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetVendorGUID( pguidVendor );
            CheckHRESULT( hr );
            return *this;
        }
        GUID ComponentInfo::GetVendorGUID( ) const
        {
            GUID result = { 0, };
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetVendorGUID( &result );
            CheckHRESULT( hr );
            return result;
        }

        WideString ComponentInfo::GetVersion( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            WCHAR buffer[1024];
            UINT actual = 0;
            auto hr = pInterface->GetVersion( 1024, buffer, &actual );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actual ) );
        }

        WideString ComponentInfo::GetSpecVersion( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            WCHAR buffer[1024];
            UINT actual = 0;
            auto hr = pInterface->GetSpecVersion( 1024, buffer, &actual );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actual ) );
        }

        WideString ComponentInfo::GetFriendlyName( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            WCHAR buffer[1024];
            UINT actual = 0;
            auto hr = pInterface->GetFriendlyName( 1024, buffer, &actual );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actual ) );
        }

        // -----------------------------------------------------------------
        // FormatConverterInfo
        // -----------------------------------------------------------------
        std::shared_ptr< std::vector<WICPixelFormatGUID> > FormatConverterInfo::GetPixelFormats( ) const
        {
            auto result = std::make_shared< std::vector<WICPixelFormatGUID> >( );
            InterfaceType* pInterface = GetInterface( );
            WICPixelFormatGUID buffer[64];
            UINT actual = 0;
            auto hr = pInterface->GetPixelFormats( 64, buffer, &actual );
            CheckHRESULT( hr );

            for ( UINT i = 0; i < actual; i++ )
            {
                result->push_back( buffer[i] );
            }

            return result;
        }
        FormatConverter FormatConverterInfo::CreateInstance( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICFormatConverter* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateInstance( &result );
            CheckHRESULT( hr );
            return FormatConverter( factory, result );
        }

        // -----------------------------------------------------------------
        // BitmapCodecInfo
        // -----------------------------------------------------------------
        const BitmapCodecInfo& BitmapCodecInfo::GetContainerFormat( GUID* pguidContainerFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetContainerFormat( pguidContainerFormat );
            CheckHRESULT( hr );
            return *this;
        }
        GUID BitmapCodecInfo::GetContainerFormat( ) const
        {
            GUID result = { 0, };
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetContainerFormat( &result );
            CheckHRESULT( hr );
            return result;
        }

        std::shared_ptr< std::vector<WICPixelFormatGUID> > BitmapCodecInfo::GetPixelFormats( ) const
        {
            auto result = std::make_shared< std::vector<WICPixelFormatGUID> >( );
            InterfaceType* pInterface = GetInterface( );
            WICPixelFormatGUID buffer[64];
            UINT actual = 0;
            auto hr = pInterface->GetPixelFormats( 64, buffer, &actual );
            CheckHRESULT( hr );

            for ( UINT i = 0; i < actual; i++ )
            {
                result->push_back( buffer[i] );
            }

            return result;
        }

        WideString BitmapCodecInfo::GetColorManagementVersion( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            WCHAR buffer[1024];
            UINT actual = 0;
            auto hr = pInterface->GetColorManagementVersion( 1024, buffer, &actual );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actual ) );
        }
        WideString BitmapCodecInfo::GetDeviceManufacturer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            WCHAR buffer[1024];
            UINT actual = 0;
            auto hr = pInterface->GetDeviceManufacturer( 1024, buffer, &actual );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actual ) );
        }
        WideString BitmapCodecInfo::GetDeviceModels( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            WCHAR buffer[1024];
            UINT actual = 0;
            auto hr = pInterface->GetDeviceModels( 1024, buffer, &actual );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actual ) );
        }
        WideString BitmapCodecInfo::GetMimeTypes( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            WCHAR buffer[1024];
            UINT actual = 0;
            auto hr = pInterface->GetMimeTypes( 1024, buffer, &actual );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actual ) );
        }
        WideString BitmapCodecInfo::GetFileExtensions( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            WCHAR buffer[1024];
            UINT actual = 0;
            auto hr = pInterface->GetFileExtensions( 1024, buffer, &actual );
            CheckHRESULT( hr );
            return WideString( buffer, size_t( actual ) );
        }

        bool BitmapCodecInfo::DoesSupportAnimation( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result = FALSE;
            auto hr = pInterface->DoesSupportAnimation( &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }

        bool BitmapCodecInfo::DoesSupportChromakey( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result = FALSE;
            auto hr = pInterface->DoesSupportChromakey( &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }
        bool BitmapCodecInfo::DoesSupportLossless( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result = FALSE;
            auto hr = pInterface->DoesSupportLossless( &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }
        bool BitmapCodecInfo::DoesSupportMultiframe( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result = FALSE;
            auto hr = pInterface->DoesSupportMultiframe( &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }
        bool BitmapCodecInfo::MatchesMimeType( LPCWSTR wzMimeType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result = FALSE;
            auto hr = pInterface->MatchesMimeType( wzMimeType, &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }
        bool BitmapCodecInfo::MatchesMimeType( const WideString& theMimeType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            BOOL result = FALSE;
            auto hr = pInterface->MatchesMimeType( theMimeType.c_str( ), &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }

        // -----------------------------------------------------------------
        // BitmapEncoderInfo
        // -----------------------------------------------------------------
        BitmapEncoder BitmapEncoderInfo::CreateInstance( )
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapEncoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateInstance( &result );
            CheckHRESULT( hr );
            return BitmapEncoder( factory, result );
        }

        // -----------------------------------------------------------------
        // BitmapDecoderInfo
        // -----------------------------------------------------------------
        std::shared_ptr< std::vector<BitmapPattern> > BitmapDecoderInfo::GetPatterns( ) const
        {

            InterfaceType* pInterface = GetInterface( );

            UINT actual = 0;
            UINT actualBufferSize = 0;
            auto hr = pInterface->GetPatterns( 0, nullptr, &actual, &actualBufferSize );
            CheckHRESULT( hr );
            auto result = std::make_shared< std::vector<BitmapPattern> >( actual );

            hr = pInterface->GetPatterns( actual, (WICBitmapPattern*)result->data( ), &actual, &actualBufferSize );
            CheckHRESULT( hr );
            return result;
        }

        bool BitmapDecoderInfo::MatchesPattern( IStream* theStream ) const
        {
            BOOL result = FALSE;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->MatchesPattern( theStream, &result );
            CheckHRESULT( hr );
            return result != FALSE;
        }

        BitmapDecoder BitmapDecoderInfo::CreateInstance( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateInstance( &result );
            CheckHRESULT( hr );
            return BitmapDecoder( factory, result );
        }

        // -----------------------------------------------------------------
        // PixelFormatInfo
        // -----------------------------------------------------------------
        const PixelFormatInfo& PixelFormatInfo::GetFormatGUID( GUID* pFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetFormatGUID( pFormat );
            CheckHRESULT( hr );
            return *this;
        }

        ColorContext PixelFormatInfo::GetColorContext( ) const
        {
            ImagingFactory* factory = Factory( );
            if ( !factory )
            {
                throw InvalidOperationException( L"ImagingFactory is not assigned" );
            }
            IWICColorContext* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetColorContext( &result );
            CheckHRESULT( hr );
            return ColorContext( factory, result );
        }

        UINT PixelFormatInfo::GetBitsPerPixel( ) const
        {
            UINT result = 0;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetBitsPerPixel( &result );
            CheckHRESULT( hr );
            return *this;
        }

        UINT PixelFormatInfo::GetChannelCount( ) const
        {
            UINT result = 0;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetChannelCount( &result );
            CheckHRESULT( hr );
            return *this;
        }

        std::shared_ptr< std::vector<BYTE> > PixelFormatInfo::GetChannelMask( UINT uiChannelIndex ) const
        {
            UINT actual;
            BYTE buffer[512];
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetChannelMask( uiChannelIndex, 512, buffer, &actual );
            CheckHRESULT( hr );
            auto result = std::make_shared< std::vector<BYTE> >( buffer, buffer + actual );
            return result;
        }

        // IWICPixelFormatInfo2
        // bool PixelFormatInfo::SupportsTransparency( ) const

        //  PixelFormatNumericRepresentation PixelFormatInfo::GetNumericRepresentation( ) const

        // -----------------------------------------------------------------
        // ImagingFactory
        // -----------------------------------------------------------------

        ImagingFactory ImagingFactory::Create( )
        {
            IWICImagingFactory* pIWICFactory = nullptr;
            HRESULT hr = CoCreateInstance( CLSID_WICImagingFactory1, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &pIWICFactory ) );
            CheckHRESULT( hr );

            ImagingFactory result( pIWICFactory );
            return result;
        }

        BitmapDecoder ImagingFactory::CreateDecoderFromFilename( LPCWSTR theFilename, const GUID* pguidVendor, DWORD dwDesiredAccess, DecodeOptions metadataOptions ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoderFromFilename( theFilename, pguidVendor, dwDesiredAccess, WICDecodeOptions( metadataOptions ), &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }
        BitmapDecoder ImagingFactory::CreateDecoderFromFilename( LPCWSTR theFilename, DWORD dwDesiredAccess, DecodeOptions metadataOptions ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoderFromFilename( theFilename, nullptr, dwDesiredAccess, WICDecodeOptions( metadataOptions ), &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }
        BitmapDecoder ImagingFactory::CreateDecoderFromFilename( LPCWSTR theFilename ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoderFromFilename( theFilename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }
        BitmapDecoder ImagingFactory::CreateDecoderFromFilename( const WideString& theFilename, const GUID* pguidVendor, DWORD dwDesiredAccess, DecodeOptions metadataOptions ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoderFromFilename( theFilename.c_str( ), pguidVendor, dwDesiredAccess, WICDecodeOptions( metadataOptions ), &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }
        BitmapDecoder ImagingFactory::CreateDecoderFromFilename( const WideString& theFilename, DWORD dwDesiredAccess, DecodeOptions metadataOptions ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoderFromFilename( theFilename.c_str( ), nullptr, dwDesiredAccess, WICDecodeOptions( metadataOptions ), &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }
        BitmapDecoder ImagingFactory::CreateDecoderFromFilename( const WideString& theFilename ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoderFromFilename( theFilename.c_str( ), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }

        BitmapDecoder ImagingFactory::CreateDecoderFromStream( IStream* theStream, const GUID* pguidVendor, DecodeOptions metadataOptions ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoderFromStream( theStream, pguidVendor, WICDecodeOptions( metadataOptions ), &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }
        BitmapDecoder ImagingFactory::CreateDecoderFromStream( IStream* theStream, DecodeOptions metadataOptions ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoderFromStream( theStream, nullptr, WICDecodeOptions( metadataOptions ), &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }

        BitmapDecoder ImagingFactory::CreateDecoderFromFileHandle( ULONG_PTR hFile, const GUID* pguidVendor, DecodeOptions metadataOptions ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoderFromFileHandle( hFile, pguidVendor, WICDecodeOptions( metadataOptions ), &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }

        ComponentInfo ImagingFactory::CreateComponentInfo( REFCLSID clsidComponent ) const
        {
            IWICComponentInfo* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateComponentInfo( clsidComponent, &result );
            CheckHRESULT( hr );
            return ComponentInfo( const_cast<ImagingFactory*>( this ), result );
        }

        BitmapDecoder ImagingFactory::CreateDecoder( REFGUID guidContainerFormat, const GUID* pguidVendor ) const
        {
            IWICBitmapDecoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDecoder( guidContainerFormat, pguidVendor, &result );
            CheckHRESULT( hr );
            return BitmapDecoder( const_cast<ImagingFactory*>( this ), result );
        }

        BitmapEncoder ImagingFactory::CreateEncoder( REFGUID guidContainerFormat, const GUID* pguidVendor ) const
        {
            IWICBitmapEncoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateEncoder( guidContainerFormat, pguidVendor, &result );
            CheckHRESULT( hr );
            return BitmapEncoder( const_cast<ImagingFactory*>( this ), result );
        }

        BitmapEncoder ImagingFactory::CreateBMPEncoder( ) const
        {
            return CreateEncoder( GUID_ContainerFormatBmp, nullptr );
        }
        BitmapEncoder ImagingFactory::CreatePNGEncoder( ) const
        {
            return CreateEncoder( GUID_ContainerFormatPng, nullptr );
        }
        BitmapEncoder ImagingFactory::CreateICOEncoder( ) const
        {
            return CreateEncoder( GUID_ContainerFormatIco, nullptr );
        }
        BitmapEncoder ImagingFactory::CreateJPEGEncoder( ) const
        {
            return CreateEncoder( GUID_ContainerFormatJpeg, nullptr );
        }
        BitmapEncoder ImagingFactory::CreateTIFFEncoder( ) const
        {
            return CreateEncoder( GUID_ContainerFormatTiff, nullptr );
        }
        BitmapEncoder ImagingFactory::CreateGIFEncoder( ) const
        {
            return CreateEncoder( GUID_ContainerFormatGif, nullptr );
        }
        BitmapEncoder ImagingFactory::CreateWMPEncoder( ) const
        {
            return CreateEncoder( GUID_ContainerFormatWmp, nullptr );
        }


        Palette ImagingFactory::CreatePalette( ) const
        {
            IWICPalette* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreatePalette( &result );
            CheckHRESULT( hr );
            return Palette( const_cast<ImagingFactory*>( this ), result );
        }

        FormatConverter ImagingFactory::CreateFormatConverter( ) const
        {
            IWICFormatConverter* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateFormatConverter( &result );
            CheckHRESULT( hr );
            return FormatConverter( const_cast<ImagingFactory*>( this ), result );
        }

        BitmapScaler ImagingFactory::CreateBitmapScaler( ) const
        {
            IWICBitmapScaler* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapScaler( &result );
            CheckHRESULT( hr );
            return BitmapScaler( const_cast<ImagingFactory*>( this ), result );
        }

        BitmapClipper ImagingFactory::CreateBitmapClipper( ) const
        {
            IWICBitmapClipper* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapClipper( &result );
            CheckHRESULT( hr );
            return BitmapClipper( const_cast<ImagingFactory*>( this ), result );
        }

        BitmapFlipRotator ImagingFactory::CreateBitmapFlipRotator( ) const
        {
            IWICBitmapFlipRotator* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapFlipRotator( &result );
            CheckHRESULT( hr );
            return BitmapFlipRotator( const_cast<ImagingFactory*>( this ), result );
        }

        Stream ImagingFactory::CreateStream( ) const
        {
            IWICStream* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateStream( &result );
            CheckHRESULT( hr );
            return Stream( const_cast<ImagingFactory*>( this ), result );
        }

        ColorContext ImagingFactory::CreateColorContext( ) const
        {
            IWICColorContext* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateColorContext( &result );
            CheckHRESULT( hr );
            return ColorContext( const_cast<ImagingFactory*>( this ), result );
        }

        ColorTransform ImagingFactory::CreateColorTransformer( ) const
        {
            IWICColorTransform* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateColorTransformer( &result );
            CheckHRESULT( hr );
            return ColorTransform( const_cast<ImagingFactory*>( this ), result );
        }

        Bitmap ImagingFactory::CreateBitmap( UINT uiWidth, UINT uiHeight, REFWICPixelFormatGUID pixelFormat, BitmapCreateCacheOption option ) const
        {
            IWICBitmap* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmap( uiWidth, uiHeight, pixelFormat, WICBitmapCreateCacheOption( option ), &result );
            CheckHRESULT( hr );
            return Bitmap( const_cast<ImagingFactory*>( this ), result );
        }

        Bitmap ImagingFactory::CreateBitmapFromSource( const BitmapSource& theBitmapSource, BitmapCreateCacheOption option ) const
        {
            IWICBitmap* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapFromSource( theBitmapSource, WICBitmapCreateCacheOption( option ), &result );
            CheckHRESULT( hr );
            return Bitmap( const_cast<ImagingFactory*>( this ), result );
        }

        Bitmap ImagingFactory::CreateBitmapFromSourceRect( const BitmapSource& theBitmapSource, UINT x, UINT y, UINT width, UINT height ) const
        {
            IWICBitmap* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapFromSourceRect( theBitmapSource, x, y, width, height, &result );
            CheckHRESULT( hr );
            return Bitmap( const_cast<ImagingFactory*>( this ), result );
        }

        Bitmap ImagingFactory::CreateBitmapFromMemory( UINT uiWidth, UINT uiHeight, REFWICPixelFormatGUID pixelFormat, UINT cbStride, UINT cbBufferSize, BYTE* pbBuffer ) const
        {
            IWICBitmap* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapFromMemory( uiWidth, uiHeight, pixelFormat, cbStride, cbBufferSize, pbBuffer, &result );
            CheckHRESULT( hr );
            return Bitmap( const_cast<ImagingFactory*>( this ), result );
        }

        Bitmap ImagingFactory::CreateBitmapFromHBITMAP( HBITMAP hBitmap, HPALETTE hPalette, BitmapAlphaChannelOption options ) const
        {
            IWICBitmap* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapFromHBITMAP( hBitmap, hPalette, WICBitmapAlphaChannelOption( options ), &result );
            CheckHRESULT( hr );
            return Bitmap( const_cast<ImagingFactory*>( this ), result );
        }

        Bitmap ImagingFactory::CreateBitmapFromHICON( HICON hIcon ) const
        {
            IWICBitmap* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateBitmapFromHICON( hIcon, &result );
            CheckHRESULT( hr );
            return Bitmap( const_cast<ImagingFactory*>( this ), result );
        }

        const ImagingFactory& ImagingFactory::CreateComponentEnumerator( DWORD componentTypes, DWORD options, IEnumUnknown** ppIEnumUnknown ) const
        {
            IWICBitmap* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateComponentEnumerator( componentTypes, options, ppIEnumUnknown );
            CheckHRESULT( hr );
            return *this;
        }

        FastMetadataEncoder ImagingFactory::CreateFastMetadataEncoderFromDecoder( const BitmapDecoder& theDecoder ) const
        {
            IWICFastMetadataEncoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateFastMetadataEncoderFromDecoder( theDecoder, &result );
            CheckHRESULT( hr );
            return FastMetadataEncoder( const_cast<ImagingFactory*>( this ), result );
        }

        FastMetadataEncoder ImagingFactory::CreateFastMetadataEncoderFromFrameDecode( const BitmapFrameDecode& theFrameDecoder ) const
        {
            IWICFastMetadataEncoder* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateFastMetadataEncoderFromFrameDecode( theFrameDecoder, &result );
            CheckHRESULT( hr );
            return FastMetadataEncoder( const_cast<ImagingFactory*>( this ), result );
        }

        MetadataQueryWriter ImagingFactory::CreateQueryWriter( REFGUID guidMetadataFormat, const GUID* pguidVendor ) const
        {
            IWICMetadataQueryWriter* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateQueryWriter( guidMetadataFormat, pguidVendor, &result );
            CheckHRESULT( hr );
            return MetadataQueryWriter( const_cast<ImagingFactory*>( this ), result );
        }

        MetadataQueryWriter ImagingFactory::CreateQueryWriterFromReader( const MetadataQueryReader& theQueryReader, const GUID* pguidVendor ) const
        {
            IWICMetadataQueryWriter* result = nullptr;
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateQueryWriterFromReader( theQueryReader, pguidVendor, &result );
            CheckHRESULT( hr );
            return MetadataQueryWriter( const_cast<ImagingFactory*>( this ), result );
        }

    };
}