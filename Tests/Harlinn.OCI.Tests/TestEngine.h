#pragma once
#ifndef __TESTDATACONTEXT_H__
#define __TESTDATACONTEXT_H__
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

#include "TestTypes.h"
#include <HOCI.h>

using namespace Harlinn;
using namespace Harlinn::Common::Core;

namespace OCITest
{

    class OwnedObjectTypeReader : public OCI::ArrayDataReader
    {

    public:
        static constexpr UInt32 ID_FIELD_ID = 0;
        static constexpr UInt32 NAME_FIELD_ID = 1;
        static constexpr UInt32 OPTIMISTICLOCK_FIELD_ID = 2;
        static constexpr UInt32 CREATED_FIELD_ID = 3;
        static constexpr UInt32 DELETED_FIELD_ID = 4;
        static constexpr UInt32 DESCRIPTION_FIELD_ID = 5;

        static constexpr wchar_t SQL[] = L"SELECT Id, Name, OptimisticLock, Created, Deleted, Description FROM OwnedObjectType";



        using Base = OCI::ArrayDataReader;

        OwnedObjectTypeReader( const OCI::Statement& statement, size_t rowCount )
            : Base( statement, rowCount )
        {
        }

        virtual void InitializeDefines( ) final override
        {
            Define<Guid>( ID_FIELD_ID + 1 );
            Define<WideString>( NAME_FIELD_ID + 1, 128 );
            Define<Int64>( OPTIMISTICLOCK_FIELD_ID + 1 );
            Define<DateTime>( CREATED_FIELD_ID + 1 );
            Define<DateTime>( DELETED_FIELD_ID + 1 );
            Define<OCI::CLOBArrayDefine>( DESCRIPTION_FIELD_ID + 1 );
        }

        Guid Id( ) { return As<Guid>( ID_FIELD_ID ); }
        WideString Name( ) { return As<WideString>( NAME_FIELD_ID ); }
        Int64 OptimisticLock( ) { return As<Int64>( OPTIMISTICLOCK_FIELD_ID ); }
        DateTime Created( ) { return As<DateTime>( CREATED_FIELD_ID ); }
        std::optional<DateTime> Deleted( ) { return As<std::optional<DateTime>>( DELETED_FIELD_ID ); }
        WideString Description( ) { return As<WideString>( DESCRIPTION_FIELD_ID ); }

        void AssignTo( OwnedObjectType& ownedObjectType )
        {
            ownedObjectType.Assign( Id( ), Name( ), OptimisticLock( ), Created( ), Deleted( ), Description( ) );
        }


    };



    class Session
    {
        OCI::ServiceContext serviceContext_;
    public:
        Session( OCI::ServiceContext&& serviceContext )
            : serviceContext_( std::move( serviceContext ) )
        {
        }

        Session( const Session& other ) = delete;
        Session( Session&& other ) noexcept
            : serviceContext_( std::move( other.serviceContext_ ) )
        {

        }

        ~Session( )
        {
            if ( IsValid( ) )
            {
                SessionEnd( );
            }
        }

        Session& operator = ( const Session& other ) = delete;
        Session& operator = ( Session&& other ) noexcept
        {
            if ( this != &other )
            {
                serviceContext_ = std::move( other.serviceContext_ );
            }
            return *this;
        }

        bool IsValid( ) const noexcept
        {
            return serviceContext_.IsValid( );
        }

        void SessionBegin( ) const
        {
            serviceContext_.SessionBegin( );
        }
        void SessionEnd( ) const
        {
            serviceContext_.SessionEnd( );
        }

        void Commit( ) const
        {
            serviceContext_.TransactionCommit( );
        }



        const OCI::ServiceContext& ServiceContext( ) const noexcept
        {
            return serviceContext_;
        }

        OCI::Statement CreateStatement( const WideString& sql )
        {
            return serviceContext_.CreateStatement( sql );
        }


