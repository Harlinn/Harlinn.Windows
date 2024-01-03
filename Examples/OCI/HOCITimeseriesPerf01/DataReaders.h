#pragma once
#ifndef __DATAREADERS_H__
#define __DATAREADERS_H__
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


#include <OwnedObject.h>
#include <Timeseries.h>
#include <HOCI.h>

using namespace Harlinn;

class OwnedObjectTypeDataReader : public OCI::ArrayDataReader
{
public:
    using Base = OCI::ArrayDataReader;
    constexpr static UInt32 ID_FIELDID = 0;
    constexpr static UInt32 NAME_FIELDID = 1;
    constexpr static UInt32 OPTIMISTICLOCK_FIELDID = 2;
    constexpr static UInt32 CREATED_FIELDID = 3;
    constexpr static UInt32 DELETED_FIELDID = 4;
    constexpr static UInt32 DESCRIPTION_FIELDID = 5;

    constexpr static wchar_t SQL[] = L"SELECT Id, Name, OptimisticLock, Created, Deleted, Description FROM OwnedObjectType";

    OwnedObjectTypeDataReader( const OCI::Statement& statement, size_t size )
        : Base( statement, size )
    {
    }


    virtual void InitializeDefines( ) override
    {
        Define<Guid>( ID_FIELDID + 1 );
        Define<WideString>( NAME_FIELDID + 1, 128 );
        Define<Int64>( OPTIMISTICLOCK_FIELDID + 1 );
        Define<DateTime>( CREATED_FIELDID + 1 );
        Define<DateTime>( DELETED_FIELDID + 1 );
        Define<OCI::CLOBArrayDefine>( DESCRIPTION_FIELDID + 1 );
    }

    Guid Id( ) const
    {
        return GetGuid( ID_FIELDID );
    }
    WideString Name( ) const
    {
        return GetString( NAME_FIELDID );
    }
    Int64 OptimisticLock( ) const
    {
        return GetInt64( OPTIMISTICLOCK_FIELDID );
    }
    DateTime Created( ) const
    {
        return GetDateTime( CREATED_FIELDID );
    }
    std::optional<DateTime> Deleted( ) const
    {
        return GetDateTime( DELETED_FIELDID );
    }
    WideString Description( ) const
    {
        return GetString( DESCRIPTION_FIELDID );
    }

    std::unique_ptr<OwnedObjectTypeData> GetDataObject( ) const
    {
        return std::make_unique<OwnedObjectTypeData>( Id( ), Name( ), OptimisticLock( ), Created( ), Deleted( ), Description( ) );
    }
};


class OwnedObjectDataReader : public OCI::ArrayDataReader
{
public:
    using Base = OCI::ArrayDataReader;
    constexpr static UInt32 ID_FIELDID = 0;
    constexpr static UInt32 TYPE_FIELDID = 1;
    constexpr static UInt32 OWNER_FIELDID = 2;
    constexpr static UInt32 NAME_FIELDID = 3;
    constexpr static UInt32 OPTIMISTICLOCK_FIELDID = 4;
    constexpr static UInt32 CREATED_FIELDID = 5;
    constexpr static UInt32 DELETED_FIELDID = 6;
    constexpr static UInt32 DESCRIPTION_FIELDID = 7;
    constexpr static UInt32 DATA_FIELDID = 8;

    constexpr static wchar_t SQL[] = L"SELECT Id, Tp, Owner, Name, OptimisticLock, Created, Deleted, Description, Data FROM OwnedObject";

    OwnedObjectDataReader( const OCI::Statement& statement, size_t size )
        : Base( statement, size )
    {
    }


    virtual void InitializeDefines( ) override
    {
        Define<Guid>( ID_FIELDID + 1 );
        Define<Guid>( TYPE_FIELDID + 1 );
        Define<Guid>( OWNER_FIELDID + 1 );
        Define<WideString>( NAME_FIELDID + 1, 128 );
        Define<Int64>( OPTIMISTICLOCK_FIELDID + 1 );
        Define<DateTime>( CREATED_FIELDID + 1 );
        Define<DateTime>( DELETED_FIELDID + 1 );
        Define<OCI::CLOBArrayDefine>( DESCRIPTION_FIELDID + 1 );
        Define<OCI::BLOBArrayDefine>( DATA_FIELDID + 1 );
    }

