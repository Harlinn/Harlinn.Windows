#pragma once

#include <HWDef.h>
#include <HCCSIMD.h>

namespace Harlinn::Windows::Graphics
{

    class Color
    {
    public:
        using Traits = SIMD::Traits<float, 4>;
        using SIMDType = typename Traits::SIMDType;
        using value_type = float;
        static constexpr size_t Size = 4;
    private:
        using Constants = typename Traits::Constants;
    public:
        SIMDType simd;

        Color()
            : simd( Constants::IdentityR4 )
        { }

        Color( float red, float green, float blue, float alpha = 1.0f )
            : simd( Traits::Set(alpha,blue,green,red) )
        { }

        Color( SIMDType value )
            : simd( value )
        { }

        Color( UInt16 red, UInt16 green, UInt16 blue, UInt16 alpha = 255, UInt16 bitDepth = 8 )
            : simd( Traits::Mul( 1.0f / static_cast<value_type>( ( 1 << bitDepth ) - 1 ),Traits::Set( alpha, blue, green, red ) ) )
        { }

        explicit Color( UInt32 rgba )
            : simd( Traits::Mul( 1.0f / 255.f, 
                Traits::Set( static_cast< value_type >( ( rgba >> 24 ) & 0xFF ), 
                    static_cast< value_type >( ( rgba >> 16 ) & 0xFF ), 
                        static_cast< value_type >( ( rgba >> 8 ) & 0xFF ), 
                            static_cast< value_type >( rgba & 0xFF ) ) ) )
        { }

        float R( ) const { return Traits::Extract<0>( simd ); }
        float Red( ) const { return Traits::Extract<0>( simd ); }
        float G( ) const { return Traits::Extract<1>( simd ); }
        float Green( ) const { return Traits::Extract<1>( simd ); }
        float B( ) const { return Traits::Extract<2>( simd ); }
        float Blue( ) const { return Traits::Extract<2>( simd ); }
        float A( ) const { return Traits::Extract<3>( simd ); }
        float Alpha( ) const { return Traits::Extract<3>( simd ); }

        float operator[]( size_t index ) const
        {
            return reinterpret_cast<const float*>(&simd)[ index ];
        }

        const float* data( ) const
        {
            return reinterpret_cast< const float* >( &simd );
        }

        std::array<float, 4> ToRGBA( ) const
        {
            alignas( 16 ) std::array<float, 4> result;
            _mm_store_ps( result.data( ), simd );
            return result;
        }

        void Assign( const std::array<float, 4>& value )
        {
            simd = _mm_loadu_ps( value.data( ) );
        }

        void SetR( float red )
        {
            simd = Traits::SetX( simd, red );
        }
        void SetG( float green )
        {
            simd = Traits::SetY( simd, green );
        }
        void SetB( float blue )
        {
            simd = Traits::SetZ( simd, blue );
        }
        void SetA( float alpha )
        {
            simd = Traits::SetW( simd, alpha );
        }

        Color ToSRGB( void ) const
        {
            auto saturated = Traits::Saturate( simd );
            auto result = Traits::Sub( Traits::Mul( Traits::Pow( saturated, Traits::Fill( 1.0f / 2.4f ) ), 1.055f ), Traits::Fill( 0.055f ) );
            result = Traits::Select( result, Traits::Mul( saturated, 12.92f ), Traits::Less( saturated, Traits::Fill( 0.0031308f ) ) );
            return Traits::Select( saturated, result, Constants::Select2221 );
        }

        inline Color FromSRGB( void ) const
        {
            auto saturated = Traits::Saturate( simd );
            auto result = Traits::Pow( Traits::Mul( Traits::Add( saturated, Traits::Fill( 0.055f ) ), 1.0f / 1.055f ), Traits::Fill( 2.4f ) );
            result = Traits::Select( result, Traits::Mul( saturated, 1.0f / 12.92f ), Traits::Less( saturated, Traits::Fill( 0.0031308f ) ) );
            return Traits::Select( saturated, result, Constants::Select2221 );
        }

