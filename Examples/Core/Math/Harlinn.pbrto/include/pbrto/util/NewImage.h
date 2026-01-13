#pragma once
#ifndef PBRTO_UTIL_NEWIMAGE_H_
#define PBRTO_UTIL_NEWIMAGE_H_

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0



#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewLog.h>
#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewContainers.h>
#include <pbrto/util/NewFloat.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewParallel.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewVecMath.h>

#include <cstdint>
#include <cstring>
#include <map>
#include <memory>
#include <vector>

namespace pbrto
{

    // PixelFormat Definition
    enum class PixelFormat { U256, Half, Float };

    // PixelFormat Inline Functions
    inline bool Is8Bit( PixelFormat format )
    {
        return format == PixelFormat::U256;
    }
    inline bool Is16Bit( PixelFormat format )
    {
        return format == PixelFormat::Half;
    }
    inline bool Is32Bit( PixelFormat format )
    {
        return format == PixelFormat::Float;
    }

    PBRTO_EXPORT std::string ToString( PixelFormat format );

    int TexelBytes( PixelFormat format );

    // ResampleWeight Definition
    struct ResampleWeight
    {
        int firstPixel;
        Float weight[ 4 ];
    };

    // WrapMode Definitions
    enum class WrapMode { Black, Clamp, Repeat, OctahedralSphere };
    struct WrapMode2D
    {
        pstdo::array<WrapMode, 2> wrap;

        WrapMode2D( WrapMode w ) 
            : wrap{ w, w } 
        { }
        WrapMode2D( WrapMode x, WrapMode y ) 
            : wrap{ x, y } 
        { }

        
    };

    inline pstdo::optional<WrapMode> ParseWrapMode( const char* w )
    {
        if ( !strcmp( w, "clamp" ) )
            return WrapMode::Clamp;
        else if ( !strcmp( w, "repeat" ) )
            return WrapMode::Repeat;
        else if ( !strcmp( w, "black" ) )
            return WrapMode::Black;
        else if ( !strcmp( w, "octahedralsphere" ) )
            return WrapMode::OctahedralSphere;
        else
            return {};
    }

    inline std::string ToString( WrapMode mode )
    {
        switch ( mode )
        {
            case WrapMode::Clamp:
                return "clamp";
            case WrapMode::Repeat:
                return "repeat";
            case WrapMode::Black:
                return "black";
            case WrapMode::OctahedralSphere:
                return "octahedralsphere";
            default:
                NLOG_FATAL( "Unhandled wrap mode" );
                return {};
        }
    }

    // Image Wrapping Inline Functions
    inline bool RemapPixelCoords( Point2i* pp, Point2i resolution, WrapMode2D wrapMode );

    inline bool RemapPixelCoords( Point2i* pp, Point2i resolution, WrapMode2D wrapMode )
    {
        Point2i& p = *pp;

        if ( wrapMode.wrap[ 0 ] == WrapMode::OctahedralSphere )
        {
            NCHECK( wrapMode.wrap[ 1 ] == WrapMode::OctahedralSphere );
            if ( p[ 0 ] < 0 )
            {
                p[ 0 ] = -p[ 0 ];                     // mirror across u = 0
                p[ 1 ] = resolution[ 1 ] - 1 - p[ 1 ];  // mirror across v = 0.5
            }
            else if ( p[ 0 ] >= resolution[ 0 ] )
            {
                p[ 0 ] = 2 * resolution[ 0 ] - 1 - p[ 0 ];  // mirror across u = 1
                p[ 1 ] = resolution[ 1 ] - 1 - p[ 1 ];      // mirror across v = 0.5
            }

            if ( p[ 1 ] < 0 )
            {
                p[ 0 ] = resolution[ 0 ] - 1 - p[ 0 ];  // mirror across u = 0.5
                p[ 1 ] = -p[ 1 ];                     // mirror across v = 0;
            }
            else if ( p[ 1 ] >= resolution[ 1 ] )
            {
                p[ 0 ] = resolution[ 0 ] - 1 - p[ 0 ];      // mirror across u = 0.5
                p[ 1 ] = 2 * resolution[ 1 ] - 1 - p[ 1 ];  // mirror across v = 1
            }

            // Bleh: things don't go as expected for 1x1 images.
            if ( resolution[ 0 ] == 1 )
                p[ 0 ] = 0;
            if ( resolution[ 1 ] == 1 )
                p[ 1 ] = 0;

            return true;
        }

        for ( int c = 0; c < 2; ++c )
        {
            if ( p[ c ] >= 0 && p[ c ] < resolution[ c ] )
                // in bounds
                continue;

            switch ( wrapMode.wrap[ c ] )
            {
                case WrapMode::Repeat:
                    p[ c ] = Mod( p[ c ], resolution[ c ] );
                    break;
                case WrapMode::Clamp:
                    p[ c ] = Clamp( p[ c ], 0, resolution[ c ] - 1 );
                    break;
                case WrapMode::Black:
                    return false;
                default:
                    NLOG_FATAL( "Unhandled WrapMode mode" );
            }
        }
        return true;
    }

