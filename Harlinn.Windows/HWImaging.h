#pragma once
#ifndef __HWIMAGING_H__
#define __HWIMAGING_H__
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

#include <HWDef.h>
#include <HCCException.h>
#include <HCCString.h>
#include <HCCComImpl.h>

namespace Harlinn::Windows
{
    class Control;
    class BitmapHandle;
    using Unknown = Common::Core::Unknown;
}

namespace Harlinn::Windows::Graphics
{
    namespace Imaging
    {




#define HW_IMAGING_STANDARD_METHODS_IMPL( classType, baseClassType , interfaceType, baseInterfaceType ) \
    public: \
    typedef interfaceType InterfaceType; \
    typedef baseInterfaceType BaseInterfaceType; \
    private: \
     InterfaceType * GetInterface() const { if(!unknown_) { ThrowNoInterface(); } return reinterpret_cast< InterfaceType *>( unknown_ ); } \
    public: \
    classType () \
     : baseClassType ( ) \
     {} \
    explicit classType (interfaceType * theInterface, bool addref = false ) \
     : baseClassType ( reinterpret_cast< baseInterfaceType *>( theInterface ), addref ) \
     {} \
    protected: \
    classType (REFIID iid, const Unknown& theUnknown, bool throwIfNoInterface = true ) \
     : baseClassType ( iid, reinterpret_cast< const baseClassType & > (theUnknown), throwIfNoInterface ) \
     { } \
    public: \
    classType ( const Unknown& theUnknown, bool throwIfNoInterface = true ) \
     : baseClassType ( __uuidof(interfaceType), reinterpret_cast< const baseClassType & > (theUnknown), throwIfNoInterface ) \
     { } \
    classType ( ImagingFactory* theFactory, interfaceType * theInterface ) \
     : baseClassType ( theFactory, reinterpret_cast< baseInterfaceType *>( theInterface ) ) \
     { } \
    classType (const classType & other) \
     : baseClassType ( reinterpret_cast< const baseClassType & > (other) ) \
     { } \
    classType (classType && other) noexcept \
     : baseClassType ( reinterpret_cast< baseClassType && >( other ) ) \
     { } \
    classType & operator = (const classType & other) \
     { \
       baseClassType :: operator = ( reinterpret_cast< const baseClassType & > (other) ); \
       return *this; \
     } \
    classType & operator = (classType && other) noexcept \
     { \
       baseClassType :: operator = ( reinterpret_cast< baseClassType && > (other) ); \
       return *this; \
     } \
    operator interfaceType * ( ) const\
     { \
       return reinterpret_cast< interfaceType * >( unknown_ ); \
     }


        typedef UINT32 Color;
        /// <summary>
        /// Represents a rectangle for Windows Imaging Component (WIC) API.
        /// </summary>
        class Rectangle
        {
            INT x;
            INT y;
            INT width;
            INT height;
        public:
            Rectangle( )
                : x( 0 ), y( 0 ), width( 0 ), height( 0 )
            {
            }

            Rectangle( const POINT& pt )
                : x( pt.x ), y( pt.y ), width( 0 ), height( 0 )
            {
            }

            Rectangle( const SIZE& size )
                : x( 0 ), y( 0 ), width( size.cx ), height( size.cy )
            {
            }

            Rectangle( const POINT& pt, const SIZE& size )
                : x( pt.x ), y( pt.y ), width( size.cx ), height( size.cy )
            {
            }

            int X( ) const
            {
                return x;
            }
            Rectangle& SetX( int theValue )
            {
                x = theValue;
                return *this;
            }
            int Y( ) const
            {
                return y;
            }
            Rectangle& SetY( int theValue )
            {
                y = theValue;
                return *this;
            }

            int Width( ) const
            {
                return width;
            }
            Rectangle& SetWidth( int theWidth )
            {
                width = theWidth;
                return *this;
            }
            int Height( ) const
            {
                return height;
            }
            Rectangle& SetHeight( int theValue )
            {
                height = theValue;
                return *this;
            }


            operator WICRect& ( )
            {
                return *( (WICRect*)&x );
            }
            operator const WICRect& ( ) const
            {
                return *( (WICRect*)&x );
            }

            //operator WICRect* () { return ((WICRect*)&x); }
            operator WICRect* ( ) const
            {
                return ( (WICRect*)&x );
            }
        };


        class Size
        {
            UINT width;
            UINT height;
        public:
            Size( )
                : width( 0 ), height( 0 )
            {
            }


            Size( UINT theWidth, UINT theHeight )
                : width( theWidth ), height( theHeight )
            {
            }

            explicit Size( UINT theValue )
                : width( theValue ), height( theValue )
            {
            }

            Size( const POINT& pt )
                : width( UINT( pt.x ) ), height( UINT( pt.y ) )
            {
            }

            Size( const SIZE& size )
                : width( UINT( size.cx ) ), height( UINT( size.cy ) )
            {
            }

            Size( const Size& size )
                : width( size.width ), height( size.height )
            {
            }

            Size& operator = ( const SIZE& size )
            {
                width = UINT( size.cx );
                height = UINT( size.cy );
                return *this;
            }

            Size& operator = ( const POINT& pt )
            {
                width = UINT( pt.x );
                height = UINT( pt.y );
                return *this;
            }

            Size& operator = ( const Size& size )
            {
                width = size.width;
                height = size.height;
                return *this;
            }


            UINT Width( ) const
            {
                return width;
            }
            Size& SetWidth( UINT theWidth )
            {
                width = theWidth;
                return *this;
            }
            UINT Height( ) const
            {
                return height;
            }
            Size& SetHeight( UINT theValue )
            {
                height = theValue;
                return *this;
            }
            Size& Set( UINT theWidth, UINT theHeight )
            {
                width = theWidth;
                height = theHeight;
                return *this;
            }

        };


        class Resolution
        {
            double dpiX;
            double dpiY;
        public:
            Resolution( )
                : dpiX( 0.0 ), dpiY( 0.0 )
            {
            }