        inline Color ToREC709( void ) const
        {
            auto saturated = Traits::Saturate( simd );
            auto result = Traits::Sub( Traits::Mul( Traits::Pow( saturated, Traits::Fill( 0.45f ) ), 1.099f ), Traits::Fill( 0.099f ) );
            result = Traits::Select( result, Traits::Mul( saturated, 4.5f ), Traits::Less( saturated, Traits::Fill( 0.0018f ) ) );
            return Traits::Select( saturated, result, Constants::Select2221 );
        }

        inline Color FromREC709( void ) const
        {
            auto saturated = Traits::Saturate( simd );
            auto result = Traits::Pow( Traits::Mul( Traits::Add( saturated, Traits::Fill( 0.099f ) ), 1.0f / 1.099f ), Traits::Fill( 1.0f / 0.45f ) );
            result = Traits::Select( result, Traits::Mul( saturated, 1.0f / 4.5f ), Traits::Less( saturated, Traits::Fill( 0.0081f ) ) );
            return Traits::Select( saturated, result, Constants::Select2221 );
        }

        inline UInt32 R10G10B10A2( void ) const
        {
            auto result = Traits::Round( Traits::Mul( Traits::Saturate( simd ), Traits::Set( 3.0f, 1023.0f, 1023.0f, 1023.0f ) ) );
            result = _mm_castsi128_ps( _mm_cvttps_epi32( result ) );
            UInt32 r = static_cast< UInt32 >( _mm_cvtsi128_si32( _mm_castps_si128( result ) ) );
            UInt32 g = static_cast< UInt32 >( _mm_cvtsi128_si32( _mm_shuffle_epi32( _mm_castps_si128( result ), _MM_SHUFFLE( 1, 1, 1, 1 ) ) ) );
            UInt32 b = static_cast< UInt32 >( _mm_cvtsi128_si32( _mm_shuffle_epi32( _mm_castps_si128( result ), _MM_SHUFFLE( 2, 2, 2, 2 ) ) ) );
            UInt32 a = static_cast< UInt32 >( _mm_cvtsi128_si32( _mm_shuffle_epi32( _mm_castps_si128( result ), _MM_SHUFFLE( 3, 3, 3, 3 ) ) ) ) >> 8;
            return a << 30 | b << 20 | g << 10 | r;
        }

        inline UInt32 R8G8B8A8( void ) const
        {
            auto result = Traits::Round( Traits::Mul( Traits::Saturate( simd ), Traits::Fill( 255.0f ) ) );
            result = _mm_castsi128_ps( _mm_cvttps_epi32( result ) );
            UInt32 r = static_cast< UInt32 >( _mm_cvtsi128_si32( _mm_castps_si128( result ) ) );
            UInt32 g = static_cast< UInt32 >( _mm_cvtsi128_si32( _mm_shuffle_epi32( _mm_castps_si128( result ), _MM_SHUFFLE( 1, 1, 1, 1 ) ) ) );
            UInt32 b = static_cast< UInt32 >( _mm_cvtsi128_si32( _mm_shuffle_epi32( _mm_castps_si128( result ), _MM_SHUFFLE( 2, 2, 2, 2 ) ) ) );
            UInt32 a = static_cast< UInt32 >( _mm_cvtsi128_si32( _mm_shuffle_epi32( _mm_castps_si128( result ), _MM_SHUFFLE( 3, 3, 3, 3 ) ) ) );
            return a << 24 | b << 16 | g << 8 | r;
        }