    // ImageMetadata Definition
    struct ImageMetadata
    {
        // ImageMetadata Public Methods
        PBRTO_EXPORT const RGBColorSpace* GetColorSpace( ) const;
        PBRTO_EXPORT std::string ToString( ) const;

        // ImageMetadata Public Members
        pstdo::optional<float> renderTimeSeconds;
        pstdo::optional<SquareMatrix<4>> cameraFromWorld, NDCFromWorld;
        pstdo::optional<Bounds2i> pixelBounds;
        pstdo::optional<Point2i> fullResolution;
        pstdo::optional<int> samplesPerPixel;
        pstdo::optional<float> MSE;
        pstdo::optional<const RGBColorSpace*> colorSpace;
        std::map<std::string, std::string> strings;
        std::map<std::string, std::vector<std::string>> stringVectors;
    };

    struct ImageAndMetadata;

    // ImageChannelDesc Definition
    struct ImageChannelDesc
    {
        InlinedVector<int, 4> offset;

        operator bool( ) const { return size( ) > 0; }

        size_t size( ) const { return offset.size( ); }
        bool IsIdentity( ) const
        {
            for ( size_t i = 0; i < offset.size( ); ++i )
                if ( offset[ i ] != i )
                    return false;
            return true;
        }
        std::string ToString( ) const;

        
    };

    // ImageChannelValues Definition
    struct ImageChannelValues : public InlinedVector<Float, 4>
    {
        // ImageChannelValues() = default;
        explicit ImageChannelValues( size_t sz, Float v = {} )
            : InlinedVector<Float, 4>( sz, v ) {}

        operator Float( ) const
        {
            NCHECK_EQ( 1, size( ) );
            return ( *this )[ 0 ];
        }
        operator pstdo::array<Float, 3>( ) const
        {
            NCHECK_EQ( 3, size( ) );
            return { ( *this )[ 0 ], ( *this )[ 1 ], ( *this )[ 2 ] };
        }

        Float MaxValue( ) const
        {
            Float m = ( *this )[ 0 ];
            for ( int i = 1; i < size( ); ++i )
                m = std::max( m, ( *this )[ i ] );
            return m;
        }
        Float Average( ) const
        {
            Float sum = 0;
            for ( int i = 0; i < size( ); ++i )
                sum += ( *this )[ i ];
            return sum / size( );
        }

        std::string ToString( ) const;
    };

    // Image Definition
    class Image
    {
    public:
        // Image Public Methods
        PBRTO_EXPORT Image( Allocator alloc = {} )
            : p8( alloc ),
            p16( alloc ),
            p32( alloc ),
            format( PixelFormat::U256 ),
            resolution( 0, 0 )
        {
        }
        PBRTO_EXPORT Image( pstdo::vector<uint8_t> p8, Point2i resolution,
            pstdo::span<const std::string> channels, ColorEncoding encoding );
        PBRTO_EXPORT Image( pstdo::vector<Half> p16, Point2i resolution,
            pstdo::span<const std::string> channels );
        PBRTO_EXPORT Image( pstdo::vector<float> p32, Point2i resolution,
            pstdo::span<const std::string> channels );

