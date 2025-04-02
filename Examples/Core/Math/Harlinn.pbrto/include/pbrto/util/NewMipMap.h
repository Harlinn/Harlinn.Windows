#pragma once
#ifndef PBRTO_UTIL_NEWMIPMAP_H_
#define PBRTO_UTIL_NEWMIPMAP_H_

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <pbrto/util/NewImage.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewVecMath.h>

#include <memory>
#include <string>
#include <vector>

namespace pbrto
{

    // FilterFunction Definition
    enum class FilterFunction 
    { 
        Point, Bilinear, Trilinear, EWA 
    };

}

namespace std
{
    template<typename CharT>
    struct formatter<pbrto::FilterFunction, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( pbrto::FilterFunction value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                switch ( value )
                {
                    case pbrto::FilterFunction::EWA:
                        return std::format_to( ctx.out( ), L"EWA" );
                    case pbrto::FilterFunction::Trilinear:
                        return std::format_to( ctx.out( ), L"trilinear" );
                    case pbrto::FilterFunction::Bilinear:
                        return std::format_to( ctx.out( ), L"bilinear" );
                    default:
                        return std::format_to( ctx.out( ), L"point" );
                }

            }
            else
            {
                switch ( value )
                {
                    case pbrto::FilterFunction::EWA:
                        return std::format_to( ctx.out( ), "EWA" );
                    case pbrto::FilterFunction::Trilinear:
                        return std::format_to( ctx.out( ), "trilinear" );
                    case pbrto::FilterFunction::Bilinear:
                        return std::format_to( ctx.out( ), "bilinear" );
                    default:
                        return std::format_to( ctx.out( ), "point" );
                }
            }
        }
    };
}

namespace pbrto
{

    inline pstdo::optional<FilterFunction> ParseFilter( const std::string& f )
    {
        if ( f == "ewa" || f == "EWA" )
            return FilterFunction::EWA;
        else if ( f == "trilinear" )
            return FilterFunction::Trilinear;
        else if ( f == "bilinear" )
            return FilterFunction::Bilinear;
        else if ( f == "point" )
            return FilterFunction::Point;
        else
            return {};
    }

    std::string ToString( FilterFunction f );

    // MIPMapFilterOptions Definition
    struct MIPMapFilterOptions
    {
        FilterFunction filter = FilterFunction::EWA;
        Float maxAnisotropy = 8.f;
        bool operator<( MIPMapFilterOptions o ) const
        {
            return std::tie( filter, maxAnisotropy ) < std::tie( o.filter, o.maxAnisotropy );
        }
        std::string ToString( ) const;
    };

    // MIPMap Definition
    class MIPMap
    {
    public:
        // MIPMap Public Methods
        MIPMap( Image image, const RGBColorSpace* colorSpace, WrapMode wrapMode,
            Allocator alloc, const MIPMapFilterOptions& options );
        static MIPMap* CreateFromFile( const std::string& filename,
            const MIPMapFilterOptions& options, WrapMode wrapMode,
            ColorEncoding encoding, Allocator alloc );

        template <typename T>
        T Filter( Point2f st, Vector2f dstdx, Vector2f dstdy ) const;

        std::string ToString( ) const;

        Point2i LevelResolution( int level ) const
        {
            NCHECK( level >= 0 && level < pyramid.size( ) );
            return pyramid[ level ].Resolution( );
        }
        int Levels( ) const { return int( pyramid.size( ) ); }
        const RGBColorSpace* GetRGBColorSpace( ) const { return colorSpace; }
        const Image& GetLevel( int level ) const { return pyramid[ level ]; }

    private:
        // MIPMap Private Methods
        template <typename T>
        T Texel( int level, Point2i st ) const;
        template <typename T>
        T Bilerp( int level, Point2f st ) const;
        template <typename T>
        T EWA( int level, Point2f st, Vector2f dst0, Vector2f dst1 ) const;

        // MIPMap Private Members
        pstdo::vector<Image> pyramid;
        const RGBColorSpace* colorSpace;
        WrapMode wrapMode;
        MIPMapFilterOptions options;
    };

}

#endif