            Resolution( double x, double y )
                : dpiX( x ), dpiY( y )
            {
            }

            double X( ) const
            {
                return dpiX;
            }
            Resolution& SetX( double theValue )
            {
                dpiX = theValue;
                return *this;
            }
            double Y( ) const
            {
                return dpiY;
            }
            Resolution& SetY( double theValue )
            {
                dpiY = theValue;
                return *this;
            }
            Resolution& Set( double theXValue, double theYValue )
            {
                dpiX = theXValue;
                dpiY = theYValue;
                return *this;
            }

        };


        enum class ColorContextType
        {
            Uninitialized = 0,
            Profile = 0x1,
            ExifColorSpace = 0x2
        };

        enum class BitmapCreateCacheOption : DWORD
        {
            NoCache = 0,
            CacheOnDemand = 0x1,
            CacheOnLoad = 0x2
        };

        enum class DecodeOptions : DWORD
        {
            CacheOnDemand = 0,
            CacheOnLoad = 0x1
        };

        enum class BitmapEncoderCacheOption : DWORD
        {
            InMemory = 0,
            TempFile = 0x1,
            NoCache = 0x2
        };

        enum class ComponentType : DWORD
        {
            Decoder = 0x1,
            Encoder = 0x2,
            PixelFormatConverter = 0x4,
            MetadataReader = 0x8,
            MetadataWriter = 0x10,
            PixelFormat = 0x20,
            AllComponents = 0x3f
        };

        enum class ComponentEnumerateOptions : DWORD
        {
            Default = 0,
            Refresh = 0x1,
            Disabled = 0x80000000,
            Unsigned = 0x40000000,
            BuiltInOnly = 0x20000000
        };


        struct BitmapPattern
        {
            unsigned long long Position;
            unsigned long Length;
            BYTE* Pattern;
            BYTE* Mask;
            BOOL EndOfStream;
        };

        enum class BitmapInterpolationMode : DWORD
        {
            NearestNeighbor = 0,
            Linear = 0x1,
            Cubic = 0x2,
            Fant = 0x3
        };

        enum class BitmapPaletteType : DWORD
        {
            Custom = 0,
            MedianCut = 0x1,
            FixedBW = 0x2,
            FixedHalftone8 = 0x3,
            FixedHalftone27 = 0x4,
            FixedHalftone64 = 0x5,
            FixedHalftone125 = 0x6,
            FixedHalftone216 = 0x7,
            FixedWebPalette = WICBitmapPaletteTypeFixedHalftone216,
            FixedHalftone252 = 0x8,
            FixedHalftone256 = 0x9,
            FixedGray4 = 0xa,
            FixedGray16 = 0xb,
            FixedGray256 = 0xc
        };


        enum class BitmapDitherType : DWORD
        {
            None = 0,
            Solid = 0,
            Ordered4x4 = 0x1,
            Ordered8x8 = 0x2,
            Ordered16x16 = 0x3,
            Spiral4x4 = 0x4,
            Spiral8x8 = 0x5,
            DualSpiral4x4 = 0x6,
            DualSpiral8x8 = 0x7,
            ErrorDiffusion = 0x8
        };

        enum class BitmapAlphaChannelOption : DWORD
        {
            UseAlpha = 0,
            UsePremultipliedAlpha = 0x1,
            IgnoreAlpha = 0x2
        };

        enum class BitmapTransformOptions : DWORD
        {
            Rotate0 = 0,
            Rotate90 = 0x1,
            Rotate180 = 0x2,
            Rotate270 = 0x3,
            FlipHorizontal = 0x8,
            FlipVertical = 0x10
        };

        enum class BitmapLockFlags : DWORD
        {
            Read = 0x1,
            Write = 0x2,
        };

        enum class BitmapDecoderCapabilities : DWORD
        {
            SameEncoder = 0x1,
            CanDecodeAllImages = 0x2,
            CanDecodeSomeImages = 0x4,
            CanEnumerateMetadata = 0x8,
            CanDecodeThumbnail = 0x10
        };

        enum class ProgressOperation : DWORD
        {
            WICProgressOperationCopyPixels = 0x1,
            WICProgressOperationWritePixels = 0x2,
            WICProgressOperationAll = 0xffff
        };

        enum class WICProgressNotification : DWORD
        {
            Begin = 0x10000,
            End = 0x20000,
            Frequent = 0x40000,
            All = 0xffff0000
        };

        enum class ComponentSigning : DWORD
        {
            Signed = 0x1,
            Unsigned = 0x2,
            Safe = 0x4,
            Disabled = 0x80000000
        };

        enum class GifLogicalScreenDescriptorProperties : DWORD
        {
            Signature = 0x1,
            Width = 0x2,
            Height = 0x3,
            GlobalColorTableFlag = 0x4,
            ColorResolution = 0x5,
            SortFlag = 0x6,
            GlobalColorTableSize = 0x7,
            BackgroundColorIndex = 0x8,
            PixelAspectRatio = 0x9
        };

        enum class GifImageDescriptorProperties : DWORD
        {
            Left = 0x1,
            Top = 0x2,
            Width = 0x3,
            Height = 0x4,
            LocalColorTableFlag = 0x5,
            InterlaceFlag = 0x6,
            SortFlag = 0x7,
            LocalColorTableSize = 0x8
        };

        enum class GifGraphicControlExtensionProperties : DWORD
        {
            Disposal = 0x1,
            UserInputFlag = 0x2,
            TransparencyFlag = 0x3,
            Delay = 0x4,
            TransparentColorIndex = 0x5
        };

        enum class GifApplicationExtensionProperties : DWORD
        {
            Application = 0x1,
            Data = 0x2
        };

        enum class GifCommentExtensionProperties : DWORD
        {
            Text = 0x1
        };

        enum class JpegCommentProperties : DWORD
        {
            Text = 0x1
        };

        enum class JpegLuminanceProperties : DWORD
        {
            Table = 0x1
        };

        enum class JpegChrominanceProperties : DWORD
        {
            Table = 0x1
        };