        PBRTO_EXPORT Image( PixelFormat format, Point2i resolution,
            pstdo::span<const std::string> channelNames, ColorEncoding encoding = nullptr,
            Allocator alloc = {} );

        PixelFormat Format( ) const { return format; }
        Point2i Resolution( ) const { return resolution; }
        int NChannels( ) const { return channelNames.size( ); }
        
        PBRTO_EXPORT std::vector<std::string> ChannelNames( ) const;
        const ColorEncoding Encoding( ) const { return encoding; }

        operator bool( ) const { return resolution.x > 0 && resolution.y > 0; }

        size_t PixelOffset( Point2i p ) const
        {
            NDCHECK( InsideExclusive( p, Bounds2i( { 0, 0 }, resolution ) ) );
            return NChannels( ) * ( p.y * resolution.x + p.x );
        }

        Float GetChannel( Point2i p, int c, WrapMode2D wrapMode = WrapMode::Clamp ) const
        {
            // Remap provided pixel coordinates before reading channel
            if ( !RemapPixelCoords( &p, resolution, wrapMode ) )
                return 0;

            switch ( format )
            {
                case PixelFormat::U256:
                {  // Return _U256_-encoded pixel channel value
                    Float r;
                    encoding.ToLinear( { &p8[ PixelOffset( p ) + c ], 1 }, { &r, 1 } );
                    return r;
                }
                case PixelFormat::Half:
                {  // Return _Half_-encoded pixel channel value
                    return Float( p16[ PixelOffset( p ) + c ] );
                }
                case PixelFormat::Float:
                {  // Return _Float_-encoded pixel channel value
                    return p32[ PixelOffset( p ) + c ];
                }
                default:
                    NLOG_FATAL( "Unhandled PixelFormat" );
                    return 0;
            }
        }

        PBRT_CPU_GPU
            Float BilerpChannel( Point2f p, int c, WrapMode2D wrapMode = WrapMode::Clamp ) const
        {
            // Compute discrete pixel coordinates and offsets for _p_
            Float x = p[ 0 ] * resolution.x - 0.5f, y = p[ 1 ] * resolution.y - 0.5f;
            int xi = pstdo::floor( x ), yi = pstdo::floor( y );
            Float dx = x - xi, dy = y - yi;

            // Load pixel channel values and return bilinearly interpolated value
            pstdo::array<Float, 4> v = { GetChannel( {xi, yi}, c, wrapMode ),
                                       GetChannel( {xi + 1, yi}, c, wrapMode ),
                                       GetChannel( {xi, yi + 1}, c, wrapMode ),
                                       GetChannel( {xi + 1, yi + 1}, c, wrapMode ) };
            return ( ( 1 - dx ) * ( 1 - dy ) * v[ 0 ] + dx * ( 1 - dy ) * v[ 1 ] + ( 1 - dx ) * dy * v[ 2 ] +
                dx * dy * v[ 3 ] );
        }

        void SetChannel( Point2i p, int c, Float value );

        PBRTO_EXPORT ImageChannelValues GetChannels( Point2i p, WrapMode2D wrapMode = WrapMode::Clamp ) const;

        PBRTO_EXPORT ImageChannelDesc GetChannelDesc( pstdo::span<const std::string> channels ) const;

        ImageChannelDesc AllChannelsDesc( ) const
        {
            ImageChannelDesc desc;
            desc.offset.resize( NChannels( ) );
            for ( int i = 0; i < NChannels( ); ++i )
                desc.offset[ i ] = i;
            return desc;
        }

        PBRTO_EXPORT ImageChannelValues GetChannels( Point2i p, const ImageChannelDesc& desc, WrapMode2D wrapMode = WrapMode::Clamp ) const;

