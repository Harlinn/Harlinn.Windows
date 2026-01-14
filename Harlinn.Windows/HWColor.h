#pragma once
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

#include <HWDef.h>
#include <HCCSIMD.h>

namespace Harlinn::Windows::Graphics
{
    /// <summary>
    /// Represents a 4-component color (red, green, blue, alpha) stored as a SIMD float4.
    /// </summary>
    /// <remarks>
    /// Uses <c>SIMD::Traits&lt;float,4&gt;</c> for efficient SIMD operations. Component ordering inside the SIMD value
    /// is red at index 0, green at index 1, blue at index 2 and alpha at index 3. Components are typically in the
    /// [0,1] range for normalized colors.
    /// </remarks>
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

        /// <summary>
        /// Initializes a new instance of the <see cref="Color"/> class with the SIMD identity value.
        /// { R = 0.0f, G = 0.0f, B = 0.0f, A = 1.0f }
        /// </summary>
        /// <remarks>
        /// The default value is <c>Constants::IdentityR4</c>. 
        /// </remarks>
        Color()
            : simd( Constants::IdentityR4 )
        { }

        /// <summary>
        /// Initializes a new <see cref="Color"/> from individual float components.
        /// </summary>
        /// <param name="red">Red component (0..1).</param>
        /// <param name="green">Green component (0..1).</param>
        /// <param name="blue">Blue component (0..1).</param>
        /// <param name="alpha">Alpha component (0..1). Defaults to 1.0f.</param>
        Color( float red, float green, float blue, float alpha = 1.0f )
            : simd( Traits::Set(alpha,blue,green,red) )
        { }

        /// <summary>
        /// Initializes a new <see cref="Color"/> from a raw SIMD value.
        /// </summary>
        /// <param name="value">SIMD float4 value representing RGBA.</param>
        Color( SIMDType value )
            : simd( value )
        { }
        
        /// <summary>
        /// Initializes a new <see cref="Color"/> from integer channel values and bit depth.
        /// </summary>
        /// <param name="red">Red channel integer value.</param>
        /// <param name="green">Green channel integer value.</param>
        /// <param name="blue">Blue channel integer value.</param>
        /// <param name="alpha">Alpha channel integer value. Defaults to 255.</param>
        /// <param name="bitDepth">Bit depth of the integer channels (e.g. 8). Defaults to 8.</param>
        Color( UInt16 red, UInt16 green, UInt16 blue, UInt16 alpha = 255, UInt16 bitDepth = 8 )
            : simd( Traits::Mul( 1.0f / static_cast<value_type>( ( 1 << bitDepth ) - 1 ),Traits::Set( alpha, blue, green, red ) ) )
        { }

        /// <summary>
        /// Initializes a new <see cref="Color"/> from a packed 32-bit RGBA value (0xAARRGGBB).
        /// </summary>
        /// <param name="rgba">Packed 32-bit color in 0xAARRGGBB format.</param>
        explicit Color( UInt32 rgba )
            : simd( Traits::Mul( 1.0f / 255.f, 
                Traits::Set( static_cast< value_type >( ( rgba >> 24 ) & 0xFF ), 
                    static_cast< value_type >( ( rgba >> 16 ) & 0xFF ), 
                        static_cast< value_type >( ( rgba >> 8 ) & 0xFF ), 
                            static_cast< value_type >( rgba & 0xFF ) ) ) )
        { }

        /// <summary>
        /// Gets the red component.
        /// </summary>
        /// <returns>Red component as float.</returns>
        float R( ) const { return Traits::Extract<0>( simd ); }
        /// <summary>
        /// Gets the red component.
        /// </summary>
        /// <returns>Red component as float.</returns>
        float Red( ) const { return Traits::Extract<0>( simd ); }

        /// <summary>
        /// Gets the green component.
        /// </summary>
        /// <returns>Green component as float.</returns>
        float G( ) const { return Traits::Extract<1>( simd ); }

        /// <summary>
        /// Gets the green component.
        /// </summary>
        /// <returns>Green component as float.</returns>
        float Green( ) const { return Traits::Extract<1>( simd ); }
        