        enum class EightBIMIptcProperties : DWORD
        {
            PString = 0,
            EmbeddedIPTC = 0x1,
        };

        enum class EightBIMResolutionInfoProperties : DWORD
        {
            PString = 0x1,
            HResolution = 0x2,
            HResolutionUnit = 0x3,
            WidthUnit = 0x4,
            VResolution = 0x5,
            VResolutionUnit = 0x6,
            HeightUnit = 0x7,
        };

        enum class EightBIMIptcDigestProperties : DWORD
        {
            PString = 0x1,
            IptcDigest = 0x2
        };

        enum class PngGamaProperties : DWORD
        {
            Gamma = 0x1
        };

        enum class PngBkgdProperties : DWORD
        {
            BackgroundColor = 0x1
        };

        enum class PngItxtProperties : DWORD
        {
            Keyword = 0x1,
            CompressionFlag = 0x2,
            LanguageTag = 0x3,
            TranslatedKeyword = 0x4,
            Text = 0x5
        };

        enum class PngChrmProperties : DWORD
        {
            WhitePointX = 0x1,
            WhitePointY = 0x2,
            RedX = 0x3,
            RedY = 0x4,
            GreenX = 0x5,
            GreenY = 0x6,
            BlueX = 0x7,
            BlueY = 0x8
        };

        enum class PngHistProperties : DWORD
        {
            Frequencies = 0x1
        };

        enum class PngIccpProperties : DWORD
        {
            ProfileName = 0x1,
            ProfileData = 0x2
        };

        enum class PngSrgbProperties : DWORD
        {
            RenderingIntent = 0x1
        };

        enum class PngTimeProperties : DWORD
        {
            Year = 0x1,
            Month = 0x2,
            Day = 0x3,
            Hour = 0x4,
            Minute = 0x5,
            Second = 0x6
        };

        enum class SectionAccessLevel : DWORD
        {
            Read = 0x1,
            ReadWrite = 0x3
        };

        enum class PixelFormatNumericRepresentation : DWORD
        {
            Unspecified = 0,
            Indexed = 0x1,
            UnsignedInteger = 0x2,
            SignedInteger = 0x3,
            Fixed = 0x4,
            Float = 0x5
        };

        struct ImageParameters
        {
            D2D1_PIXEL_FORMAT PixelFormat;
            FLOAT DpiX;
            FLOAT DpiY;
            FLOAT Top;
            FLOAT Left;
            UINT32 PixelWidth;
            UINT32 PixelHeight;
        };

        class BitmapSource;
        class ImagingFactory;
        class ImagingObject : public Unknown
        {
            ImagingFactory* factory_ = nullptr;
        protected:
            ImagingFactory* Factory( ) const
            {
                return factory_;
            }
        public:
            typedef Unknown Base;

            ImagingObject( )
                : Base( ),
                 factory_( nullptr )
            {
            }
            explicit ImagingObject( IUnknown* theInterface, bool addref = false )
                : Base( reinterpret_cast<IUnknown*>( theInterface ), addref ),
                  factory_( nullptr )
            {
            }

            ImagingObject( ImagingFactory* theFactory, IUnknown* theInterface )
                : Base( reinterpret_cast<IUnknown*>( theInterface ) ),
                  factory_( theFactory )
            {
            }
        protected:
            ImagingObject( REFIID iid, const Unknown& theUnknown, bool throwIfNoInterface = true )
                : Base( iid, theUnknown, throwIfNoInterface )
            {
            }
        public:
            ImagingObject( const ImagingObject& other )
                : Base( reinterpret_cast<const Base&> ( other ) ),
                  factory_( other.factory_ )
            {
            }
            ImagingObject( ImagingObject&& other ) noexcept
                : Base( reinterpret_cast<Base&&>( other ) ),
                  factory_( other.factory_ )
            {
                other.factory_ = nullptr;
            }
            ImagingObject& operator = ( const ImagingObject& other )
            {
                Base :: operator = ( reinterpret_cast<const Base&> ( other ) );
                factory_ = other.factory_;
                return *this;
            }
            ImagingObject& operator = ( ImagingObject&& other ) noexcept
            {
                Base :: operator = ( reinterpret_cast<Base&&> ( other ) );
                std::swap( factory_, other.factory_ );
                return *this;
            }



        };

        /// <summary>
        /// Exposes methods for accessing and building a color table, primarily for indexed pixel formats.
        /// </summary>
        class Palette : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( Palette, ImagingObject, IWICPalette, IUnknown )

            HW_EXPORT Palette& InitializePredefined( BitmapPaletteType ePaletteType, bool addTransparentColor );

            HW_EXPORT Palette& InitializeCustom( Color* pColors, UINT cCount );
            HW_EXPORT Palette& InitializeCustom( const std::vector< Color >& theColors );
            HW_EXPORT Palette& InitializeCustom( std::shared_ptr<const std::vector< Color >>& theColors );

            HW_EXPORT Palette& InitializeFromBitmap( const BitmapSource& theSurface, UINT cCount, bool addTransparentColor );

            HW_EXPORT Palette& InitializeFromPalette( const Palette& thePalette );

            HW_EXPORT BitmapPaletteType Type( ) const;

            HW_EXPORT UINT GetColorCount( ) const;

            HW_EXPORT std::shared_ptr<std::vector< Color > > Colors( ) const;

            HW_EXPORT bool IsBlackWhite( ) const;
            HW_EXPORT bool IsGrayscale( ) const;
            HW_EXPORT bool HasAlpha( ) const;
        };


        class FormatConverter;
        class BitmapScaler;
        class BitmapClipper;
        class BitmapFlipRotator;
        class ColorTransform;
        class Bitmap;

