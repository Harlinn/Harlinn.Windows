#pragma once
#ifndef __OWNEDOBJECTTYPE_H__
#define __OWNEDOBJECTTYPE_H__
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

#include <HODef.h>
#include <HCCIO.h>

namespace OCITest
{
    using namespace Harlinn::Common::Core;

    class OwnedObjectType
    {
        Guid id_;
        WideString name_;
        Int64 optimisticLock_;
        DateTime created_;
        std::optional<DateTime> deleted_;
        WideString description_;
    public:
        OwnedObjectType( )
            : optimisticLock_( -1 )
        {
        }

        OwnedObjectType( const Guid& id, const WideString& name, Int64 optimisticLock, const DateTime& created, const std::optional<DateTime>& deleted, const WideString& description )
            : id_( id ), name_( name ), optimisticLock_( optimisticLock ), created_( created ), deleted_( deleted ), description_( description )
        {
        }

        OwnedObjectType( const WideString& name, const WideString& description = WideString() )
            : id_( Guid::NewGuid() ), name_( name ), optimisticLock_( -1 ), created_( DateTime::Now() ), description_( description )
        {
        }

        void Assign( const Guid& id, const WideString& name, Int64 optimisticLock, const DateTime& created, const std::optional<DateTime>& deleted, const WideString& description )
        {
            id_ = id;
            name_ = name;
            optimisticLock_ = optimisticLock;
            created_ = created;
            deleted_ = deleted;
            description_ = description;
        }

        const Guid& Id( ) const noexcept
        {
            return id_;
        }
        void SetId( const Guid& id ) noexcept
        {
            id_ = id;
        }

        const WideString& Name( ) const noexcept
        {
            return name_;
        }
        void SetName( const WideString& name )
        {
            name_ = name;
        }

        Int64 OptimisticLock( ) const noexcept
        {
            return optimisticLock_;
        }
        void SetOptimisticLock( Int64 optimisticLock )
        {
            optimisticLock_ = optimisticLock;
        }

        const DateTime& Created( ) const noexcept
        {
            return created_;
        }
        void SetCreated( const DateTime& created )
        {
            created_ = created;
        }

        const std::optional<DateTime>& Deleted( ) const noexcept
        {
            return deleted_;
        }
        void SetDeleted( const std::optional<DateTime>& deleted )
        {
            deleted_ = deleted;
        }
        void SetDeleted( nullptr_t )
        {
            deleted_.reset( );
        }
        void SetDeleted( const DateTime& deleted )
        {
            deleted_ = deleted;
        }

        const WideString& Description( ) const noexcept
        {
            return description_;
        }
        void SetDescription( const WideString& description )
        {
            description_ = description;
        }
    };

    class OwnedObject
    {
        Guid id_;
        Guid type_;
        Guid owner_;
        WideString name_;
        Int64 optimisticLock_;
        DateTime created_;
        std::optional<DateTime> deleted_;
        WideString description_;
        IO::MemoryStream data_;
    public:
        OwnedObject( )
            : optimisticLock_( -1 )
        {
        }

        OwnedObject( const Guid& id, const Guid& type, const Guid& owner, const WideString& name, Int64 optimisticLock, const DateTime& created, const std::optional<DateTime>& deleted, const WideString& description, const IO::MemoryStream& data )
            : id_( id ), type_( type ), owner_( owner ), name_( name ), optimisticLock_( optimisticLock ), created_( created ), deleted_( deleted ), description_( description ), data_( data )
        {
        }

        void Assign( const Guid& id, const Guid& type, const Guid& owner, const WideString& name, Int64 optimisticLock, const DateTime& created, const std::optional<DateTime>& deleted, const WideString& description, const IO::MemoryStream& data )
        {
            id_ = id;
            type_ = type;
            owner_ = owner;
            name_ = name;
            optimisticLock_ = optimisticLock;
            created_ = created;
            deleted_ = deleted;
            description_ = description;
            data_ = data;
        }

        const Guid& Id( ) const noexcept
        {
            return id_;
        }
        void SetId( const Guid& id ) noexcept
        {
            id_ = id;
        }

        const Guid& Type( ) const noexcept
        {
            return type_;
        }
        void SetType( const Guid& type ) noexcept
        {
            type_ = type;
        }

        const Guid& Owner( ) const noexcept
        {
            return owner_;
        }

        void SetOwner( const Guid& owner ) noexcept
        {
            owner_ = owner;
        }

        const WideString& Name( ) const noexcept
        {
            return name_;
        }
        void SetName( const WideString& name )
        {
            name_ = name;
        }

        Int64 OptimisticLock( ) const noexcept
        {
            return optimisticLock_;
        }
        void SetOptimisticLock( Int64 optimisticLock ) noexcept
        {
            optimisticLock_ = optimisticLock;
        }

        const DateTime& Created( ) const noexcept
        {
            return created_;
        }
        void SetCreated( const DateTime& created ) noexcept
        {
            created_ = created;
        }

        const std::optional<DateTime>& Deleted( ) const noexcept
        {
            return deleted_;
        }
        void SetDeleted( const std::optional<DateTime>& deleted ) noexcept
        {
            deleted_ = deleted;
        }
        void SetDeleted( nullptr_t ) noexcept
        {
            deleted_.reset( );
        }

        const WideString& Description( ) const noexcept
        {
            return description_;
        }
        void SetDescription( const WideString& description )
        {
            description_ = description;
        }

        const IO::MemoryStream& Data( ) const noexcept
        {
            return data_;
        }
        void SetData( const IO::MemoryStream& data )
        {
            data_ = data;
        }
    };


    class Timeseries : public OwnedObject
    {

    };

}

#endif