        void Insert( const OwnedObjectType& ownedObjectType )
        {
            std::optional<WideString> description;
            if ( ownedObjectType.Description( ).length( ) )
            {
                description = ownedObjectType.Description( );
            }

            constexpr wchar_t SQL[] = L"INSERT INTO OwnedObjectType(Id, Name, OptimisticLock, Created, Description) "\
                L"VALUES(:1,:2,0,:3,:4)";

            static WideString sql( SQL );
            auto statement = serviceContext_.CreateStatement( sql, 
                ownedObjectType.Id( ), 
                ownedObjectType.Name( ), 
                ownedObjectType.Created( ),
                description );
            statement.Execute( );
        }
        /*
        void Insert( const OwnedObjectType& ownedObjectType )
        {
            constexpr wchar_t SQL[] = L"INSERT INTO OwnedObjectType(Id, Name, OptimisticLock, Created, Description) "\
                L"VALUES(:1,:2,0,:3,:4)";

            static WideString sql( SQL );
            auto statement = CreateStatement( sql );
            auto id = statement.Bind<Guid>( 1 );
            id->Assign( ownedObjectType.Id( ) );
            auto name = statement.Bind<WideString>( 2, ownedObjectType.Name( ).length() );
            name->Assign( ownedObjectType.Name( ) );
            auto created = statement.Bind<DateTime>( 3 );
            created->Assign( ownedObjectType.Created( ) );

            auto description = statement.Bind<WideString>( 4, ownedObjectType.Description( ).length( ) );
            if ( ownedObjectType.Description( ).length( ) )
            {
                description->Assign( ownedObjectType.Description( ) );
            }
            else
            {
                description->SetDBNull( );
            }
            statement.Execute( );
        }
        */

        bool OwnedObjectTypeExist( const Guid& id )
        {
            constexpr wchar_t SQL[] = L"SELECT COUNT(*) FROM OwnedObjectType WHERE Id=:1";
            static WideString sql( SQL );
            auto statement = CreateStatement( sql );
            auto bind = statement.Bind<OCI::GuidBind>( 1 );
            bind->Assign( id );
            auto result = statement.ExecuteScalar<Int32>( );
            return result.has_value( ) ? result.value( ) > 0 : false;
        }
        bool OwnedObjectTypeExist( const WideString& name )
        {
            constexpr wchar_t SQL[] = L"SELECT COUNT(*) FROM OwnedObjectType WHERE Name=:1";
            static WideString sql( SQL );
            auto statement = CreateStatement( sql );
            auto bind = statement.Bind<OCI::CStringBind>( 1 );
            bind->Assign( name );
            auto result = statement.ExecuteScalar<Int32>( );
            return result.has_value( ) ? result.value( ) > 0 : false;
        }
        void OwnedObjectTypeDelete( )
        {
            constexpr wchar_t SQL[] = L"DELETE FROM OwnedObjectType";
            static WideString sql( SQL );
            auto statement = CreateStatement( sql );
            statement.Execute( );
        }
        void OwnedObjectTypeDelete( const Guid& id )
        {
            constexpr wchar_t SQL[] = L"DELETE FROM OwnedObjectType WHERE Id=:1";
            static WideString sql( SQL );
            auto statement = CreateStatement( sql );
            auto bind = statement.Bind<OCI::GuidBind>( 1 );
            bind->Assign( id );
            statement.Execute( );
        }
        void OwnedObjectTypeDelete( const WideString& name )
        {
            constexpr wchar_t SQL[] = L"DELETE FROM OwnedObjectType WHERE Name=:1";
            static WideString sql( SQL );
            auto statement = CreateStatement( sql );
            auto bind = statement.Bind<OCI::CStringBind>( 1 );
            bind->Assign( name );
            statement.Execute( );
        }




    };

    class Engine
    {
        OCI::Environment environment_;
        OCI::Server server_;
    public:
        Engine( const OCI::EnvironmentOptions& options )
            : environment_( options )
        {
            server_ = environment_.CreateServer( );
        }

        Session Connect( const WideString& username, const WideString& password, const WideString& alias )
        {
            auto serviceContext = server_.CreateServiceContext( username, password, alias );
            Session result( std::move( serviceContext ) );
            result.SessionBegin( );
            return result;
        }
    };


}

#endif