        /// <summary>
        /// Exposes methods that refers to a source from which pixels are retrieved, but cannot be written back to.
        /// </summary>
        class BitmapSource : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapSource, ImagingObject, IWICBitmapSource, IUnknown )

            HW_EXPORT const BitmapSource& GetSize( UINT* puiWidth, UINT* puiHeight ) const;
            HW_EXPORT Size GetSize( ) const;
            HW_EXPORT const BitmapSource& GetPixelFormat( WICPixelFormatGUID* pPixelFormat ) const;
            HW_EXPORT WICPixelFormatGUID GetPixelFormat( ) const;
            HW_EXPORT const BitmapSource& GetResolution( double* pDpiX, double* pDpiY ) const;
            HW_EXPORT Resolution GetResolution( ) const;

            HW_EXPORT const BitmapSource& CopyPalette( Palette& theTargetPalette ) const;
            HW_EXPORT Palette CopyPalette( ) const;


            HW_EXPORT const BitmapSource& CopyPixels( Rectangle& rectangle, UINT bytePerStride, UINT bufferSize, BYTE* pbBuffer ) const;
            HW_EXPORT const BitmapSource& CopyPixels( UINT bytePerStride, UINT bufferSize, BYTE* pbBuffer ) const;

            HW_EXPORT FormatConverter Convert( REFGUID dstFormat, BitmapDitherType dither, const Palette& thePalette, double alphaThresholdPercent, BitmapPaletteType paletteTranslate ) const;
            HW_EXPORT FormatConverter Convert( REFGUID dstFormat ) const;
            HW_EXPORT FormatConverter Convert( ) const;
            HW_EXPORT BitmapScaler Scale( UINT uiWidth, UINT uiHeight, BitmapInterpolationMode mode = BitmapInterpolationMode::Fant ) const;
            HW_EXPORT BitmapScaler Scale( const Size& size, BitmapInterpolationMode mode = BitmapInterpolationMode::Fant ) const;
            HW_EXPORT BitmapClipper Clip( const Rectangle& reactangle ) const;
            HW_EXPORT BitmapFlipRotator Rotate( BitmapTransformOptions options ) const;
            HW_EXPORT Bitmap ToBitmap( ) const;

            HW_EXPORT BitmapHandle AsBitmapHandle( ) const;


        };

        /// <summary>
        /// Represents a BitmapSource that converts the image data from one 
        /// pixel format to another, handling dithering and halftoning to 
        /// indexed formats, palette translation and alpha thresholding.
        /// </summary>
        class FormatConverter : public BitmapSource
        {
        public:
            typedef BitmapSource Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( FormatConverter, BitmapSource, IWICFormatConverter, IWICBitmapSource )

            HW_EXPORT FormatConverter& Initialize( const BitmapSource& theSource, REFGUID dstFormat, BitmapDitherType dither, const Palette& thePalette, double alphaThresholdPercent, BitmapPaletteType paletteTranslate );
            HW_EXPORT FormatConverter& Initialize( const BitmapSource& theSource, REFGUID dstFormat, double alphaThresholdPercent, BitmapPaletteType paletteTranslate );

            HW_EXPORT bool CanConvert( REFGUID  srcPixelFormat, REFGUID  dstPixelFormat ) const;

        };

        /// <summary>
        /// Represents a resized version of the input bitmap using a resampling or filtering algorithm.
        /// </summary>
        class BitmapScaler : public BitmapSource
        {
        public:
            typedef BitmapSource Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapScaler, BitmapSource, IWICBitmapScaler, IWICBitmapSource )

            HW_EXPORT BitmapScaler& Initialize( const BitmapSource& theSource, UINT uiWidth, UINT uiHeight, BitmapInterpolationMode mode = BitmapInterpolationMode::Fant );
            HW_EXPORT BitmapScaler& Initialize( const BitmapSource& theSource, const Size& theSize, BitmapInterpolationMode mode = BitmapInterpolationMode::Fant );
        };

        /// <summary>
        /// Exposes methods that produce a clipped version of the input bitmap for a specified rectangular region of interest.
        /// </summary>
        class BitmapClipper : public BitmapSource
        {
        public:
            typedef BitmapSource Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapClipper, BitmapSource, IWICBitmapClipper, IWICBitmapSource )

            HW_EXPORT BitmapClipper& Initialize( const BitmapSource& theSource, const Rectangle& reactangle );

        };

        /// <summary>
        /// Exposes methods that produce a flipped (horizontal or vertical) 
        /// and/or rotated (by 90 degree increments) bitmap source. The flip 
        /// is done before the rotation.
        /// </summary>
        class BitmapFlipRotator : public BitmapSource
        {
        public:
            typedef BitmapSource Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapFlipRotator, BitmapSource, IWICBitmapFlipRotator, IWICBitmapSource )

            HW_EXPORT BitmapFlipRotator& Initialize( const BitmapSource& theSource, BitmapTransformOptions options );

        };

        /// <summary>
        /// Exposes methods that support the Lock method.
        /// </summary>
        class BitmapLock : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapLock, ImagingObject, IWICBitmapLock, IUnknown )

            HW_EXPORT const BitmapLock& GetSize( UINT* puiWidth, UINT* puiHeight ) const;
            HW_EXPORT Size GetSize( ) const;

            HW_EXPORT const BitmapLock& GetStride( UINT* pcbStride ) const;
            HW_EXPORT UINT GetStride( ) const;

            HW_EXPORT const BitmapLock& GetDataPointer( UINT* pcbBufferSize, BYTE** ppbData ) const;

            HW_EXPORT const BitmapLock& GetPixelFormat( GUID* pPixelFormat ) const;
            HW_EXPORT GUID GetPixelFormat( ) const;

        };

        /// <summary>
        /// Defines methods that add the concept of writeability and static 
        /// in-memory representations of bitmaps to BitmapSource.
        /// </summary>
        class Bitmap : public BitmapSource
        {
        public:
            typedef BitmapSource Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( Bitmap, BitmapSource, IWICBitmap, IWICBitmapSource )

            HW_EXPORT BitmapLock Lock( const Rectangle& lockRectangle, DWORD flags );
            HW_EXPORT Bitmap& SetPalette( const Palette& thePalette );
            HW_EXPORT Bitmap& SetResolution( double dpiX, double dpiY );
            HW_EXPORT Bitmap& SetResolution( const Resolution& resolution );

        };

        /// <summary>
        /// Exposes methods for color management.
        /// </summary>
        class ColorContext : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( ColorContext, ImagingObject, IWICColorContext, IUnknown )

            HW_EXPORT ColorContext& InitializeFromFilename( LPCWSTR theFilename );
            HW_EXPORT ColorContext& InitializeFromFilename( const WideString& theFilename );

            HW_EXPORT ColorContext& InitializeFromMemory( const BYTE* theBuffer, UINT theBufferSize );

            HW_EXPORT ColorContext& InitializeFromExifColorSpace( UINT value );

            HW_EXPORT ColorContextType GetType( ) const;

            HW_EXPORT const ColorContext& GetProfileBytes( UINT bufferSize, BYTE* pbBuffer, UINT* actualNumberOfBytesCopied ) const;

            HW_EXPORT UINT GetExifColorSpace( ) const;

        };

        /// <summary>
        /// Exposes methods that transforms a BitmapSource from one color context to another.
        /// </summary>
        class ColorTransform : public BitmapSource
        {
        public:
            typedef BitmapSource Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( ColorTransform, BitmapSource, IWICColorTransform, IWICBitmapSource )

            HW_EXPORT ColorTransform& Initialize( const BitmapSource& theBitmapSource, const ColorContext& theContextSource, const ColorContext& theContextDest, REFGUID pixelFmtDest );

        };


        class MetadataQueryWriter;
        /// <summary>
        /// Exposes methods used for in-place metadata editing. A fast 
        /// metadata encoder enables you to add and remove metadata to 
        /// an image without having to fully re-encode the image.
        /// </summary>
        class FastMetadataEncoder : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( FastMetadataEncoder, ImagingObject, IWICFastMetadataEncoder, IUnknown )

            HW_EXPORT FastMetadataEncoder& Commit( );
            HW_EXPORT MetadataQueryWriter GetMetadataQueryWriter( );

        };

        /// <summary>
        /// Represents a Windows Imaging Component (WIC) stream for 
        /// referencing imaging and metadata content.
        /// </summary>
        class Stream : public ImagingObject /*IStream*/
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( Stream, ImagingObject, IWICStream, IUnknown )

            HW_EXPORT Stream& InitializeFromIStream( IStream* theStream );
            HW_EXPORT Stream& InitializeFromFilename( LPCWSTR theFileName, DWORD theDesiredAccess );
            HW_EXPORT Stream& InitializeFromMemory( BYTE* theBuffer, DWORD theBufferSize );
            HW_EXPORT Stream& InitializeFromIStreamRegion( IStream* theStream, unsigned long long theOffset, unsigned long long theMaxSize );

        };

        /// <summary>
        /// Exposes methods that provide enumeration services for individual metadata items.
        /// </summary>
        class EnumMetadataItem : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( EnumMetadataItem, ImagingObject, IWICEnumMetadataItem, IUnknown )

            HW_EXPORT bool Next( ULONG celt,
                    PROPVARIANT* rgeltSchema,
                    PROPVARIANT* rgeltId,
                    PROPVARIANT* rgeltValue,
                    ULONG* pceltFetched );

            HW_EXPORT EnumMetadataItem& Skip( ULONG celt );
            HW_EXPORT EnumMetadataItem& Reset( );
            HW_EXPORT EnumMetadataItem Clone( ) const;
        };

        /// <summary>
        /// Exposes methods for retrieving metadata blocks and items from a decoder or its image frames using a metadata query expression.
        /// </summary>
        class MetadataQueryReader : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( MetadataQueryReader, ImagingObject, IWICMetadataQueryReader, IUnknown )

            HW_EXPORT const MetadataQueryReader& GetContainerFormat( GUID* pguidContainerFormat ) const;
            HW_EXPORT GUID GetContainerFormat( ) const;

            HW_EXPORT const MetadataQueryReader& GetLocation( UINT cchMaxLength, WCHAR* wzNamespace, UINT* pcchActualLength ) const;
            HW_EXPORT WideString GetLocation( ) const;

            HW_EXPORT const MetadataQueryReader& GetMetadataByName( LPCWSTR wzName, PROPVARIANT* pvarValue ) const;
            HW_EXPORT const MetadataQueryReader& GetMetadataByName( const WideString& theName, PROPVARIANT* pvarValue ) const;


            HW_EXPORT EnumString GetEnumerator( ) const;

        };

        /// <summary>
        /// Exposes methods for setting or removing metadata blocks 
        /// and items to an encoder or its image frames using a 
        /// metadata query expression.
        /// </summary>
        class MetadataQueryWriter : public MetadataQueryReader
        {
        public:
            typedef MetadataQueryReader Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( MetadataQueryWriter, MetadataQueryReader, IWICMetadataQueryWriter, IWICMetadataQueryReader )

            HW_EXPORT MetadataQueryWriter& SetMetadataByName( LPCWSTR wzName, const PROPVARIANT* pvarValue );
            HW_EXPORT MetadataQueryWriter& RemoveMetadataByName( LPCWSTR wzName );
        };


        class BitmapFrameEncode;
        class BitmapEncoderInfo;
        /// <summary>
        /// Defines methods for setting an encoder's properties such as thumbnails, frames, and palettes.
        /// </summary>
        class BitmapEncoder : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapEncoder, ImagingObject, IWICBitmapEncoder, IUnknown )

            HW_EXPORT BitmapEncoder& Initialize( IStream* theStream, BitmapEncoderCacheOption cacheOption );

            HW_EXPORT const BitmapEncoder& GetContainerFormat( GUID* pguidContainerFormat ) const;
            HW_EXPORT GUID GetContainerFormat( ) const;

            HW_EXPORT BitmapEncoderInfo GetEncoderInfo( ) const;

            HW_EXPORT BitmapEncoder& SetColorContexts( std::shared_ptr< std::vector<ColorContext> > colorContexts );

            HW_EXPORT BitmapEncoder& SetPalette( const Palette& thePalette );

            HW_EXPORT BitmapEncoder& SetThumbnail( const BitmapSource& theThumbnail );

            HW_EXPORT BitmapEncoder& SetPreview( const BitmapSource& thePreview );

            HW_EXPORT BitmapFrameEncode CreateNewFrame( IPropertyBag2** ppIEncoderOptions );
            HW_EXPORT BitmapFrameEncode CreateNewFrame( PropertyBag2& encoderOptions );
            HW_EXPORT BitmapFrameEncode CreateNewFrame( );

            HW_EXPORT BitmapEncoder& Commit( );

            HW_EXPORT MetadataQueryWriter GetMetadataQueryWriter( ) const;

        };

        /// <summary>
        /// Represents an encoder's individual image frames.
        /// </summary>
        class BitmapFrameEncode : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapFrameEncode, ImagingObject, IWICBitmapFrameEncode, IUnknown )

            HW_EXPORT BitmapFrameEncode& Initialize( );
            HW_EXPORT BitmapFrameEncode& Initialize( IPropertyBag2* pIEncoderOptions );

            HW_EXPORT BitmapFrameEncode& SetSize( UINT uiWidth, UINT uiHeight );
            HW_EXPORT BitmapFrameEncode& SetSize( const Size& size );

            HW_EXPORT BitmapFrameEncode& SetResolution( double dpiX, double dpiY );
            HW_EXPORT BitmapFrameEncode& SetResolution( const Resolution& resolution );

            HW_EXPORT BitmapFrameEncode& SetPixelFormat( GUID* pPixelFormat );
            HW_EXPORT BitmapFrameEncode& SetPixelFormat( const GUID& thePixelFormat );

            HW_EXPORT BitmapFrameEncode& SetColorContexts( std::shared_ptr< std::vector<ColorContext> > colorContexts );

            HW_EXPORT BitmapFrameEncode& SetPalette( const Palette& thePalette );

            HW_EXPORT BitmapFrameEncode& SetThumbnail( const BitmapSource& theThumbnail );

            HW_EXPORT BitmapFrameEncode& WritePixels( UINT lineCount, UINT cbStride, UINT cbBufferSize, BYTE* pbPixels );

            HW_EXPORT BitmapFrameEncode& WriteSource( const BitmapSource& theBitmapSource, const Rectangle& rectangle );
            HW_EXPORT BitmapFrameEncode& WriteSource( const BitmapSource& theBitmapSource );

            HW_EXPORT BitmapFrameEncode& Commit( );

            HW_EXPORT MetadataQueryWriter GetMetadataQueryWriter( ) const;

        };

        /// <summary>
        /// Encodes ID2D1Image interfaces to an BitmapEncoder. The input 
        /// images can be larger than the maximum device texture size.
        /// </summary>
        class ImageEncoder : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( ImageEncoder, ImagingObject, IWICImageEncoder, IUnknown )

            HW_EXPORT ImageEncoder& WriteFrame( ID2D1Image* pImage, const BitmapFrameEncode& theFrameEncoder, const ImageParameters& theImageParameters );
            HW_EXPORT ImageEncoder& WriteFrameThumbnail( ID2D1Image* pImage, const BitmapFrameEncode& theFrameEncoder, const ImageParameters& theImageParameters );
            HW_EXPORT ImageEncoder& WriteThumbnail( ID2D1Image* pImage, const BitmapEncoder& theEncoder, const ImageParameters& theImageParameters );
        };



        class BitmapDecoderInfo;
        class BitmapFrameDecode;
        /// <summary>
        /// Exposes methods that represent a decoder. The class 
        /// provides access to the decoder's properties such as 
        /// global thumbnails (if supported), frames, and palette.
        /// </summary>
        class BitmapDecoder : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapDecoder, ImagingObject, IWICBitmapDecoder, IUnknown )

            HW_EXPORT DWORD QueryCapability( IStream* theStream ) const;

            HW_EXPORT BitmapDecoder& Initialize( IStream* theStream, DecodeOptions cacheOptions );

            HW_EXPORT const BitmapDecoder& GetContainerFormat( GUID* pguidContainerFormat ) const;
            HW_EXPORT GUID GetContainerFormat( ) const;

            HW_EXPORT BitmapDecoderInfo GetDecoderInfo( ) const;

            HW_EXPORT const BitmapDecoder& CopyPalette( Palette& theTargetPalette ) const;
            HW_EXPORT Palette CopyPalette( ) const;

            HW_EXPORT MetadataQueryReader GetMetadataQueryReader( ) const;

            HW_EXPORT BitmapSource GetPreview( ) const;

            HW_EXPORT std::shared_ptr< std::vector<ColorContext> >  GetColorContexts( ) const;

            HW_EXPORT BitmapSource GetThumbnail( ) const;

            HW_EXPORT UINT GetFrameCount( ) const;

            HW_EXPORT BitmapFrameDecode GetFrame( UINT index ) const;

        };

        /// <summary>
        /// Exposes methods for offloading certain operations to the underlying BitmapSource implementation.
        /// </summary>
        class BitmapSourceTransform : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapSourceTransform, ImagingObject, IWICBitmapSourceTransform, IUnknown )

            HW_EXPORT const BitmapSourceTransform& CopyPixels( const Rectangle& rectangle, UINT uiWidth, UINT uiHeight, WICPixelFormatGUID* pguidDstFormat, BitmapTransformOptions dstTransform, UINT nStride, UINT cbBufferSize, BYTE* pbBuffer ) const;

            HW_EXPORT const BitmapSourceTransform& GetClosestSize( UINT* puiWidth, UINT* puiHeight ) const;

            HW_EXPORT const BitmapSourceTransform& GetClosestPixelFormat( WICPixelFormatGUID* pguidDstFormat ) const;

            HW_EXPORT bool DoesSupportTransform( BitmapTransformOptions dstTransform ) const;

        };

        /// <summary>
        /// Defines methods for decoding individual image frames of an encoded file.
        /// </summary>
        class BitmapFrameDecode : public BitmapSource
        {
        public:
            typedef BitmapSource Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapFrameDecode, BitmapSource, IWICBitmapFrameDecode, IWICBitmapSource )

            HW_EXPORT MetadataQueryReader GetMetadataQueryReader( ) const;

            HW_EXPORT std::shared_ptr< std::vector<ColorContext> > GetColorContexts( ) const;

            HW_EXPORT BitmapSource GetThumbnail( ) const;

        };

        /// <summary>
        /// Exposes methods for obtaining information about and controlling progressive decoding.
        /// </summary>
        class ProgressiveLevelControl : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( ProgressiveLevelControl, ImagingObject, IWICProgressiveLevelControl, IUnknown )

            HW_EXPORT UINT GetLevelCount( );
            HW_EXPORT UINT GetCurrentLevel( );
            HW_EXPORT ProgressiveLevelControl& SetCurrentLevel( UINT theLevel );

        };


        class ProgressCallback : public Com::ObjectBase<ProgressCallback,IWICProgressCallback>
        {
        public:
            typedef Com::ObjectBase<ProgressCallback, IWICProgressCallback> Base;
            HW_EXPORT virtual HRESULT STDMETHODCALLTYPE Notify( ULONG uFrameNum, WICProgressOperation operation, double dblProgress );
        };

        /// <summary>
        /// Exposes methods used for progress notification for encoders and decoders.
        /// </summary>
        class BitmapCodecProgressNotification : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapCodecProgressNotification, ImagingObject, IWICBitmapCodecProgressNotification, IUnknown )

            HW_EXPORT BitmapCodecProgressNotification& RegisterProgressNotification( PFNProgressNotification pfnProgressNotification, LPVOID pvData, DWORD dwProgressFlags );

        };

        /// <summary>
        /// Exposes methods that provide component information.
        /// </summary>
        class ComponentInfo : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( ComponentInfo, ImagingObject, IWICComponentInfo, IUnknown )

            HW_EXPORT ComponentType GetComponentType( ) const;

            HW_EXPORT const ComponentInfo& GetCLSID( CLSID* pclsid ) const;
            HW_EXPORT CLSID GetCLSID( ) const;

            HW_EXPORT DWORD GetSigningStatus( ) const;

            HW_EXPORT WideString GetAuthor( ) const;

            HW_EXPORT const ComponentInfo& GetVendorGUID( GUID* pguidVendor ) const;
            HW_EXPORT GUID GetVendorGUID( ) const;

            HW_EXPORT WideString GetVersion( ) const;

            HW_EXPORT WideString GetSpecVersion( ) const;

            HW_EXPORT WideString GetFriendlyName( ) const;

        };

        class FormatConverter;
        /// <summary>
        /// Exposes methods that provide information about a pixel format converter.
        /// </summary>
        class FormatConverterInfo : public ComponentInfo
        {
        public:
            typedef ComponentInfo Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( FormatConverterInfo, ComponentInfo, IWICFormatConverterInfo, IWICComponentInfo )

            HW_EXPORT std::shared_ptr< std::vector<WICPixelFormatGUID> > GetPixelFormats( ) const;
            HW_EXPORT FormatConverter CreateInstance( ) const;

        };


        /// <summary>
        /// Exposes methods that provide information about a particular codec.
        /// </summary>
        class BitmapCodecInfo : public ComponentInfo
        {
        public:
            typedef ComponentInfo Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapCodecInfo, ComponentInfo, IWICBitmapCodecInfo, IWICComponentInfo )

            HW_EXPORT const BitmapCodecInfo& GetContainerFormat( GUID* pguidContainerFormat ) const;
            HW_EXPORT GUID GetContainerFormat( ) const;

            HW_EXPORT std::shared_ptr< std::vector<WICPixelFormatGUID> > GetPixelFormats( ) const;

            HW_EXPORT WideString GetColorManagementVersion( ) const;

            HW_EXPORT WideString GetDeviceManufacturer( ) const;

            HW_EXPORT WideString GetDeviceModels( ) const;

            HW_EXPORT WideString GetMimeTypes( ) const;

            HW_EXPORT WideString GetFileExtensions( ) const;

            HW_EXPORT bool DoesSupportAnimation( ) const;

            HW_EXPORT bool DoesSupportChromakey( ) const;

            HW_EXPORT bool DoesSupportLossless( ) const;

            HW_EXPORT bool DoesSupportMultiframe( ) const;

            HW_EXPORT bool MatchesMimeType( LPCWSTR wzMimeType ) const;
            HW_EXPORT bool MatchesMimeType( const WideString& theMimeType ) const;

        };

        /// <summary>
        /// Exposes methods that provide information about an encoder.
        /// </summary>
        class BitmapEncoderInfo : public BitmapCodecInfo
        {
        public:
            typedef BitmapCodecInfo Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapEncoderInfo, BitmapCodecInfo, IWICBitmapEncoderInfo, IWICBitmapCodecInfo )

            HW_EXPORT BitmapEncoder CreateInstance( );

        };


        /// <summary>
        /// Exposes methods that provide information about a decoder.
        /// </summary>
        class BitmapDecoderInfo : public BitmapCodecInfo
        {
        public:
            typedef BitmapCodecInfo Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( BitmapDecoderInfo, BitmapCodecInfo, IWICBitmapDecoderInfo, IWICBitmapCodecInfo )

            HW_EXPORT std::shared_ptr< std::vector<BitmapPattern> > GetPatterns( ) const;

            HW_EXPORT bool MatchesPattern( IStream* theStream ) const;

            HW_EXPORT BitmapDecoder CreateInstance( ) const;

        };

        /// <summary>
        /// Exposes methods that provide information about a pixel format.
        /// </summary>
        class PixelFormatInfo : public ComponentInfo
        {
        public:
            typedef ComponentInfo Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( PixelFormatInfo, ComponentInfo, IWICPixelFormatInfo, IWICComponentInfo )

            HW_EXPORT const PixelFormatInfo& GetFormatGUID( GUID* pFormat ) const;

            HW_EXPORT ColorContext GetColorContext( ) const;

            HW_EXPORT UINT GetBitsPerPixel( ) const;

            HW_EXPORT UINT GetChannelCount( ) const;

            HW_EXPORT std::shared_ptr< std::vector<BYTE> > GetChannelMask( UINT uiChannelIndex ) const;

            // IWICPixelFormatInfo2
            //HW_EXPORT bool SupportsTransparency( ) const;

            //HW_EXPORT PixelFormatNumericRepresentation GetNumericRepresentation( ) const;

        };

        /// <summary>
        /// Exposes methods used to create components for the Windows Imaging Component (WIC) 
        /// such as decoders, encoders and pixel format converters.
        /// </summary>
        class ImagingFactory : public ImagingObject
        {
        public:
            typedef ImagingObject Base;
            HW_IMAGING_STANDARD_METHODS_IMPL( ImagingFactory, ImagingObject, IWICImagingFactory, IUnknown )

            HW_EXPORT static ImagingFactory Create( );

            HW_EXPORT BitmapDecoder CreateDecoderFromFilename( LPCWSTR theFilename, const GUID* pguidVendor, DWORD dwDesiredAccess, DecodeOptions metadataOptions ) const;
            HW_EXPORT BitmapDecoder CreateDecoderFromFilename( LPCWSTR theFilename, DWORD dwDesiredAccess, DecodeOptions metadataOptions ) const;
            HW_EXPORT BitmapDecoder CreateDecoderFromFilename( LPCWSTR theFilename ) const;

            HW_EXPORT BitmapDecoder CreateDecoderFromFilename( const WideString& theFilename, const GUID* pguidVendor, DWORD dwDesiredAccess, DecodeOptions metadataOptions ) const;
            HW_EXPORT BitmapDecoder CreateDecoderFromFilename( const WideString& theFilename, DWORD dwDesiredAccess, DecodeOptions metadataOptions ) const;
            HW_EXPORT BitmapDecoder CreateDecoderFromFilename( const WideString& theFilename ) const;


            HW_EXPORT BitmapDecoder CreateDecoderFromStream( IStream* theStream, const GUID* pguidVendor, DecodeOptions metadataOptions ) const;
            HW_EXPORT BitmapDecoder CreateDecoderFromStream( IStream* theStream, DecodeOptions metadataOptions ) const;

            HW_EXPORT BitmapDecoder CreateDecoderFromFileHandle( ULONG_PTR hFile, const GUID* pguidVendor, DecodeOptions metadataOptions ) const;

            HW_EXPORT ComponentInfo CreateComponentInfo( REFCLSID clsidComponent ) const;

            HW_EXPORT BitmapDecoder CreateDecoder( REFGUID guidContainerFormat, const GUID* pguidVendor ) const;

            HW_EXPORT BitmapEncoder CreateEncoder( REFGUID guidContainerFormat, const GUID* pguidVendor ) const;

            HW_EXPORT BitmapEncoder CreateBMPEncoder( ) const;
            HW_EXPORT BitmapEncoder CreatePNGEncoder( ) const;
            HW_EXPORT BitmapEncoder CreateICOEncoder( ) const;
            HW_EXPORT BitmapEncoder CreateJPEGEncoder( ) const;
            HW_EXPORT BitmapEncoder CreateTIFFEncoder( ) const;
            HW_EXPORT BitmapEncoder CreateGIFEncoder( ) const;
            HW_EXPORT BitmapEncoder CreateWMPEncoder( ) const;


            HW_EXPORT Palette CreatePalette( ) const;

            HW_EXPORT FormatConverter CreateFormatConverter( ) const;

            HW_EXPORT BitmapScaler CreateBitmapScaler( ) const;

            HW_EXPORT BitmapClipper CreateBitmapClipper( ) const;

            HW_EXPORT BitmapFlipRotator CreateBitmapFlipRotator( ) const;

            HW_EXPORT Stream CreateStream( ) const;

            HW_EXPORT ColorContext CreateColorContext( ) const;

            HW_EXPORT ColorTransform CreateColorTransformer( ) const;

            HW_EXPORT Bitmap CreateBitmap( UINT uiWidth, UINT uiHeight, REFWICPixelFormatGUID pixelFormat, BitmapCreateCacheOption option ) const;

            HW_EXPORT Bitmap CreateBitmapFromSource( const BitmapSource& theBitmapSource, BitmapCreateCacheOption option ) const;

            HW_EXPORT Bitmap CreateBitmapFromSourceRect( const BitmapSource& theBitmapSource, UINT x, UINT y, UINT width, UINT height ) const;

            HW_EXPORT Bitmap CreateBitmapFromMemory( UINT uiWidth, UINT uiHeight, REFWICPixelFormatGUID pixelFormat, UINT cbStride, UINT cbBufferSize, BYTE* pbBuffer ) const;

            HW_EXPORT Bitmap CreateBitmapFromHBITMAP( HBITMAP hBitmap, HPALETTE hPalette, BitmapAlphaChannelOption options ) const;

            HW_EXPORT Bitmap CreateBitmapFromHICON( HICON hIcon ) const;

            HW_EXPORT const ImagingFactory& CreateComponentEnumerator( DWORD componentTypes, DWORD options, IEnumUnknown** ppIEnumUnknown ) const;

            HW_EXPORT FastMetadataEncoder CreateFastMetadataEncoderFromDecoder( const BitmapDecoder& theDecoder ) const;

            HW_EXPORT FastMetadataEncoder CreateFastMetadataEncoderFromFrameDecode( const BitmapFrameDecode& theFrameDecoder ) const;

            HW_EXPORT MetadataQueryWriter CreateQueryWriter( REFGUID guidMetadataFormat, const GUID* pguidVendor ) const;

            HW_EXPORT MetadataQueryWriter CreateQueryWriterFromReader( const MetadataQueryReader& theQueryReader, const GUID* pguidVendor ) const;

        };






    };
}

#endif