        /// <summary>
        /// Gets the blue component.
        /// </summary>
        /// <returns>Blue component as float.</returns>
        float B( ) const { return Traits::Extract<2>( simd ); }
        /// <summary>
        /// Gets the blue component.
        /// </summary>
        /// <returns>Blue component as float.</returns>
        float Blue( ) const { return Traits::Extract<2>( simd ); }
        /// <summary>
        /// Gets the alpha component.
        /// </summary>
        /// <returns>Alpha component as float.</returns>
        float A( ) const { return Traits::Extract<3>( simd ); }
        /// <summary>
        /// Gets the alpha component.
        /// </summary>
        /// <returns>Alpha component as float.</returns>
        float Alpha( ) const { return Traits::Extract<3>( simd ); }

        /// <summary>
        /// Access a component by index.
        /// </summary>
        /// <param name="index">Component index (0 = red, 1 = green, 2 = blue, 3 = alpha).</param>
        /// <returns>The component value as float.</returns>
        /// <remarks>
        /// No bounds-check is performed; index must be in the range 0..3 to avoid undefined behavior.
        /// </remarks>
        float operator[]( size_t index ) const
        {
            switch ( index )
            {
				case 0: return R( );
				case 1: return G( );
				case 2: return B( );
                default: return A( );
            }
        }

        /// <summary>
        /// Gets a pointer to the underlying float component array.
        /// </summary>
        /// <returns>Pointer to the first float component (red).</returns>
        const float* data( ) const
        {
            return reinterpret_cast< const float* >( &simd );
        }

        /// <summary>
        /// Returns the components as a std::array in RGBA order.
        /// </summary>
        /// <returns>An array of four floats representing red, green, blue and alpha.</returns>
        std::array<float, 4> ToRGBA( ) const
        {
            alignas( 16 ) std::array<float, 4> result;
            _mm_store_ps( result.data( ), simd );
            return result;
        }

        /// <summary>
        /// Assigns components from a std::array containing RGBA values.
        /// </summary>
        /// <param name="value">Array with four floats in RGBA order.</param>
        void Assign( const std::array<float, 4>& value )
        {
            simd = _mm_loadu_ps( value.data( ) );
        }

        /// <summary>
        /// Sets the red component.
        /// </summary>
        /// <param name="red">New red component value.</param>
        void SetR( float red )
        {
            simd = Traits::SetX( simd, red );
        }
        /// <summary>
        /// Sets the green component.
        /// </summary>
        /// <param name="green">New green component value.</param>
        void SetG( float green )
        {
            simd = Traits::SetY( simd, green );
        }
        /// <summary>
        /// Sets the blue component.
        /// </summary>
        /// <param name="blue">New blue component value.</param>
        void SetB( float blue )
        {
            simd = Traits::SetZ( simd, blue );
        }
        /// <summary>
        /// Sets the alpha component.
        /// </summary>
        /// <param name="alpha">New alpha component value.</param>
        void SetA( float alpha )
        {
            simd = Traits::SetW( simd, alpha );
        }

        /// <summary>
        /// Converts the color from linear space to sRGB space.
        /// </summary>
        /// <returns>A new <see cref="Color"/> converted to sRGB. The alpha channel is preserved.</returns>
        /// <remarks>
        /// The conversion uses the standard sRGB transfer function with a piecewise definition.
        /// Input colors are saturated to the [0,1] range prior to conversion.
        /// </remarks>
        Color ToSRGB( void ) const
        {
            auto saturated = Traits::Saturate( simd );
            auto result = Traits::Sub( Traits::Mul( Traits::Pow( saturated, Traits::Fill( 1.0f / 2.4f ) ), 1.055f ), Traits::Fill( 0.055f ) );
            result = Traits::Select( result, Traits::Mul( saturated, 12.92f ), Traits::Less( saturated, Traits::Fill( 0.0031308f ) ) );
            return Traits::Select( saturated, result, Constants::Select2221 );
        }

        /// <summary>
        /// Converts the color from sRGB space to linear space.
        /// </summary>
        /// <returns>A new <see cref="Color"/> converted from sRGB to linear space. The alpha channel is preserved.</returns>
        inline Color FromSRGB( void ) const
        {
            auto saturated = Traits::Saturate( simd );
            auto result = Traits::Pow( Traits::Mul( Traits::Add( saturated, Traits::Fill( 0.055f ) ), 1.0f / 1.055f ), Traits::Fill( 2.4f ) );
            result = Traits::Select( result, Traits::Mul( saturated, 1.0f / 12.92f ), Traits::Less( saturated, Traits::Fill( 0.0031308f ) ) );
            return Traits::Select( saturated, result, Constants::Select2221 );
        }

