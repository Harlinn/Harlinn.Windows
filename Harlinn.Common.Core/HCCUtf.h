#pragma once
#ifndef HCCUTF_H_
#define HCCUTF_H_

#include <HCCDef.h>

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

namespace Harlinn::Common::Core::Utf
{
    using CodePointType = char32_t;


    /**
     * Is this code point a Unicode noncharacter?
     * @param codePoint 32-bit code point
     * @return true or false
     */
    inline constexpr bool IsUnicodeNonChar( CodePointType codePoint )
    {
        return codePoint >= 0xfdd0 && ( codePoint <= 0xfdef || ( codePoint & 0xfffe ) == 0xfffe ) && codePoint <= 0x10ffff;
    }

    /**
     * Is this a Unicode code point value (0..U+10ffff)
     * that can be assigned a character?
     *
     * Code points that are not characters include:
     * - single surrogate code points (U+d800..U+dfff, 2048 code points)
     * - the last two code points on each plane (U+__fffe and U+__ffff, 34 code points)
     * - U+fdd0..U+fdef (new with Unicode 3.1, 32 code points)
     * - the highest Unicode code point value is U+10ffff
     *
     * This means that all code points below U+d800 are character code points,
     * and that boundary is tested first for performance.
     *
     * @param codePoint 32-bit code point
     * @return true or false
     */
    inline constexpr bool IsUnicodeChar( CodePointType codePoint )
    {
        return codePoint < 0xd800 || ( codePoint >= 0xdfff && codePoint <= 0x10ffff && !IsUnicodeNonChar( codePoint ) );
    }

    /**
     * Is this code point a BMP code point (U+0000..U+ffff)?
     * 
     * @param c 32-bit code point
     * @return true or false
     */
    inline constexpr bool IsBmp( CodePointType codePoint )
    {
        return codePoint <= 0xffff;
    }

    /**
     * Is this code point a supplementary code point (U+10000..U+10ffff)?
     * 
     * @param codePoint 32-bit code point
     * @return true or false
     */
    inline constexpr bool IsSupplementary( CodePointType codePoint )
    {
        return ( codePoint - 0x10000 ) <= 0xfffff;
    }

    /**
     * Is this code point a lead surrogate (U+d800..U+dbff)?
     * 
     * @param codePoint 32-bit code point
     * @return true or false
     */
    inline constexpr bool IsLead( CodePointType codePoint )
    {
        return ( codePoint & 0xfffffc00 ) == 0xd800;
    }

    /**
     * Is this code point a trail surrogate (U+dc00..U+dfff)?
     * 
     * @param codePoint 32-bit code point
     * @return true or false
     */
    inline constexpr bool IsTrail( CodePointType codePoint )
    {
        return ( codePoint & 0xfffffc00 ) == 0xdc00;
    }

    /**
     * Is this code point a surrogate (U+d800..U+dfff)?
     * 
     * @param codePoint 32-bit code point
     * @return true or false
     */
    inline constexpr bool IsSurrogate( CodePointType codePoint )
    {
        return ( codePoint & 0xfffff800 ) == 0xd800;
    }

    /**
     * Assuming codePoint is a surrogate code point (IsSurrogate(codePoint)),
     * is it a lead surrogate?
     * 
     * @param codePoint 32-bit code point
     * @return true or false
     */
    inline constexpr bool IsSurrogateLead( CodePointType codePoint )
    {
        return ( codePoint & 0x400 ) == 0;
    }

    /**
     * Assuming codePoint is a surrogate code point (IsSurrogate(codePoint)),
     * is it a trail surrogate?
     *
     * @param codePoint 32-bit code point
     * @return true or false
     */
    inline constexpr bool IsSurrogateTrail( CodePointType codePoint )
    {
        return ( codePoint & 0x400 ) != 0;
    }

    template<typename T>
    class Traits;

    namespace Internal
    {
        template<typename T>
        class Utf16Traits
        {
        public:
            using CharType = T;
            static constexpr bool IsUtf16 = true;
            static constexpr bool IsUtf8 = false;
            static constexpr UInt32 SurrogateOffset = ( 0x0000d800 << 10UL ) + 0xdc00 - 0x10000;

            static constexpr size_t MaxLength = 2;


            /**
             * Does this code unit alone encode a code point (BMP, not a surrogate)?
             * 
             * @param c 16-bit code unit
             * @return true or false
             */
            static constexpr bool IsSingle( CharType c )
            {
                return Utf::IsSurrogate( std::bit_cast<UInt16>( c ) );
            }

            /**
             * Is this code unit a lead surrogate (U+d800..U+dbff)?
             * 
             * @param c 16-bit code unit
             * @return true or false
             */
            static constexpr bool IsLead( CharType c )
            {
                return ( std::bit_cast<UInt16>( c ) & 0xfc00 ) == 0xd800;
            }

            /**
             * Is this code unit a trail surrogate (U+dc00..U+dfff)?
             * 
             * @param c 16-bit code unit
             * @return true or false
             */
            static constexpr bool IsTrail( CharType c )
            {
                return ( std::bit_cast< UInt16 >( c ) & 0xfc00 ) == 0xdc00;
            }


            /**
             * Is this code unit a surrogate (U+d800..U+dfff)?
             * 
             * @param c 16-bit code unit
             * @return true or false
             */
            static constexpr bool IsSurrogate( CharType c )
            {
                return Utf::IsSurrogate( std::bit_cast< UInt16 >( c ) );
            }