        PBRTO_EXPORT Image SelectChannels( const ImageChannelDesc& desc, Allocator alloc = {} ) const;
        PBRTO_EXPORT Image Crop( const Bounds2i& bounds, Allocator alloc = {} ) const;

        PBRTO_EXPORT void CopyRectOut( const Bounds2i& extent, pstdo::span<float> buf, WrapMode2D wrapMode = WrapMode::Clamp ) const;
        PBRTO_EXPORT void CopyRectIn( const Bounds2i& extent, pstdo::span<const float> buf );

        PBRTO_EXPORT ImageChannelValues Average( const ImageChannelDesc& desc ) const;

        PBRTO_EXPORT bool HasAnyInfinitePixels( ) const;
        PBRTO_EXPORT bool HasAnyNaNPixels( ) const;

        PBRTO_EXPORT ImageChannelValues MAE( const ImageChannelDesc& desc, const Image& ref, Image* errorImage = nullptr ) const;
        PBRTO_EXPORT ImageChannelValues MSE( const ImageChannelDesc& desc, const Image& ref, Image* mseImage = nullptr ) const;
        PBRTO_EXPORT ImageChannelValues MRSE( const ImageChannelDesc& desc, const Image& ref, Image* mrseImage = nullptr ) const;

        PBRTO_EXPORT Image GaussianFilter( const ImageChannelDesc& desc, int halfWidth, Float sigma ) const;

        template <typename F>
        Array2D<Float> GetSamplingDistribution(
            F dxdA, const Bounds2f& domain = Bounds2f( Point2f( 0, 0 ), Point2f( 1, 1 ) ),
            Allocator alloc = {} );
        Array2D<Float> GetSamplingDistribution( )
        {
            return GetSamplingDistribution( []( Point2f ) { return Float( 1 ); } );
        }

        PBRTO_EXPORT static ImageAndMetadata Read( std::string filename, Allocator alloc = {}, ColorEncoding encoding = nullptr );

        PBRTO_EXPORT bool Write( std::string name, const ImageMetadata& metadata = {} ) const;

        PBRTO_EXPORT Image ConvertToFormat( PixelFormat format, ColorEncoding encoding = nullptr ) const;

        // TODO? provide an iterator to iterate over all pixels and channels?

        PBRT_CPU_GPU
            Float LookupNearestChannel( Point2f p, int c,
                WrapMode2D wrapMode = WrapMode::Clamp ) const
        {
            Point2i pi( p.x * resolution.x, p.y * resolution.y );
            return GetChannel( pi, c, wrapMode );
        }

        PBRTO_EXPORT ImageChannelValues LookupNearest( Point2f p, WrapMode2D wrapMode = WrapMode::Clamp ) const;
        PBRTO_EXPORT ImageChannelValues LookupNearest( Point2f p, const ImageChannelDesc& desc, WrapMode2D wrapMode = WrapMode::Clamp ) const;

        PBRTO_EXPORT ImageChannelValues Bilerp( Point2f p, WrapMode2D wrapMode = WrapMode::Clamp ) const;
        PBRTO_EXPORT ImageChannelValues Bilerp( Point2f p, const ImageChannelDesc& desc, WrapMode2D wrapMode = WrapMode::Clamp ) const;

        PBRTO_EXPORT void SetChannels( Point2i p, const ImageChannelValues& values );
        PBRTO_EXPORT void SetChannels( Point2i p, pstdo::span<const Float> values );
        PBRTO_EXPORT void SetChannels( Point2i p, const ImageChannelDesc& desc, pstdo::span<const Float> values );

        PBRTO_EXPORT Image FloatResizeUp( Point2i newResolution, WrapMode2D wrap ) const;
        PBRTO_EXPORT void FlipY( );
        PBRTO_EXPORT static pstdo::vector<Image> GeneratePyramid( Image image, WrapMode2D wrapMode, Allocator alloc = {} );

        PBRTO_EXPORT std::vector<std::string> ChannelNames( const ImageChannelDesc& ) const;