    Guid Id( ) const
    {
        return GetGuid( ID_FIELDID );
    }
    Guid Type( ) const
    {
        return GetGuid( TYPE_FIELDID );
    }
    Guid Owner( ) const
    {
        if ( IsDBNull( OWNER_FIELDID ) == false )
        {
            return GetGuid( OWNER_FIELDID );
        }
        return Guid( );
    }
    WideString Name( ) const
    {
        return GetString( NAME_FIELDID );
    }
    Int64 OptimisticLock( ) const
    {
        return GetInt64( OPTIMISTICLOCK_FIELDID );
    }
    DateTime Created( ) const
    {
        return GetDateTime( CREATED_FIELDID );
    }
    std::optional<DateTime> Deleted( ) const
    {
        if ( IsDBNull( DELETED_FIELDID ) == false )
        {
            return GetDateTime( DELETED_FIELDID );
        }
        else
        {
            return std::optional<DateTime>( );
        }
    }
    WideString Description( ) const
    {
        return GetString( DESCRIPTION_FIELDID );
    }

    IO::MemoryStream Data( ) const
    {
        if ( IsDBNull( DATA_FIELDID ) == false )
        {
            auto stream = GetStream( DATA_FIELDID );
            auto streamSize = stream.Size( );

            IO::MemoryStream result;
            result.SetSize( streamSize );
            auto buffer = result.Buffer( );
            stream.Read( buffer, static_cast<size_t>(streamSize) );
            return result;
        }
        else
        {
            return IO::MemoryStream( );
        }
    }

    std::unique_ptr<OwnedObjectData> GetDataObject( ) const
    {
        return std::make_unique<OwnedObjectData>( Id( ), Type(), Owner(), Name( ), OptimisticLock( ), Created( ), Deleted( ), Description( ), Data() );
    }
};


class TimeseriesSegmentDataReader : public OCI::ArrayDataReader
{
public:
    using Base = OCI::ArrayDataReader;

    constexpr static UInt32 ID_FIELDID = 0;
    constexpr static UInt32 OPTIMISTICLOCK_FIELDID = 1;
    constexpr static UInt32 DATA_FIELDID = 2;

    constexpr static wchar_t SQL[] = L"SELECT Id, OptimisticLock, Data FROM TimeseriesSegment";

    TimeseriesSegmentDataReader( const OCI::Statement& statement, size_t size )
        : Base( statement, size )
    {
    }


    virtual void InitializeDefines( ) override
    {
        Define<Guid>( ID_FIELDID + 1 );
        Define<Int64>( OPTIMISTICLOCK_FIELDID + 1 );
        Define<OCI::FixedBinaryArrayDefine<TimeseriesPointSegment::BufferSize>  >( DATA_FIELDID + 1 );
    }

    Guid Id( ) const
    {
        return GetGuid( ID_FIELDID );
    }

    Int64 OptimisticLock( ) const
    {
        return GetInt64( OPTIMISTICLOCK_FIELDID );
    }

    IO::MemoryStream Data( ) const
    {
        auto stream = GetStream( DATA_FIELDID );
        auto streamSize = stream.Size( );

        IO::MemoryStream result;
        result.SetSize( streamSize );
        auto buffer = result.Buffer( );
        stream.Read( buffer, static_cast<size_t>( streamSize ) );
        return result;
    }


    std::unique_ptr<TimeseriesPointSegment> GetDataObject( ) const
    {
        auto result = std::make_unique<TimeseriesPointSegment>( OptimisticLock( ) );
        auto dbdata = static_cast<const Byte*>(GetData( DATA_FIELDID ));
        auto buffer = result->Buffer( );
        memcpy( buffer, dbdata, TimeseriesPointSegment::BufferSize );
        return result;
    }



};


#endif