        /// <summary>
        /// Converts the color from linear space to REC.709 (gamma 0.45) encoding.
        /// </summary>
        /// <returns>A new <see cref="Color"/> converted to REC.709 encoding. The alpha channel is preserved.</returns>
        inline Color ToREC709( void ) const
        {
            auto saturated = Traits::Saturate( simd );
            auto result = Traits::Sub( Traits::Mul( Traits::Pow( saturated, Traits::Fill( 0.45f ) ), 1.099f ), Traits::Fill( 0.099f ) );
            result = Traits::Select( result, Traits::Mul( saturated, 4.5f ), Traits::Less( saturated, Traits::Fill( 0.0018f ) ) );
            return Traits::Select( saturated, result, Constants::Select2221 );
        }

        /// <summary>
        /// Converts the color from REC.709 encoding to linear space.
        /// </summary>
        /// <returns>A new <see cref="Color"/> converted from REC.709 to linear space. The alpha channel is preserved.</returns>
        inline Color FromREC709( void ) const
        {
            auto saturated = Traits::Saturate( simd );
            auto result = Traits::Pow( Traits::Mul( Traits::Add( saturated, Traits::Fill( 0.099f ) ), 1.0f / 1.099f ), Traits::Fill( 1.0f / 0.45f ) );
            result = Traits::Select( result, Traits::Mul( saturated, 1.0f / 4.5f ), Traits::Less( saturated, Traits::Fill( 0.0081f ) ) );
            return Traits::Select( saturated, result, Constants::Select2221 );
        }

        /// <summary>
        /// Packs the color into a 32-bit R10G10B10A2 format value.
        /// </summary>
        /// <returns>32-bit packed color in R10G10B10A2 layout.</returns>
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

        /// <summary>
        /// Packs the color into a 32-bit R8G8B8A8 format value.
        /// </summary>
        /// <returns>32-bit packed color in R8G8B8A8 layout.</returns>
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

        /// <summary>
        /// Packs the color into the R11G11B10 floating point bitfield representation.
        /// </summary>
        /// <param name="roundToEven">If true, uses round-to-even when quantizing; otherwise uses round-to-nearest.</param>
        /// <returns>32-bit packed R11G11B10F value.</returns>
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
        /// <summary>
        /// Packs the color into a 32-bit R9G9B9E5 shared-exponent format.
        /// </summary>
        /// <returns>32-bit packed R9G9B9E5 value.</returns>
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

    /// <summary>
    /// Returns the component-wise maximum of two colors.
    /// </summary>
    /// <param name="a">First color operand.</param>
    /// <param name="b">Second color operand.</param>
    /// <returns>A <see cref="Color"/> containing the maximum of each component.</returns>
    inline Color Max( Color a, Color b )
    { 
        using Traits = Color::Traits;
        return Color( Traits::Max( a.simd, b.simd ) );
    }
    
    /// <summary>
    /// Returns the component-wise minimum of two colors.
    /// </summary>
    /// <param name="a">First color operand.</param>
    /// <param name="b">Second color operand.</param>
    /// <returns>A <see cref="Color"/> containing the minimum of each component.</returns>
    inline Color Min( Color a, Color b )
    { 
        using Traits = Color::Traits;
        return Color( Traits::Min( a.simd, b.simd ) );
    }
    /// <summary>
    /// Clamps the components of a color to the range defined by <paramref name="a"/> and <paramref name="b"/>.
    /// </summary>
    /// <param name="x">Color to clamp.</param>
    /// <param name="a">Lower bound color.</param>
    /// <param name="b">Upper bound color.</param>
    /// <returns>A <see cref="Color"/> where each component is clamped to the corresponding component in <paramref name="a"/>..&lt;paramref name="b"/&gt;.</returns>
    inline Color Clamp( Color x, Color a, Color b )
    { 
        using Traits = Color::Traits;
        return Color( Traits::Clamp( x.simd, a.simd, b.simd ) );
    }

}
