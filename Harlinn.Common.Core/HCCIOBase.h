#pragma once
#ifndef __HCCIOBASE_H__
#define __HCCIOBASE_H__
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


#include <HCCDef.h>

namespace Harlinn::Common::Core::IO
{
    enum class SeekOrigin
    {
        StartOfFile = 0,
        CurrentPosition = 1,
        EndOfFile = 2
    };

    template<typename T>
    concept StreamReader = requires( T t, void* buffer, size_t count )
    {
        { t.Read( buffer, count ) }->std::convertible_to<long long>;
    };

    template<typename T>
    concept StreamWriter = requires( T t, const void* constBuffer, size_t count )
    {
        { t.Write( constBuffer, count ) }->std::convertible_to<long long>;
    };

    template<typename T>
    concept StreamPosition = requires( T t, long long position )
    {
        { t.Position( ) }->std::convertible_to<long long>;
        { t.SetPosition( position ) };
    };
    template<typename T>
    concept StreamSize = requires( T t, long long size )
    {
        { t.Size( ) }->std::convertible_to<long long>;
        { t.SetSize( size ) };
    };


    template<typename T>
    concept StreamIO = ( StreamReader<T> && StreamWriter<T> );

    template<typename T>
    concept StreamSeek = requires( T t, long long offset, SeekOrigin seekOrigin )
    {
        { t.Seek( offset, seekOrigin ) }->std::convertible_to<long long>;
    };

    template<typename T>
    concept StreamFeatureTests = requires( T t )
    {
        { t.CanRead( ) } ->std::convertible_to<bool>;
        { t.CanSeek( ) } ->std::convertible_to<bool>;
        { t.CanTimeout( ) } ->std::convertible_to<bool>;
        { t.CanWrite( ) } ->std::convertible_to<bool>;
    };


    template<typename T>
    concept StreamFlush = requires( T t )
    {
        { t.Flush( ) };
    };

    template<typename T>
    concept StreamClone = requires( T t )
    {
        { t.Clone( ) } -> std::convertible_to<T>;
    };


    template<typename T>
    concept Stream = ( StreamIO<T> && StreamPosition<T> && StreamSize<T> && StreamSeek<T> && StreamFlush<T> );




}

#endif