            /**
             * Assuming c is a surrogate code point (IsSurrogate(c)),
             * is it a lead surrogate?
             * 
             * @param c 16-bit code unit
             * @return true or false
             */
            static constexpr bool IsSurrogateLead( CharType c )
            {
                return ( std::bit_cast< UInt16 >( c ) & 0x400 ) == 0;
            }

            /**
             * Assuming c is a surrogate code point (IsSurrogate(c)),
             * is it a trail surrogate?
             * 
             * @param c 16-bit code unit
             * @return true or false
             */
            static constexpr bool IsSurrogateTrail( CharType c )
            {
                return ( std::bit_cast< UInt16 >( c ) & 0x400 ) != 0;
            }


            /**
             * Get a supplementary code point value (U+10000..U+10ffff)
             * from its lead and trail surrogates.
             * 
             * The result is undefined if the input values are not
             * lead and trail surrogates.
             *
             * @param lead lead surrogate (U+d800..U+dbff)
             * @param trail trail surrogate (U+dc00..U+dfff)
             * @return supplementary code point (U+10000..U+10ffff)
             */
            static constexpr CodePointType Supplementary( CharType lead, CharType trail )
            {
                CodePointType l = std::bit_cast< UInt16 >( lead );
                CodePointType t = std::bit_cast< UInt16 >( trail );
                return ( l << 10UL ) + t - SurrogateOffset;
            }

            /**
             * Get the lead surrogate (0xd800..0xdbff) for a
             * supplementary code point (0x10000..0x10ffff).
             * 
             * @param supplementary 32-bit code point (U+10000..U+10ffff)
             * @return lead surrogate (U+d800..U+dbff) for supplementary
             */
            static constexpr CharType Lead( CodePointType supplementary )
            {
                return ( supplementary >> 10 ) + 0xd7c0;
            }

            /**
             * Get the trail surrogate (0xdc00..0xdfff) for a
             * supplementary code point (0x10000..0x10ffff).
             * 
             * @param supplementary 32-bit code point (U+10000..U+10ffff)
             * @return trail surrogate (U+dc00..U+dfff) for supplementary
             */
            static constexpr CharType Trail( CodePointType supplementary )
            {
                return ( supplementary & 0x3ff ) | 0xdc00;
            }

            /**
             * How many 16-bit code units are used to encode this Unicode code point? (1 or 2)
             * 
             * The result is not defined if c is not a Unicode code point (U+0000..U+10ffff).
             * 
             * @param c 32-bit code point
             * @return 1 or 2
             */
            static constexpr size_t Length( CodePointType c )
            {
                return c <= 0xffff ? 1 : 2;
            }

            /**
             * Get a code point from a string at a random-access offset,
             * without changing the offset.
             *
             * The offset may point to either the lead or trail surrogate unit
             * for a supplementary code point, in which case the macro will read
             * the adjacent matching surrogate as well.
             * 
             * The result is undefined if the offset points to a single, unpaired surrogate.
             * Iteration through a string is more efficient with U16_NEXT_UNSAFE or U16_NEXT.
             *
             * @param s const UChar * string
             * @param i string offset
             * @return code point
             */
            static constexpr CodePointType CodePoint( const CharType* str, size_t index )
            {
                auto c = str[ index ];
                if ( IsSurrogate( c ) )
                {
                    if ( IsLead( c ) )
                    {
                        return Supplementary( c , str[ index + 1 ] );
                    }
                    else
                    {
                        if ( !index )
                        {
                            throw std::out_of_range( "index is 0" );
                        }
                        return Supplementary( str[ index - 1 ], c );
                    }
                }
                return std::bit_cast< UInt16 >( c );
            }


            static constexpr CodePointType CodePoint( const CharType* str, size_t index, size_t length, size_t start = 0)
            {
                auto c = str[ index ];
                if ( IsSurrogate( c ) )
                { 
                    if ( IsLead( c ) )
                    {
                        auto nextIndex = index + 1;
                        if ( nextIndex >= length )
                        {
                            throw std::out_of_range( "index" );
                        }
                        auto c2 = str[ nextIndex ];
                        if ( !IsTrail( c2 ) )
                        {
                            throw std::logic_error( "not a valid trail surrogate." );
                        }
                        return Supplementary( c, c2 );
                    }
                    else
                    {
                        if ( index <= start )
                        {
                            throw std::out_of_range( "index <= start" );
                        }
                        auto previousIndex = index - 1;
                        auto c2 = str[ previousIndex ];
                        if ( !IsLead( c2 ) )
                        {
                            throw std::logic_error( "not a valid lead surrogate." );
                        }
                        return Supplementary( c2, c );
                    }
                }
                return std::bit_cast< UInt16 >( c );
            }

            static constexpr const CharType* Next( const CharType* str )
            {
                auto c = *str;
                if ( IsLead( c ) )
                {
                    return str + 2;
                }
                return str + 1;
            }


        };

        template<typename T>
        class Utf8Traits
        {
        public:
            using CharType = T;
            static constexpr bool IsUtf16 = false;
            static constexpr bool IsUtf8 = true;
        };
    }

    template<>
    class Traits<wchar_t> : public Internal::Utf16Traits<wchar_t>
    { };
    template<>
    class Traits<char16_t> : public Internal::Utf16Traits<char16_t>
    { };


    namespace Internal
    {
        
    }
    template<>
    class Traits<char> : public Internal::Utf8Traits<char>
    {
    };
    template<>
    class Traits<unsigned char> : public Internal::Utf8Traits<unsigned char>
    {
    };
    template<>
    class Traits<signed char> : public Internal::Utf8Traits<signed char>
    {
    };
    template<>
    class Traits<char8_t> : public Internal::Utf8Traits<char8_t>
    {
    };

}


#endif
