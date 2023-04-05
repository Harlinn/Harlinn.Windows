#pragma once
#ifndef __HCCIOBASE_H__
#define __HCCIOBASE_H__

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
