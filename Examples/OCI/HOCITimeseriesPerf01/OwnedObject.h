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
    std::wstring Name;
    Int64 OptimisticLock;
    DateTime Created;
    std::optional<DateTime> Deleted;
    std::wstring Description;

    OwnedObjectTypeData( const Guid& id,
        std::wstring&& name,
        Int64 optimisticLock,
        const DateTime& created,
        const std::optional<DateTime>& deleted,
        std::wstring&& description )
        : Id( id ), Name(std::move( name )), OptimisticLock( optimisticLock ), Created( created ), Deleted( deleted ), Description(std::move( description ))
    {}

    OwnedObjectTypeData( const Guid& id,
        const std::wstring& name,
        Int64 optimisticLock,
        const DateTime& created,
        const std::optional<DateTime>& deleted,
        const std::wstring& description )
        : Id( id ), Name( name ), OptimisticLock( optimisticLock ), Created( created ), Deleted( deleted ), Description( description )
    {
    }


};

struct OwnedObjectData
{
    Guid Id;
    Guid Type;
    Guid Owner;
    std::wstring Name;
    Int64 OptimisticLock;
    DateTime Created;
    std::optional<DateTime> Deleted;
    std::wstring Description;
    IO::MemoryStream Data;

    OwnedObjectData( const Guid& id, const Guid& type, const Guid& owner,
        std::wstring&& name,
        Int64 optimisticLock,
        const DateTime& created,
        const std::optional<DateTime>& deleted,
        std::wstring&& description, IO::MemoryStream&& data )
        : Id( id ), Type(type), Owner( owner ), Name( std::move( name ) ), OptimisticLock( optimisticLock ), Created( created ), Deleted( deleted ), Description( std::move( description ) ), Data(std::move(data))
    {
    }

    OwnedObjectData( const Guid& id, const Guid& type, const Guid& owner,
        const std::wstring& name,
        Int64 optimisticLock,
        const DateTime& created,
        const std::optional<DateTime>& deleted,
        const std::wstring& description, const IO::MemoryStream& data )
        : Id( id ), Type( type ), Owner( owner ), Name( name ), OptimisticLock( optimisticLock ), Created( created ), Deleted( deleted ), Description( description ), Data( data )
    {
    }

};

struct TimeseriesData : public OwnedObjectData
{
    using Base = OwnedObjectData;



};




#endif
