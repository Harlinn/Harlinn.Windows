#pragma once
#ifndef __DATACONTEXT_H__
#define __DATACONTEXT_H__
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


#include <DataReaders.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn;

class Session;
class Engine;

class DataContext
{
    const Session* session_;
public:
    DataContext( Session& session )
        : session_( &session )
    { }
    const OCI::ServiceContext& ServiceContext( ) const;

    std::unique_ptr<OwnedObjectTypeData> CreateOwnedObjectType( const WideString& name, const WideString& description ) const;
    std::unique_ptr<OwnedObjectTypeData> CreateOwnedObjectType( const wchar_t* name, const wchar_t* description ) const
    {
        return CreateOwnedObjectType( WideString( name ), WideString( description ) );
    }

    std::unique_ptr<OwnedObjectTypeData> CreateOwnedObjectType( const Guid& id, const WideString& name, const WideString& description ) const;
    std::unique_ptr<OwnedObjectTypeData> CreateOwnedObjectType( const Guid& id, const wchar_t* name, const wchar_t* description ) const
    {
        return CreateOwnedObjectType( id, WideString( name ), WideString( description ) );
    }
    std::unique_ptr<OwnedObjectTypeData> FindOwnedObjectType( const Guid& id ) const;
    std::unique_ptr<OwnedObjectTypeData> FindOwnedObjectType( const WideString& name ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectTypeData> > ReadOwnedObjectTypes( ) const;
    void ClearOwnedObjectTypes( ) const;
    bool UpdateOwnedObjectType( std::unique_ptr<OwnedObjectTypeData>& data ) const;
    bool DeleteOwnedObjectType( const Guid& id, Int64 optimisticLock ) const;
    

    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& type, const WideString& name, const WideString& description ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& type, const wchar_t* name, const wchar_t* description ) const
    {
        return CreateOwnedObject( type, WideString( name ), WideString( description ) );
    }
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& type, const WideString& name, const WideString& description, const IO::MemoryStream& data ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& id, const Guid& type, const WideString& name, const WideString& description ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& id, const Guid& owner, const Guid& type, const WideString& name, const WideString& description ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& id, const Guid& type, const WideString& name, const WideString& description, const IO::MemoryStream& data ) const;
    std::unique_ptr<OwnedObjectData> CreateOwnedObject( const Guid& id, const Guid& owner, const Guid& type, const WideString& name, const WideString& description, const IO::MemoryStream& data ) const;
    std::unique_ptr<OwnedObjectData> FindOwnedObject( const Guid& id ) const;
    std::unique_ptr<OwnedObjectData> FindOwnedObject( const Guid& owner, const WideString& name ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > ReadOwnedObjects( ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > ReadOwnedObjectsByOwner( const Guid& owner ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > ReadOwnedObjectsByType( const Guid& type ) const;
    std::unordered_map<Guid, std::unique_ptr<OwnedObjectData> > ReadOwnedObjectsByOwnerAndType( const Guid& owner, const Guid& type ) const;
    void ClearOwnedObjects( ) const;
    bool UpdateOwnedObject( std::unique_ptr<OwnedObjectData>& data ) const;
    bool DeleteOwnedObject( const Guid& id, Int64 optimisticLock ) const;

    void InsertTimeseriesPointSegment( const Guid& owner, const TimeseriesPointSegment& segment ) const;
    TimeseriesPoints ReadSegments( const Guid& owner ) const;
    void ClearTimeseriesPointSegments( ) const;


};

class Session
{
    const Engine* engine_;
    OCI::Server server_;
    OCI::ServiceContext serviceContext_;
public:
    Session( const Engine& engine, const WideString& userId, const WideString& password, const WideString& alias );
    ~Session( )
    {
        serviceContext_.SessionEnd( );
    }
        
    const OCI::Server& Server( ) const
    {
        return server_;
    }
    const OCI::ServiceContext& ServiceContext( ) const
    {
        return serviceContext_;
    }
    void Commit( OCI::TransactionEndFlags flags = OCI::TransactionEndFlags::WriteImmediately ) const
    {
        serviceContext_.TransactionCommit( );
    }

};

inline const OCI::ServiceContext& DataContext::ServiceContext( ) const
{
    return session_->ServiceContext( );
}

class Engine
{
    OCI::Environment environment_;
public:
    Engine( )
        : environment_( OCI::EnvironmentOptions() )
    { }

    const OCI::Environment& Environment( ) const
    {
        return environment_;
    }



};

inline Session::Session( const Engine& engine, const WideString& userId, const WideString& password, const WideString& alias )
    : engine_( &engine )
{
    const auto& environment = engine.Environment( );
    server_ = environment.CreateServer( );
    serviceContext_ = server_.CreateServiceContext( userId, password, alias );
    serviceContext_.SessionBegin( );
}


#endif