        PBRT_CPU_GPU
            size_t BytesUsed( ) const { return p8.size( ) + 2 * p16.size( ) + 4 * p32.size( ); }

        PBRT_CPU_GPU
            const void* RawPointer( Point2i p ) const
        {
            if ( Is8Bit( format ) )
                return p8.data( ) + PixelOffset( p );
            if ( Is16Bit( format ) )
                return p16.data( ) + PixelOffset( p );
            else
            {
                NCHECK( Is32Bit( format ) );
                return p32.data( ) + PixelOffset( p );
            }
        }
        PBRT_CPU_GPU
            void* RawPointer( Point2i p )
        {
            return const_cast< void* >( ( ( const Image* )this )->RawPointer( p ) );
        }

        PBRTO_EXPORT Image JointBilateralFilter( const ImageChannelDesc& toFilter, int halfWidth,
            const Float xySigma[ 2 ], const ImageChannelDesc& joint,
            const ImageChannelValues& jointSigma ) const;

        PBRTO_EXPORT std::string ToString( ) const;

    private:
        // Image Private Methods
        static std::vector<ResampleWeight> ResampleWeights( int oldRes, int newRes );
        bool WriteEXR( const std::string& name, const ImageMetadata& metadata ) const;
        bool WritePFM( const std::string& name, const ImageMetadata& metadata ) const;
        bool WritePNG( const std::string& name, const ImageMetadata& metadata ) const;
        bool WriteQOI( const std::string& name, const ImageMetadata& metadata ) const;

        std::unique_ptr<uint8_t[ ]> QuantizePixelsToU256( int* nOutOfGamut ) const;

        // Image Private Members
        PixelFormat format;
        Point2i resolution;
        pstdo::vector<std::string> channelNames;
        ColorEncoding encoding = nullptr;
        pstdo::vector<uint8_t> p8;
        pstdo::vector<Half> p16;
        pstdo::vector<float> p32;
    };

    // Image Inline Method Definitions
    inline void Image::SetChannel( Point2i p, int c, Float value )
    {
        // NCHECK(!IsNaN(value));
        if ( IsNaN( value ) )
        {
#ifndef PBRT_IS_GPU_CODE
            NLOG_ERROR( "NaN at pixel %d,%d comp %d", p.x, p.y, c );
#endif
            value = 0;
        }

        switch ( format )
        {
            case PixelFormat::U256:
                encoding.FromLinear( { &value, 1 }, { &p8[ PixelOffset( p ) + c ], 1 } );
                break;
            case PixelFormat::Half:
                p16[ PixelOffset( p ) + c ] = Half( value );
                break;
            case PixelFormat::Float:
                p32[ PixelOffset( p ) + c ] = value;
                break;
            default:
                NLOG_FATAL( "Unhandled PixelFormat in Image::SetChannel()" );
        }
    }

    template <typename F>
    inline Array2D<Float> Image::GetSamplingDistribution( F dxdA, const Bounds2f& domain,
        Allocator alloc )
    {
        Array2D<Float> dist( resolution[ 0 ], resolution[ 1 ], alloc );
        ParallelFor( 0, resolution[ 1 ], [ & ]( int64_t y0, int64_t y1 ) {
            for ( int y = y0; y < y1; ++y )
            {
                for ( int x = 0; x < resolution[ 0 ]; ++x )
                {
                    // This is noticeably better than MaxValue: discuss / show
                    // example..
                    Float value = GetChannels( { x, y } ).Average( );

                    // Assume Jacobian term is basically constant over the
                    // region.
                    Point2f p = domain.Lerp2(
                        Point2f( ( x + .5f ) / resolution[ 0 ], ( y + .5f ) / resolution[ 1 ] ) );
                    dist( x, y ) = value * dxdA( p );
                }
            }
            } );
        return dist;
    }

    // ImageAndMetadata Definition
    struct ImageAndMetadata
    {
        Image image;
        ImageMetadata metadata;
    };

}


#endif