        UInt32 R11G11B10F( bool roundToEven = false ) const
        {
            constexpr SIMDType scale = { { std::bit_cast< float >( 0x07800000 ), std::bit_cast< float >( 0x07800000 ), std::bit_cast< float >( 0x07800000 ), 0 } };
            constexpr SIMDType round1 = { { std::bit_cast< float >( 0x00010000 ), std::bit_cast< float >( 0x00010000 ), std::bit_cast< float >( 0x00020000 ), 0 } };
            constexpr SIMDType round2 = { { std::bit_cast< float >( 0x0000FFFF ), std::bit_cast< float >( 0x0000FFFF ), std::bit_cast< float >( 0x0001FFFF), 0 } };
            constexpr SIMDType mask =   { { std::bit_cast< float >( 0x0FFE0000), std::bit_cast< float >( 0x0FFE0000), std::bit_cast< float >( 0x0FFC0000 ), 0 } };

            __m128i ti = _mm_max_epi32( _mm_castps_si128( simd ), _mm_setzero_si128( ) );
            ti = _mm_min_epi32( ti, _mm_set1_epi32( 0x47800000 ) ); 

            ti = _mm_castps_si128( _mm_mul_ps( _mm_castsi128_ps( ti ), scale ) );

            if ( roundToEven )
            {
                ti = _mm_add_epi32( ti, _mm_max_epi32( _mm_and_si128( _mm_srli_epi32( ti, 1 ), _mm_castps_si128( round1 ) ), _mm_castps_si128( round2 ) ) );
            }
            else
            {
                ti = _mm_add_epi32( ti, _mm_castps_si128( round1 ) );
            }

            alignas(16) std::array<UInt32, 4> result;
            _mm_store_si128( reinterpret_cast< __m128i* >( result.data( ) ), _mm_and_si128( ti, _mm_castps_si128( mask ) ) );
            
            return result[ 0 ] >> 17 | result[ 1 ] >> 6 | result[ 2 ] << 4;
        }
        UInt32 R9G9B9E5( ) const
        {
            __m128 maxValue = _mm_castsi128_ps( _mm_set1_epi32( 0x477F8000 ) );
            __m128 rgb = _mm_min_ps( _mm_max_ps( simd, _mm_setzero_ps( ) ), maxValue );

            __m128 minValue = _mm_castsi128_ps( _mm_set1_epi32( 0x37800000 ) );
            __m128 maxChannel = _mm_max_ps( rgb, minValue );
            maxChannel = _mm_max_ps( _mm_permute_ps( maxChannel, _MM_SHUFFLE( 3, 1, 0, 2 ) ), _mm_max_ps( _mm_permute_ps( maxChannel, _MM_SHUFFLE( 3, 0, 2, 1 ) ), maxChannel ) );

            __m128i bias15 = _mm_set1_epi32( 0x07804000 );
            __m128i expMask = _mm_set1_epi32( 0x7F800000 );
            __m128i bias = _mm_and_si128( _mm_add_epi32( _mm_castps_si128( maxChannel ), bias15 ), expMask );

            rgb = _mm_add_ps( rgb, _mm_castsi128_ps( bias ) );

            __m128i Exp = _mm_add_epi32( _mm_slli_epi32( bias, 4 ), _mm_set1_epi32( 0x10000000 ) );

            alignas( 16 ) std::array<UInt32, 4> result;
            _mm_store_si128( reinterpret_cast< __m128i* >( result.data() ), _mm_castps_si128( _mm_insert_ps( rgb, _mm_castsi128_ps( Exp ), 0x30 ) ) );

            return result[ 3 ] | result[ 2 ] << 18 | result[ 1 ] << 9 | result[ 0 ] & 511;
        }
    };

    inline Color Max( Color a, Color b ) 
    { 
        using Traits = Color::Traits;
        return Color( Traits::Max( a.simd, b.simd ) );
    }
    inline Color Min( Color a, Color b ) 
    { 
        using Traits = Color::Traits;
        return Color( Traits::Min( a.simd, b.simd ) );
    }
    inline Color Clamp( Color x, Color a, Color b ) 
    { 
        using Traits = Color::Traits;
        return Color( Traits::Clamp( x.simd, a.simd, b.simd ) );
    }

}
