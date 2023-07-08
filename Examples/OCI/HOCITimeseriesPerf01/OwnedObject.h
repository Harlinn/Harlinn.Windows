#pragma once
#ifndef __OWNEDOBJECT_H__
#define __OWNEDOBJECT_H__

#include <HCCString.h>
#include <HCCDateTime.h>
#include <HCCGuid.h>
#include <HCCIO.h>

using namespace Harlinn::Common::Core;

struct OwnedObjectTypeData
{
    Guid Id;
    WideString Name;
    Int64 OptimisticLock;
    DateTime Created;
    std::optional<DateTime> Deleted;
    WideString Description;

    OwnedObjectTypeData( const Guid& id,
        WideString&& name,
        Int64 optimisticLock,
        const DateTime& created,
        const std::optional<DateTime>& deleted,
        WideString&& description )
        : Id( id ), Name(std::move( name )), OptimisticLock( optimisticLock ), Created( created ), Deleted( deleted ), Description(std::move( description ))
    {}

    OwnedObjectTypeData( const Guid& id,
        const WideString& name,
        Int64 optimisticLock,
        const DateTime& created,
        const std::optional<DateTime>& deleted,
        const WideString& description )
        : Id( id ), Name( name ), OptimisticLock( optimisticLock ), Created( created ), Deleted( deleted ), Description( description )
    {
    }


};

struct OwnedObjectData
{
    Guid Id;
    Guid Type;
    Guid Owner;
    WideString Name;
    Int64 OptimisticLock;
    DateTime Created;
    std::optional<DateTime> Deleted;
    WideString Description;
    IO::MemoryStream Data;

    OwnedObjectData( const Guid& id, const Guid& type, const Guid& owner,
        WideString&& name,
        Int64 optimisticLock,
        const DateTime& created,
        const std::optional<DateTime>& deleted,
        WideString&& description, IO::MemoryStream&& data )
        : Id( id ), Type(type), Owner( owner ), Name( std::move( name ) ), OptimisticLock( optimisticLock ), Created( created ), Deleted( deleted ), Description( std::move( description ) ), Data(std::move(data))
    {
    }

    OwnedObjectData( const Guid& id, const Guid& type, const Guid& owner,
        const WideString& name,
        Int64 optimisticLock,
        const DateTime& created,
        const std::optional<DateTime>& deleted,
        const WideString& description, const IO::MemoryStream& data )
        : Id( id ), Type( type ), Owner( owner ), Name( name ), OptimisticLock( optimisticLock ), Created( created ), Deleted( deleted ), Description( description ), Data( data )
    {
    }

};

struct TimeseriesData : public OwnedObjectData
{
    using Base = OwnedObjectData;



};




#endif
