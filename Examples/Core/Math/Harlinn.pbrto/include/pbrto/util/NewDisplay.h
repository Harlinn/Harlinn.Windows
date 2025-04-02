#pragma once
#ifndef PBRTO_UTIL_NEWDISPLAY_H_
#define PBRTO_UTIL_NEWDISPLAY_H_

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

#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewContainers.h>
#include <pbrto/util/NewImage.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewVecMath.h>

#include <functional>
#include <string>

namespace pbrto
{

    // DisplayServer Function Declarations
    void ConnectToDisplayServer( const std::string& host );
    void DisconnectFromDisplayServer( );

    void DisplayStatic(
        std::string title, Point2i resolution, std::vector<std::string> channelNames,
        std::function<void( Bounds2i, pstdo::span<pstdo::span<float>> )> getValues );

    void DisplayDynamic(
        std::string title, Point2i resolution, std::vector<std::string> channelNames,
        std::function<void( Bounds2i, pstdo::span<pstdo::span<float>> )> getValues );

    void DisplayStatic( std::string title, const Image& image,
        pstdo::optional<ImageChannelDesc> channelDesc = {} );
    void DisplayDynamic( std::string title, const Image& image,
        pstdo::optional<ImageChannelDesc> channelDesc = {} );

    template <typename T>
    inline typename std::enable_if_t<std::is_arithmetic_v<T>, void> DisplayStatic(
        const std::string& title, pstdo::span<const T> values, int xResolution )
    {
        NCHECK_EQ( 0, values.size( ) % xResolution );
        int yResolution = values.size( ) / xResolution;
        DisplayStatic( title, { xResolution, yResolution }, { "value" },
            [ = ]( Bounds2i b, pstdo::span<pstdo::span<float>> displayValue ) {
                NDCHECK_EQ( 1, displayValue.size( ) );
                int index = 0;
                for ( Point2i p : b )
                    displayValue[ 0 ][ index++ ] = values[ p.x + p.y * xResolution ];
            } );
    }

    template <typename T>
    inline typename std::enable_if_t<std::is_arithmetic_v<T>, void> DisplayDynamic(
        const std::string& title, pstdo::span<const T> values, int xResolution )
    {
        NCHECK_EQ( 0, values.size( ) % xResolution );
        int yResolution = values.size( ) / xResolution;
        DisplayDynamic( title, { xResolution, yResolution }, { "value" },
            [ = ]( Bounds2i b, pstdo::span<pstdo::span<float>> displayValue ) {
                NDCHECK_EQ( 1, displayValue.size( ) );
                int index = 0;
                for ( Point2i p : b )
                    displayValue[ 0 ][ index++ ] = values[ p.x + p.y * xResolution ];
            } );
    }

    namespace detail
    {

        // https://stackoverflow.com/a/31306194
        // base case
        template <typename...>
        using void_t = void;

        template <class T, class Index, typename = void>
        struct has_subscript_operator : std::false_type {};

        template <class T, class Index>
        struct has_subscript_operator<T, Index,
            void_t<decltype( std::declval<T>( )[ std::declval<Index>( ) ] )>>
            : std::true_type {};

        template <class T, class Index>
        using has_subscript_operator_t = typename has_subscript_operator<T, Index>::type;

    }  // namespace detail

    template <typename T>
    inline typename std::enable_if_t<detail::has_subscript_operator_t<T, int>::value, void>
        DisplayStatic( const std::string& title, pstdo::span<const T> values,
            const std::vector<std::string>& channelNames, int xResolution )
    {
        NCHECK_EQ( 0, values.size( ) % xResolution );
        int yResolution = values.size( ) / xResolution;
        DisplayStatic( title, { xResolution, yResolution }, channelNames,
            [ = ]( Bounds2i b, pstdo::span<pstdo::span<float>> displayValue ) {
                NDCHECK_EQ( channelNames.size( ), displayValue.size( ) );
                int index = 0;
                for ( Point2i p : b )
                {
                    int offset = p.x + p.y * xResolution;
                    for ( int i = 0; i < channelNames.size( ); ++i )
                        displayValue[ i ][ index ] = values[ offset ][ i ];
                    ++index;
                }
            } );
    }

    template <typename T>
    inline typename std::enable_if_t<detail::has_subscript_operator_t<T, int>::value, void>
        DisplayDynamic( const std::string& title, pstdo::span<const T> values,
            const std::vector<std::string>& channelNames, int xResolution )
    {
        NCHECK_EQ( 0, values.size( ) % xResolution );
        int yResolution = values.size( ) / xResolution;
        DisplayDynamic( title, { xResolution, yResolution }, channelNames,
            [ = ]( Bounds2i b, pstdo::span<pstdo::span<float>> displayValue ) {
                NDCHECK_EQ( channelNames.size( ), displayValue.size( ) );
                int index = 0;
                for ( Point2i p : b )
                {
                    int offset = p.x + p.y * xResolution;
                    for ( int i = 0; i < channelNames.size( ); ++i )
                        displayValue[ i ][ index ] = values[ offset ][ i ];
                    ++index;
                }
            } );
    }

    // TODO: Array2D equivalents

}

#endif
